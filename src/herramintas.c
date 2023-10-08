#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../include/herramientas.h"
extern char *archConf;


bool ejecutarComando(char *comando){
    int resultado = system(comando);

    if (resultado != 0) {
        return false;
    } else {
        return true;
    }
}

char *devolverTextoComando(char *comando){
    FILE *fp = popen(comando, "r");
    if (fp == NULL) {
        printf("ERROR: El comando no se ha podido ejecutar correctamente.");
        return NULL;
    }

    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        pclose(fp);
        char *newline = strchr(buffer, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        return strdup(buffer);
    } else {
        pclose(fp);
        perror("ERROR: No se ha podido leer la salida del comando");
        return NULL;
    }
}

bool haySalidaComando(char *comando){
    FILE *fp = popen(comando, "r");
    if (fp == NULL) {
        printf("ERROR: El comando no se ha podido ejecutar correctamente.\n");
        return false;
    }

    char buffer[1024];
     
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        pclose(fp);
        if (strlen(buffer) == 0 || buffer[0] == '\n') {
            return false;
        } else {
            return true;
        }
    } else {
        pclose(fp);
        return false;
    }
}

bool modificarLinea(const char *archivo, const char *busqueda, const char *reemplazo){
    FILE *entrada = fopen(archivo, "r");
    if (entrada == NULL) {
        printf("ERROR: No se ha podido abrir el archivo %s en modo lectura\n",archivo);
        return false;
    }

    FILE *salida = fopen("temp.txt", "w");
    if (salida == NULL) {
        printf("ERROR: No se ha podido abrir el archivo temporal en modo escritura\n");
        fclose(entrada);
        return false;
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), entrada) != NULL) {
        char *posicion = strstr(linea, busqueda);
        if (posicion != NULL) {
            fprintf(salida, "%.*s%s%s", (int)(posicion - linea), linea, reemplazo, posicion + strlen(busqueda));
        } else {
            fputs(linea, salida);
        }
    }

    fclose(entrada);
    fclose(salida);

    remove(archivo);
    rename("temp.txt", archivo);
    return true;
}

char *generarFlag(){
    int longitudFlag = 32;
    char *flag = malloc((longitudFlag + 1) * sizeof(char));
    if (flag == NULL) {
        printf("ERROR: No se ha podido asignar memoria");
        return NULL;
    }
    flag[0] = '\0';
    for (int i = 0; i < longitudFlag; i++){
        char caracter;
        int aleatorio = rand() % 36;
        if (aleatorio < 26){
            caracter = 'a' + aleatorio;
        } else {
            caracter = '0' + (aleatorio - 26);
        }
        strncat(flag, &caracter, 1);
    }
    return(flag);
}

char *lineaAleatoria(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("ERROR: No se puede leer el archivo %s\n",nombreArchivo);
        return NULL;
    }

    int numLineas = 0;
    char caracter;
    while ((caracter = fgetc(archivo)) != EOF) {
        if (caracter == '\n') {
            numLineas++;
        }
    }

    int lineaAleatoria = (rand() % numLineas) + 1;
    rewind(archivo);
    int lineaActual = 0;
    char *linea = NULL;
    size_t longitud = 0;
    while (lineaActual < lineaAleatoria && getline(&linea, &longitud, archivo) != -1) {
        lineaActual++;
    }

    fclose(archivo);
    int len = strlen(linea);
    char *lineanueva = malloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (linea[i] != '\n' && linea[i] != '\t' && linea[i] != '\r') {
            lineanueva[j] = linea[i];
            j++;
        }
    }
    lineanueva[j] = '\0';
    return lineanueva;
}

void verFlags(char *userFlag, char *rootFlag, bool *userFlagConseguida, bool *rootFlagConseguida){
    *userFlagConseguida = false;
    *rootFlagConseguida = false;
    
    FILE *archivo = fopen(archConf, "r");
    if (archivo != NULL) {
        if (fscanf(archivo, "%[^,],", userFlag) == 1) {
            char estado[2];
            fscanf(archivo, "%1s", estado);
            if (fscanf(archivo, "%1s\n", estado) == 1) {
                *userFlagConseguida = (estado[0] == 's');
            }
        }

        if (fscanf(archivo, "%[^,],", rootFlag) == 1) {
            char estado[2];
            fscanf(archivo, "%1s", estado);
            if (fscanf(archivo, "%1s\n", estado) == 1) {
                *rootFlagConseguida = (estado[0] == 's');
            }
        }

        fclose(archivo);
    } else {
        printf("ERROR: No se a podido abrir el archivo para lectura.\n");
        return;
    }
}