#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "../include/herramientas.h"
#include "../include/maquina.h"
#include "../include/argumentos.h"

char *rutaDockers = "./dockers/";
char *archConf = "./dockers/altair/src/flags";
char *rutaEjemploDocker = "./assets/ejemploDocker/";
char *rutaBdds = "./assets/bddsConf/";
char *rutaListas = "./assets/listas/";
char *rutaOtros = "./assets/otros/";
char *rutaVulnsWriteUp = "./doc/vulns/";
int puerto = 80;

/*
======================================================================
Proyecto: ctf-generator
Descripción: Generador automático de maquinas vulnerables para CTFs
Autor: Iban Ruiz de Galarreta Cadenas
Fecha de creación: 10/09/2023
======================================================================
*/
int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc > 3 || (argc == 3 && argv[2][0] == '-')) {
        printf("Error: Se requiere como mucho una opcion.\n");
        mostrarAyuda();
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc) {
                puerto = atoi(argv[i + 1]);
                i++;
            } else {
                printf("Error: Se esperaba un valor de puerto después de %s\n", argv[i]);
                return 1;
            }
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            mostrarAyuda();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--flag") == 0) {
            if (i + 1 < argc) {
                char *flag = argv[i + 1];
                introduccirFlag(flag);
                return 0;
            } else {
                mostrarObjetivos();
                return 0;
            }
        
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cancel") == 0) {
            cancelarMaquina(true);
            return 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--stop") == 0) {
            pararMaquina();
            return 1;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--run") == 0) {
            ejecutarMaquina();
            return 1;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--multi") == 0){
            if (i + 1 < argc) {
                crearVariasMaquinas(atoi(argv[i + 1]));
                return 1;
            } else {
                printf("Error: Se esperaba la cantidad de maquina a crear después de %s\n", argv[i]);
                return 1;
            }
        }else {
            printf("Error: Opción no válida: %s\n", argv[i]);
            return 1;
        }
    }

    if(requisitosCorrectos() && !maquinaCorriendo()){
        if(!crearNuevaMaquina("altair")){
            printf("No se pudo crear la maquina. Deshaciendo... \n");
            cancelarMaquina(false);
            return 1;
        }
        iniciarNuevaMaquina();
    } else {
        return 1;
    }
 
    return 0;
}