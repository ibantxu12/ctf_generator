#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/vulnerabilidades.h"
#include "../include/herramientas.h"

extern char *rutaDockers;
extern char *rutaListas;

bool crearSuid(const char *nombreMaquina){
    char cambiarPermisos[100];
    char rutainstall[100];
    char listaSuid[100];
    sprintf(listaSuid,"%ssuid.txt",rutaListas);
    char *archivoVuln = lineaAleatoria(listaSuid);
    sprintf(cambiarPermisos,"chmod u+s %s && chmod +x %s",archivoVuln,archivoVuln);
    sprintf(rutainstall, "%s%s/src/scripts/install.sh",rutaDockers,nombreMaquina);
    if(!modificarLinea(rutainstall,"##elevacion##",cambiarPermisos)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de escalada.");
        return false;
    }
    return true;
}

bool crearSudo(const char *nombreMaquina){
    char anadirSudoers[100];
    char rutainstall[100];
    char listaSudo[100];
    sprintf(listaSudo,"%ssudo.txt",rutaListas);
    sprintf(anadirSudoers,"echo 'ALL ALL=(ALL) NOPASSWD: %s' >> /etc/sudoers",lineaAleatoria(listaSudo));
    sprintf(rutainstall, "%s%s/src/scripts/install.sh",rutaDockers,nombreMaquina);
    if(!modificarLinea(rutainstall,"##elevacion##",anadirSudoers)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de escalada.");
        return false;
    }
    return true;
}

bool usypassRelajado(const char *nombreMaquina){
    char anadirUsuario[100];
    char rutainstall[100];
    char listaUsyPas[100];
    sprintf(listaUsyPas,"%susuarioyPass.txt",rutaListas);
    sprintf(anadirUsuario,"INSERT INTO usuarios (usuario, contrasena) VALUES %s",lineaAleatoria(listaUsyPas));
    sprintf(rutainstall, "%s%s/src/scripts/install.sh",rutaDockers, nombreMaquina);
    if(!modificarLinea(rutainstall,"-- relajados --",anadirUsuario)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de login.");
        return false;
    }
    return true;
}

bool sqlInjection(const char *nombreMaquina){
    char rutalogin[100];
    sprintf(rutalogin, "%s%s/src/webContent/login.php",rutaDockers, nombreMaquina);
    if(!modificarLinea(rutalogin,"##sqlinjectionP##","$sql = \"SELECT * FROM usuarios WHERE usuario = '$usuario' AND contrasena = '$contrasena'\"; /*") || !modificarLinea(rutalogin,"##sqlinjectionF##","*/\n$result = $pdo->query($sql);\nif ($result && $result->rowCount() > 0) {")){
        printf("ERROR: no se ha podido generar la vulnerabilidad de login.");
        return false;
    }
    return true;
}

bool crearVulnerabilidadLogin(const char *nombreMaquina){
    int tipoVuln = rand() % 2;
    if (tipoVuln == 0){
        //Vulnerabilidad con usuario y password relajado
        return usypassRelajado(nombreMaquina);
    }else {
        //Vulnerabilidad con sqlinjection
        return sqlInjection(nombreMaquina);
    }
}

bool crearVulnerabilidadElevacion(const char *nombreMaquina){
    int tipoVuln = rand() % 2;
    if (tipoVuln == 0){
        //Vulnerabilidad con SUID
        return crearSuid(nombreMaquina);
    }else {
        //Vulnerabilidad con Sudo
        return crearSudo(nombreMaquina);
    }
}