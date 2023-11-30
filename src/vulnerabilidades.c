#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/vulnerabilidades.h"
#include "../include/herramientas.h"

extern char *rutaDockers;
extern char *rutaListas;
extern char *rutaVulnsWriteUp;

bool crearSuid(const char *nombreMaquina){
    char cambiarPermisos[500];
    char rutainstall[100];
    char listaSuid[100];
    sprintf(listaSuid,"%ssuid.txt",rutaListas);
    char *archivoVuln = lineaAleatoria(listaSuid);
    sprintf(cambiarPermisos,"groupadd login && usermod -a -G login www-data && chgrp login %s && chmod u+s %s && chmod g+x %s && chmod o-x %s",archivoVuln,archivoVuln,archivoVuln,archivoVuln);
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
    if(!modificarLinea(rutalogin,"##sqlinjectionP##","$sql = \"SELECT * FROM usuarios WHERE usuario = '$usuario' AND contrasena = '$contrasena'\"; /*") || !modificarLinea(rutalogin,"##sqlinjectionF##","*/\n$result = $pdo->query($sql);\nif ($result && $result->fetchColumn() > 0) {")){
        printf("ERROR: no se ha podido generar la vulnerabilidad de login.");
        return false;
    }
    return true;
}

bool crearVulnerabilidadLogin(const char *nombreMaquina){
    int tipoVuln = rand() % 2;
    nuevaLineaEnWriteUp("1. Vulnerabilidad en el login: \n\n",nombreMaquina);
    if (tipoVuln == 0){
        //Vulnerabilidad con usuario y password relajado
        nuevaVulnEnWriteUp("l-relajados",nombreMaquina);
        return usypassRelajado(nombreMaquina);
    }else {
        //Vulnerabilidad con sqlinjection
        nuevaVulnEnWriteUp("l-sqli",nombreMaquina);
        return sqlInjection(nombreMaquina);
    }
}

bool crearVulnerabilidadElevacion(const char *nombreMaquina){
    int tipoVuln = rand() % 2;
    nuevaLineaEnWriteUp("\n\n3. Vulnerabilidad para la elevación: \n\n",nombreMaquina);
    if (tipoVuln == 0){
        //Vulnerabilidad con SUID
        nuevaVulnEnWriteUp("p-suid",nombreMaquina);
        return crearSuid(nombreMaquina);
    }else {
        //Vulnerabilidad con Sudo
        nuevaVulnEnWriteUp("p-sudo",nombreMaquina);
        return crearSudo(nombreMaquina);
    }
}

bool crearVulnerabilidadEjecucion(const char *nombreMaquina){
    int tipoVuln = rand() % 2;
    nuevaLineaEnWriteUp("\n\n2. Vulnerabilidad de ejecución de comandos: \n\n",nombreMaquina);
    if (tipoVuln == 0){
        //Vulnerabilidad con SUID
        return crearSuid(nombreMaquina);
    }else {
        //Vulnerabilidad con Sudo
        return crearSudo(nombreMaquina);
    }
}

//Crear write-Up

bool nuevaLineaEnWriteUp(const char* linea, const char *nombreMaquina) {

    char rutaWrite[100];
    sprintf(rutaWrite, "%s%s/write-up.txt", rutaDockers, nombreMaquina);

    FILE* archivo = fopen(rutaWrite, "a");
    if (archivo == NULL) {
        printf("ERROR: No se pudo abrir el archivo de los write-ups.\n");
        return false;
    }

    fprintf(archivo, linea);
    fclose(archivo);
    return true;
}

bool nuevaVulnEnWriteUp(const char* nombreVuln, const char *nombreMaquina) {

    char rutaWrite[100];
    char rutaVuln[100];
    sprintf(rutaWrite, "%s%s/write-up.txt", rutaDockers, nombreMaquina);

    FILE* archivo = fopen(rutaWrite, "a");
    if (archivo == NULL) {
        printf("ERROR: No se pudo abrir el archivo de los write-ups.\n");
        return false;
    }

    sprintf(rutaVuln, "%s%s.txt", rutaVulnsWriteUp, nombreVuln);

    FILE* archivoEntrada = fopen(rutaVuln, "r");
    if (archivoEntrada == NULL) {
        printf("ERROR: No se pudo abrir el archivo con la explicacion de la vulnerabilidad.\n");
        fclose(archivo);
        return false;
    }

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), archivoEntrada) != NULL) {
        fprintf(archivo, "%s", buffer);
    } 

    fclose(archivoEntrada);
    fclose(archivo);
    return true;
}

//Fin crear write-Up