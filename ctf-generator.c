// Autor: Iban Ruiz de Galarreta

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
int puerto = 80;


/*
    Muestra la ayuda cuando se ejeccuta el programa con -h
*/
void mostrar_ayuda();

/*
    Elimina la maquina cuando se ejucata con -c
*/
void cancelar_maquina();

/*
    Para la maquina si esta corriendo con -s
*/
void parar_maquina();

/*
    Ejecuta la maquina si no esta corriendo con -r
*/
void ejecutar_maquina();

/*
    Verifica si la falg que le llega es correcta y la marca como completada en el archivo correspondiente.
*/
void introduccir_flag(char*);

/*
    Ejecuta un comando en el host y devuelve true si ha funcionado con exito.
*/
bool ejecutar_comando_simple(char*);

/*
    Ejecuta un comando y devuelve su salida.
*/
char *comando_devolver_texto(char *);

/*
    Comprueba que el host tenga instalado docker y el usuario tenga los permisos necesarios.
*/
bool requisitos_correctos();

/*
    Comprueba si un comando ejecutado devuelve texto (true) o devuelve una cadena vacia (false).
*/
bool hay_salida_comando(char*);

/*
    Comprueba si la maquina esta correindo.
*/
bool maquina_corriendo();

/*
    Crea la maquina vulnerable.
*/
void iniciar_nueva_maquina();

/*
    Recive un nombre de archivo, una linea a cambiar y el numero de esa linea.
    Cambia la linea que tenga ese numero por la de la entrada en ese archivo.
*/
void modificar_linea(char *,char *, int);



int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc > 3 || (argc == 3 && argv[2][0] == '-')) {
        printf("Error: Se requiere como mucho una opcion.\n");
        mostrar_ayuda();
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
            mostrar_ayuda();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--flag") == 0) {
            if (i + 1 < argc) {
                char *flag = argv[i + 1];
                introduccir_flag(flag);
                return 0;
            } else {
                printf("Error: Se esperaba un valor de flag después de %s\n", argv[i]);
                return 1;
            }
        
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cancel") == 0) {
            cancelar_maquina();
            return 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--stop") == 0) {
            parar_maquina();
            return 1;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--run") == 0) {
            ejecutar_maquina();
            return 1;
        } else {
            printf("Error: Opción no válida: %s\n", argv[i]);
            return 1;
        }
    }

    if(requisitos_correctos() && !maquina_corriendo()){
        iniciar_nueva_maquina();
    } else {
        return 1;
    }
 
    return 0;
}

void mostrar_ayuda() {
    printf("Uso: mi_programa [OPCION]\n");
    printf("Opciones:\n");
    printf("  -p, --port PUERTO    Especifica el puerto, por defecto 80\n");
    printf("  -h, --help           Muestra esta ayuda\n");
    printf("  -f, --flag FLAG      Introducir flag\n");
    printf("  -c, --cancel         Canela la maquina 'lo que implica rendirse'\n");
    printf("  -s, --stop           Para la maquina, pero no la elimina\n");
    printf("  -r, --run            Ejecuta la maquina en el caso de estar parada\n");
}

void cancelar_maquina(){
    char *respuesta;
    printf("¿Seguro que quieres eliminar la maquina? [y/n]: ");
    scanf("%s",respuesta);
    bool continuar = (*respuesta == 'Y' || *respuesta == 'y');
    if(continuar){
        char * cancelar = "docker stop altair 1>/dev/null 2>/dev/null && docker rm altair 1>/dev/null 2>/dev/null";
        if(ejecutar_comando_simple(cancelar)){
            printf("La maquina se ha eiminado correctamente.\n");
        } else {
            printf("La maquina no se ha podido eliminar, pronbablamente no existia.\n");
        }
    } else {
        printf("Abortado\n");
    }
    
}

void parar_maquina(){
    char * parar = "docker stop altair 1>/dev/null 2>/dev/null";
    if(ejecutar_comando_simple(parar)){
        printf("La maquina se ha parado correctamente.\n");
    } else {
        printf("La maquina no se ha podido parar, pronbablamente no existia\n");
    }
}

void ejecutar_maquina(){
    char *ejecutar = "docker start altair 1>/dev/null 2>/dev/null";
    if(ejecutar_comando_simple(ejecutar)){
        char *puerto = comando_devolver_texto("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("La maquina esta corriendo en el puerto %s.\n", puerto);
    } else {
        printf("La maquina no se ha podido ejecutar, pronbablamente no existia\n");
    }
}

void introduccir_flag(char *flag){
    printf("%s\n",flag);
}

bool ejecutar_comando_simple(char *comando){
    int resultado = system(comando);

    if (resultado != 0) {
        return false;
    } else {
        return true;
    }

    printf("El contenedor %s ha sido detenido.\n");
}

char *comando_devolver_texto(char *comando){
    FILE *fp = popen(comando, "r");
    if (fp == NULL) {
        printf("ERROR: Docker no funciona correctamente.");
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
bool requisitos_correctos(){
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

bool hay_salida_comando(char *comando){
    FILE *fp = popen(comando, "r");
    if (fp == NULL) {
        printf("ERROR: Docker no funciona correctamente.");
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

bool maquina_corriendo(){
    char *dockerPS = "docker ps | grep altair";
    if(hay_salida_comando(dockerPS)){
        char *puerto = comando_devolver_texto("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("Ya hay una maquina corriendo incompleta en el puerto %s.\n", puerto); //programar ver puerto
        printf("Puede cancelarla con la flag '-c' si desea rendirse.\n");
        return true;
    }else {
        char *dockerPSla = "docker ps -la | grep altair";
        if(hay_salida_comando(dockerPSla)){
            printf ("Hay una maquina incompleta que no esta corriendo.\n");
            printf ("Puede volver a lanzarla con '-r' o cancelarla con '-c'.\n");
            return true;
        } else {
            return false;
        }
    }
}

void modificar_linea(char *nombreArchivo,char *lineaNueva, int numeroLinea){
    FILE *archivo = fopen(nombreArchivo, "r+");
    if (archivo == NULL) {
        printf("ERROR: No se puede abrir el archivo %s", nombreArchivo);
        return;
    }
    char buffer[1024];
    int numeroLineaActual = 0;
    long int posicionInicioLinea = 0;
    while (fgets(buffer, sizeof(buffer), archivo)) {
        numeroLineaActual++;
        if (numeroLineaActual == numeroLinea) {
            posicionInicioLinea = ftell(archivo) - strlen(buffer);
            break;
        }
    }

    if (numeroLineaActual != numeroLinea) {
        printf("ERROR: No se encontró la línea especificada.\n");
        fclose(archivo);
        return;
    }

    fseek(archivo, posicionInicioLinea, SEEK_SET);
    fputs(lineaNueva, archivo);
    fclose(archivo);

}



void iniciar_nueva_maquina(){
    printf("Creadndo la nueva maquina...\n");
    char generarAltair[200]; 
    sprintf(generarAltair, "docker run -d --name altair --hostname altair -p %d:80 -e LANG=C.UTF-8 -v $(pwd)/webContent/:/var/www/html ibantxu12/debian_vulnerable /usr/sbin/apachectl -D FOREGROUND", puerto);
    printf("%s\n",generarAltair);
    if(ejecutar_comando_simple(generarAltair)){
        
        // Cambiar estilo pagina
        char nuevalinea[100];
        sprintf(nuevalinea, "    <link rel='stylesheet' href='styles/style%d.css'>",(rand() % 5) + 1);
        modificar_linea("./webContent/index.html",nuevalinea,7);
        // Fin cambiar estilo pagina

        char *puerto = comando_devolver_texto("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("La maquina esta corriendo en el puerto %s.\n", puerto);
    } else {
        printf("La maquina no se ha podido crear.\n");
    }
}