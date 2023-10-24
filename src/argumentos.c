#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../include/argumentos.h"
#include "../include/herramientas.h"
#include "../include/maquina.h"

extern char *archConf;

void mostrarAyuda() {
    printf("Uso: ctf-generator [OPCION]\n");
    printf("Opciones:\n");
    printf("  -p, --port PUERTO      Especifica el puerto, por defecto 80\n");
    printf("  -h, --help             Muestra esta ayuda\n");
    printf("  -f, --flag FLAG        Introducir flag, si no se especifica FLAG las muestra\n");
    printf("  -c, --cancel           Canela la maquina 'lo que implica rendirse'\n");
    printf("  -s, --stop             Para la maquina, pero no la elimina\n");
    printf("  -r, --run              Ejecuta la maquina en el caso de estar parada\n");
    printf("  -m, --multi CANTIDAD   Crea el numero de maquinas especificado y las guarda en la carpeta dockers\n");
}

void introduccirFlag(char *flag){
    char userFlag[40];
    char rootFlag[40];
    bool userFlagConseguida;
    bool rootFlagConseguida;
    verFlags(userFlag,rootFlag,&userFlagConseguida,&rootFlagConseguida);
    if (userFlagConseguida && rootFlagConseguida){
        printf("Ya has conseguido todas las flags de esta maquina, no hace falta seguir intentandolo.\n");
    } else {
        if (strcmp(userFlag,flag) == 0){
            printf("Enhorabuena!! Has conseguido la flag de User.\n");
            userFlagConseguida = true;
            modificarLinea(archConf,",un",",us");
        } else if (strcmp(rootFlag,flag) == 0) {
            printf("Enhorabuena!! Has conseguido la flag de Root.\n");
            rootFlagConseguida = true;
            modificarLinea(archConf,",rn",",rs");
        } else {
            printf("Lamentablemente esto no es una flag valida, sigue intentadolo.\n");
        }
        if (userFlagConseguida && rootFlagConseguida){
            printf("\nMaquina completada!!!!!! Buen trabajo.\n");
            cancelarMaquina(false);
        } else {
            mostrarObjetivos();
        }
    }
}

void mostrarObjetivos(){
    char userFlag[40];
    char rootFlag[40];
    bool userFlagConseguida;
    bool rootFlagConseguida;
    verFlags(userFlag,rootFlag,&userFlagConseguida,&rootFlagConseguida);

    printf("\nObjetivos: \n");
    printf("Flag de Usuario Conseguida: %s\n", userFlagConseguida ? "Sí" : "No");
    printf("Flag de Root Conseguida: %s\n\n", rootFlagConseguida ? "Sí" : "No");

}

void cancelarMaquina(bool preguntar){
    char respuesta[2];
    bool continuar;

    if (preguntar){
        printf("¿Seguro que quiere eliminar la maquina? [y/n]: ");
        scanf("%1s",respuesta);
        continuar = (*respuesta == 'Y' || *respuesta == 'y');
    } else {
        continuar = true;
    }
    if(continuar){
        char * cancelar = "docker stop altair 1>/dev/null 2>/dev/null && docker rm altair && docker rmi altair 1>/dev/null 2>/dev/null";
        ejecutarComando("rm -r ./dockers/altair 2>/dev/null");

        if(ejecutarComando(cancelar) && preguntar){
            printf("La maquina se ha eiminado correctamente.\n");
        } else if(preguntar){
            printf("La maquina no se ha podido eliminar, pronbablamente no existia.\n");
        }
        
    } else {
        printf("Abortado\n");
    }
    
}

void pararMaquina(){
    char * parar = "docker stop altair 1>/dev/null 2>/dev/null";
    if(ejecutarComando(parar)){
        printf("La maquina se ha parado correctamente.\n");
    } else {
        printf("La maquina no se ha podido parar, pronbablamente no existia\n");
    }
}

void ejecutarMaquina(){
    char *ejecutar = "docker start altair 1>/dev/null 2>/dev/null";
    if(ejecutarComando(ejecutar)){
        char *puerto = devolverTextoComando("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("La maquina esta corriendo en el puerto %s.\n", puerto);
    } else {
        printf("La maquina no se ha podido ejecutar, pronbablamente no existia\n");
    }
}

bool requisitosCorrectos(){
    int estado;
    char *comando = "docker info 1>/dev/null 2>/dev/null";
    estado = system(comando);

    if (estado != 0) {
        printf("Error: El programa no se puede ejecutar, puede que docker no este instalado o el usuario no tenga los permisos correctos. \n");
        printf("Verifique que docker esté instalado, si es así, pruebe a ejecutar el comando con permisos de sperusuario. \n");
        return false;
    }else {
        return true;
    }
}

bool maquinaCorriendo(){
    char *dockerPS = "docker ps | grep altair";

    if(haySalidaComando(dockerPS)){
        char *puerto = devolverTextoComando("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("Ya hay una maquina corriendo incompleta en el puerto %s.\n", puerto);
        mostrarObjetivos();
        return true;
    }else {
        char *dockerPSla = "docker ps -la | grep altair";
        if(haySalidaComando(dockerPSla)){
            printf ("Hay una maquina incompleta que no esta corriendo.\n");
            printf ("Puede volver a lanzarla con '-r' o cancelarla con '-c'.\n");
            return true;
        } else {
            return false;
        }
    }
}

void crearVariasMaquinas(int cantidadMaquinas){
    char nombreCarpeta[50];

    for (int i = 1; i <= cantidadMaquinas; i++) {
        puerto = 80 + i;
        snprintf(nombreCarpeta, sizeof(nombreCarpeta), "mvuln%d", i);
        if (crearNuevaMaquina(nombreCarpeta)) {
            printf("Maquina '%s' creada con éxito.\n", nombreCarpeta);
        }else {
            printf("No se pudo crear la maquina '%s'. Deshaciendo... \n", nombreCarpeta);
            cancelarMaquina(false);
        }
        
    }
}