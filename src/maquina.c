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

        if(!establecerPuerto(nombreMaquina) || !anadirFlags(nombreMaquina) || !cambiarEstilo(nombreMaquina) || !elegirBdd(nombreMaquina) || !crearVulnerabilidadElevacion(nombreMaquina)){
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

bool elegirBdd(const char *nombreMaquina){
    int numbdd = (rand() % 3) + 1;
    int numeroUsuarios = 5; //Numero de usaurios a crear
    int MAX_BUFFER_SIZE = 1000;
    char copiarBDD[100];
    char rutalogin[100];
    char rutainstall[100];
    char listaUsuarios[100];
    char listaContrasenas[100];

    char usuariosAleatorios[MAX_BUFFER_SIZE];
    char tempBuffer[MAX_BUFFER_SIZE];

    sprintf(listaUsuarios,"%susuarios.txt",rutaListas);
    sprintf(listaContrasenas,"%scontrasenas.txt",rutaListas);
    sprintf(copiarBDD,"cp -r %sbdd%d %s%s/src/scripts",rutaBdds,numbdd,rutaDockers,nombreMaquina);
    sprintf(rutalogin, "%s%s/src/webContent/login.php",rutaDockers, nombreMaquina);
    sprintf(rutainstall, "%s%s/src/scripts/install.sh",rutaDockers, nombreMaquina);

    if(!ejecutarComando(copiarBDD)){
        printf("ERROR: no se ha podido generar la base de datos");
        return false;
    }
    if (numbdd == 1){
        if(!modificarLinea(rutalogin,"##motorbdd##","\"mysql:host=$host;dbname=$dbname\", $usuario_bd, $contrasena_bd")){
            return false;
        }
    }else if (numbdd == 2) {
        if(!modificarLinea(rutalogin,"##motorbdd##","\"pgsql:host=$host;dbname=$dbname\", $usuario_bd, $contrasena_bd")){
            return false;
        }
    } else {
        if(!modificarLinea(rutalogin,"##motorbdd##","\"sqlite:./$dbname.db\"")){
            return false;
        }
    }

    // tempBuffer[0] = '\0';
    snprintf(tempBuffer,MAX_BUFFER_SIZE,"('%s', '%s')",lineaAleatoria(listaUsuarios),lineaAleatoria(listaContrasenas));
    for (int i = 0; i < (numeroUsuarios - 1); i++) {
        char temp[MAX_BUFFER_SIZE];
        snprintf(temp,MAX_BUFFER_SIZE,",\n('%s', '%s')",lineaAleatoria(listaUsuarios),lineaAleatoria(listaContrasenas));
        strncat(tempBuffer, temp, MAX_BUFFER_SIZE - strlen(tempBuffer) - 5);
    }
    snprintf(usuariosAleatorios,MAX_BUFFER_SIZE,"%s;",tempBuffer);
    return modificarLinea(rutainstall,"##usuarios##",usuariosAleatorios);
}