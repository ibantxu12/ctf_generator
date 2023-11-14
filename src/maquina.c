#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../include/maquina.h"
#include "../include/herramientas.h"
#include "../include/vulnerabilidades.h"
#include "../include/argumentos.h"

extern char *rutaDockers;
extern char *rutaEjemploDocker;
extern char *rutaBdds;
extern char *rutaListas;

bool crearNuevaMaquina(const char *nombreMaquina){
    char copiarMaquina[100]; 
    sprintf(copiarMaquina, "cp -r %s %s%s", rutaEjemploDocker, rutaDockers, nombreMaquina);
    if(ejecutarComando(copiarMaquina)){

        if(!establecerNombre(nombreMaquina) || !establecerPuerto(nombreMaquina) || !anadirFlags(nombreMaquina) || !cambiarEstilo(nombreMaquina) || !elegirBdd(nombreMaquina) || !crearVulnerabilidadElevacion(nombreMaquina)){
            return false;
        }
        crearVulnerabilidadLogin(nombreMaquina);
        return true;
    } else {
        return false;
    }
}

void iniciarNuevaMaquina(){
    char ejecutarMaquina[100];
    printf("Creadndo la nueva maquina...\n");
    sprintf(ejecutarMaquina, "cd %saltair/ && ./start.sh 1>/dev/null 2>/dev/null", rutaDockers);
    if (ejecutarComando(ejecutarMaquina)){
        char *puerto = devolverTextoComando("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");                
        if(puerto != NULL){
            printf("La maquina esta corriendo en el puerto %s.\n", puerto);
        }else {
            printf("La maquina no se ha podido ejecutar.\n");
            cancelarMaquina(false);
        }
       
    }else {
        printf("La maquina no se ha podido ejecutar.\n");
        cancelarMaquina(false);
    }
}

bool establecerPuerto(const char *nombreMaquina){
    char rutaStar[200];
    char puertoc[20];
    sprintf(rutaStar,"%s%s/start.sh", rutaDockers,nombreMaquina);
    sprintf(puertoc,"%d",puerto);
    return modificarLinea(rutaStar,"##puerto##",puertoc);
}

bool establecerNombre(const char *nombreMaquina){
    char rutaStar[200];
    char rutaStop[200];
    sprintf(rutaStar,"%s%s/start.sh", rutaDockers,nombreMaquina);
    sprintf(rutaStop,"%s%s/stop.sh", rutaDockers,nombreMaquina);
    return (modificarLinea(rutaStar,"##nombre##",nombreMaquina) && modificarLinea(rutaStop,"##nombre##",nombreMaquina)) ;
}

bool anadirFlags(const char *nombreMaquina){
    char *flagUser = generarFlag();
    char *flagRoot = generarFlag();
    char rutaDockerfile[200];
    char rutaConf[200];
        
    sprintf(rutaDockerfile,"%s%s/Dockerfile",rutaDockers,nombreMaquina);
    if (!modificarLinea(rutaDockerfile,"##rootFlag##",flagRoot) || !modificarLinea(rutaDockerfile,"##userFlag##",flagUser)){
        printf("ERROR: Las flags no se han podido añadir. Eliminando la maquina...\n");
        cancelarMaquina(false);
        return false;
    }
    sprintf(rutaConf,"echo '%s,un\n%s,rn\n' > %s%s/src/flags",flagUser,flagRoot,rutaDockers,nombreMaquina);
    if(!ejecutarComando(rutaConf)){
        printf("ERROR: Las flags no se han podido añadir. Eliminando la maquina...\n");
        cancelarMaquina(false);
        return false;
    }
    return true;
}

bool cambiarEstilo(const char *nombreMaquina){
    char nombrearchivo[100];
    char numeroestilo[10];
    sprintf(numeroestilo, "%d", (rand() % 5) + 1);
    sprintf(nombrearchivo, "%s%s/src/webContent/index.html",rutaDockers,nombreMaquina);
    return modificarLinea(nombrearchivo,"##estilo##",numeroestilo);
}

bool crearUsuarios(const char *rutainstall,const char *nuevoDato,const char *parteID){
    int MAX_BUFFER_SIZE = 2000;
    char linea[300];
    char listaUsuarios[100];
    char listaContrasenas[100];
    char listaDatos[100];
    char insert[MAX_BUFFER_SIZE];
    int numeroDatos = (rand() % 8) + 2;
    int posicionUsuario = (rand() % numeroDatos);
    int posicionContrasena = (rand() % numeroDatos);
    if (posicionUsuario == posicionContrasena){
        posicionContrasena = posicionUsuario+1;
        if (posicionContrasena >= numeroDatos){
            posicionContrasena = posicionUsuario-1;
        }
    }
    int numeroUsuarios = (rand() % 8) + 2;
    char *categorias[numeroDatos];

    sprintf(listaUsuarios,"%susuarios.txt",rutaListas);
    sprintf(listaContrasenas,"%scontrasenas.txt",rutaListas);
    sprintf(listaDatos,"%sdatos.txt",rutaListas);

    cargarDatosDesdeArchivo(listaDatos);
    sprintf(linea,"echo 'CREATE TABLE usuarios (' >> %s",rutainstall);
    ejecutarComando(linea);
    sprintf(linea,"echo '\tid %s,' >> %s",parteID,rutainstall);
    ejecutarComando(linea);

    for(int i = 0;i < numeroDatos-1; i++){
        if (i == posicionUsuario){
            sprintf(linea,"echo '\tusuario %s NOT NULL,' >> %s",nuevoDato,rutainstall);
            categorias[i] = "usuario";
        }else if (i == posicionContrasena){
            sprintf(linea,"echo '\tcontrasena %s NOT NULL,' >> %s",nuevoDato,rutainstall);
            categorias[i] = "contrasena";
        }else{
            categorias[i] = obtenerCategoriaAleatoria();
            sprintf(linea,"echo '\t%s %s,' >> %s",categorias[i],nuevoDato,rutainstall);
        }
        ejecutarComando(linea);
    }
    if (numeroDatos-1 == posicionUsuario){
        sprintf(linea,"echo '\tusuario %s NOT NULL' >> %s",nuevoDato,rutainstall);
        categorias[numeroDatos-1] = "usuario";
    }else if (numeroDatos-1 == posicionContrasena){
        sprintf(linea,"echo '\tcontrasena %s NOT NULL' >> %s",nuevoDato,rutainstall);
        categorias[numeroDatos-1] = "contrasena";
    }else{
        categorias[numeroDatos-1] = obtenerCategoriaAleatoria();
        sprintf(linea,"echo '\t%s %s' >> %s",categorias[numeroDatos-1],nuevoDato,rutainstall);
    }
    ejecutarComando(linea);
    sprintf(linea,"echo ');\n' >> %s",rutainstall);
    ejecutarComando(linea);

    strcpy(insert,"INSERT INTO usuarios (");
    int numCategorias = sizeof(categorias) / sizeof(categorias[0]);
    for (int i = 0; i < numCategorias; i++) {
        if (i == 0) {
            strcat(insert, categorias[i]);
        } else {
            strcat(insert, ", ");
            strcat(insert, categorias[i]);
        }
    }
    strcat(insert,") VALUES");
    sprintf(linea,"echo '%s' >> %s",insert,rutainstall);
    ejecutarComando(linea);

    cargarDatosDesdeArchivo(listaDatos);
    for (int i = 0; i < numeroUsuarios; i++) {
        strcpy(insert,"(\'");
        for (int j = 0; j < numCategorias; j++) {
            if (j != 0){
                strcat(insert,"\', \'");
            }
            if (j == posicionUsuario){
                strcat(insert,lineaAleatoria(listaUsuarios));
            }else if (j == posicionContrasena){
                strcat(insert,lineaAleatoria(listaContrasenas));
            }else{
                strcat(insert,obtenerDatoAleatorioDeCategoria(categorias[j]));
            }
        }
        if (i == numeroUsuarios-1){
            strcat(insert,"\');\n");
        } else {
            strcat(insert,"\'),");
        }
        sprintf(linea,"echo \"%s\" >> %s",insert,rutainstall);
        ejecutarComando(linea);
    }

    sprintf(linea,"echo '-- relajados --\n-- postgres --\nEOF' >> %s",rutainstall);
    ejecutarComando(linea);
    return true;

}



// Bases de datos
bool configurarMYSQL(const char *rutalogin,const char *rutainstall){
    if(!modificarLinea(rutalogin,"##motorbdd##","\"mysql:host=$host;dbname=$dbname\", $usuario_bd, $contrasena_bd")){
        return false;
    }
    return crearUsuarios(rutainstall,"VARCHAR(255)","INT AUTO_INCREMENT PRIMARY KEY");
}

bool configurarPGSQL(const char *rutalogin,const char *rutainstall){
    if(!modificarLinea(rutalogin,"##motorbdd##","\"pgsql:host=$host;dbname=$dbname\", $usuario_bd, $contrasena_bd") || !crearUsuarios(rutainstall,"VARCHAR(255)","serial PRIMARY KEY")){
        return false;
    }
    return modificarLinea(rutainstall,"-- postgres --","GRANT SELECT ON usuarios TO userweb; ");
}

bool configurarSQLite(const char *rutalogin,const char *rutainstall){
    if(!modificarLinea(rutalogin,"##motorbdd##","\"sqlite:./$dbname.db\"")){
        return false;
    }
    return crearUsuarios(rutainstall,"TEXT","INTEGER PRIMARY KEY");
}

bool elegirBdd(const char *nombreMaquina){
    int numbdd = (rand() % 3) + 1;
    char copiarBDD[100];
    char rutalogin[100];
    char rutainstall[100];


    sprintf(copiarBDD,"cp -r %sbdd%d %s%s/src/scripts",rutaBdds,numbdd,rutaDockers,nombreMaquina);
    sprintf(rutalogin, "%s%s/src/webContent/login.php",rutaDockers, nombreMaquina);
    sprintf(rutainstall, "%s%s/src/scripts/install.sh",rutaDockers, nombreMaquina);

    if(!ejecutarComando(copiarBDD)){
        printf("ERROR: no se ha podido generar la base de datos");
        return false;
    }
    if (numbdd == 1){
        return configurarMYSQL(rutalogin,rutainstall);
    }else if (numbdd == 2) {
        return configurarPGSQL(rutalogin,rutainstall);
    } else {
        return configurarSQLite(rutalogin,rutainstall);
    }
}
// Fin bases de datos