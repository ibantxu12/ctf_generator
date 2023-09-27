// Autor: Iban Ruiz de Galarreta

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
int puerto = 80;
char *archConf = "./dockers/altair/conf/flags";

/*
    Muestra la ayuda cuando se ejeccuta el programa con -h
*/
void mostrar_ayuda();

/*
    Elimina la maquina cuando se ejucata con -c
*/
void cancelar_maquina(bool);

/*
    Para la maquina si esta corriendo con -s
*/
void parar_maquina();

/*
    Ejecuta la maquina si no esta corriendo con -r
*/
void ejecutar_maquina();

/*
    Devuelve las flags y si se han conseguido o no.
*/
void ver_flags_y_consegidas(char *, char *, bool *, bool *);

/*
    Muestra por pantalla que flags se han conseguido.
*/
void mostrar_objetivos();

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
    Recive un nombre de archivo, una cadena a cambiar y la cadena que la remplaza.
    Remplaza la cadena a cambiar por la nueva.
*/
void modificar_linea(const char *, const char *, const char *);

/*
    Establece un pureto a la maquina.
*/
void establecer_puerto(const char *nombreMaquina);

/*
    Genera una falg con numeros aleatorios.
*/
char *generar_flag();

/*
    Crea las dos claves (user y root) y las añade a la maquina y al archivo de conf.
*/
void anadir_flags(const char *);

/*
    Cambia la pariencia de la pagina.
*/
void cambiar_estilo(const char *);

/*
    Devuleve una linea aleatoria de un archivo dado.
*/
char *lineaAleatoria(const char *);

/*
    Crea la vulnerablidad con suid.
*/
void crear_suid();

/*
    Crea la vulnerablidad con sudo.
*/
void crear_sudo();

/*
    Crea las vunerabilidades de elevacion de privilegios.
*/
void crear_vulnerabilidad_elevacion();

/*
    Crea la maquina vulnerable.
*/
void crear_nueva_maquina(const char *);

/*
    Ejecuta la nueva maquina.
*/
void iniciar_nueva_maquina();





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
                mostrar_objetivos();
                return 0;
            }
        
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cancel") == 0) {
            cancelar_maquina(true);
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
        crear_nueva_maquina("altair");
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
    printf("  -f, --flag FLAG      Introducir flag, si no se especifica FLAG las muestra.\n");
    printf("  -c, --cancel         Canela la maquina 'lo que implica rendirse'\n");
    printf("  -s, --stop           Para la maquina, pero no la elimina\n");
    printf("  -r, --run            Ejecuta la maquina en el caso de estar parada\n");
}

void cancelar_maquina(bool preguntar){
    char *respuesta;
    bool continuar;

    if (preguntar){
        printf("¿Seguro que quiere eliminar la maquina? [y/n]: ");
        scanf("%s",respuesta);
        continuar = (*respuesta == 'Y' || *respuesta == 'y');
    } else {
        continuar = true;
    }
    if(continuar){
        char * cancelar = "docker stop altair 1>/dev/null 2>/dev/null && docker rm altair && docker rmi altair 1>/dev/null 2>/dev/null";
        ejecutar_comando_simple("rm -r ./dockers/altair 2>/dev/null");
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

void ver_flags_y_consegidas(char *userFlag, char *rootFlag, bool *userFlagConseguida, bool *rootFlagConseguida){
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

void mostrar_objetivos(){
    char userFlag[40];
    char rootFlag[40];
    bool userFlagConseguida;
    bool rootFlagConseguida;
    ver_flags_y_consegidas(userFlag,rootFlag,&userFlagConseguida,&rootFlagConseguida);

    printf("\nObjetivos: \n");
    printf("Flag de Usuario Conseguida: %s\n", userFlagConseguida ? "Sí" : "No");
    printf("Flag de Root Conseguida: %s\n\n", rootFlagConseguida ? "Sí" : "No");

}

void introduccir_flag(char *flag){
    char userFlag[40];
    char rootFlag[40];
    bool userFlagConseguida;
    bool rootFlagConseguida;
    ver_flags_y_consegidas(userFlag,rootFlag,&userFlagConseguida,&rootFlagConseguida);
    if (userFlagConseguida && rootFlagConseguida){
        printf("Ya has conseguido todas las flags de esta maquina, no hace falta seguir intentandolo.\n");
    } else {
        if (strcmp(userFlag,flag) == 0){
            printf("Enhorabuena!! Has conseguido la flag de User.\n");
            userFlagConseguida = true;
            modificar_linea(archConf,",un",",us");
        } else if (strcmp(rootFlag,flag) == 0) {
            printf("Enhorabuena!! Has conseguido la flag de Root.\n");
            rootFlagConseguida = true;
            modificar_linea(archConf,",rn",",rs");
        } else {
            printf("Lamentablemente esto no es una flag valida, sigue intentadolo.\n");
        }
        if (userFlagConseguida && rootFlagConseguida){
            printf("\nMaquina completada!!!!!! Buen trabajo.\n");
            cancelar_maquina(false);
        } else {
            mostrar_objetivos();
        }
    }
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

bool maquina_corriendo(){
    char *dockerPS = "docker ps | grep altair";

    if(hay_salida_comando(dockerPS)){
        char *puerto = comando_devolver_texto("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");
        printf("Ya hay una maquina corriendo incompleta en el puerto %s.\n", puerto);
        mostrar_objetivos();
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

void modificar_linea(const char *archivo, const char *busqueda, const char *reemplazo){
    FILE *entrada = fopen(archivo, "r");
    if (entrada == NULL) {
        printf("ERROR: No se ha podido abrir el archivo en modo lectura\n");
        return;
    }

    FILE *salida = fopen("temp.txt", "w");
    if (salida == NULL) {
        printf("ERROR: No se ha podido abrir el archivo temporal en modo escritura\n");
        fclose(entrada);
        return;
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
}

void establecer_puerto(const char *nombreMaquina){
    char rutaStar[200];
    char puertoc[20];
    sprintf(rutaStar,"./dockers/%s/start.sh",nombreMaquina);
    sprintf(puertoc,"%d",puerto);
    modificar_linea(rutaStar,"##puerto##",puertoc);
}

char *generar_flag(){
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

void anadir_flags(const char *nombreMaquina){
    char *flagUser = generar_flag();
    char *flagRoot = generar_flag();
    char rutaDockerfile[200];
    char rutaConf[200];
        
    sprintf(rutaDockerfile,"./dockers/%s/Dockerfile",nombreMaquina);
    modificar_linea(rutaDockerfile,"##rootFlag##",flagRoot);
    modificar_linea(rutaDockerfile,"##userFlag##",flagUser);
    sprintf(rutaConf,"echo '%s,un\n%s,rn\n' > ./dockers/%s/conf/flags",flagUser,flagRoot,nombreMaquina);
    if(!ejecutar_comando_simple(rutaConf)){
        printf("ERROR: Las flags no se han podido añadir. Eliminando la maquina...\n");
        cancelar_maquina(false);
        return;
    }
}

void cambiar_estilo(const char *nombreMaquina){
    char nombrearchivo[100];
    char numeroestilo[10];
    sprintf(numeroestilo, "%d", (rand() % 5) + 1);
    sprintf(nombrearchivo, "./dockers/%s/src/webContent/index.html",nombreMaquina);
    modificar_linea(nombrearchivo,"##estilo##",numeroestilo);
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

    int lineaAleatoria = rand() % numLineas;
    rewind(archivo);

    int lineaActual = 0;
    char *linea = NULL;
    size_t longitud = 0;
    while (lineaActual < lineaAleatoria && getline(&linea, &longitud, archivo) != -1) {
        lineaActual++;
    }

    fclose(archivo);
    return linea;
}

void crear_suid(){
    char comandoSuid[100];
    sprintf(comandoSuid,"docker exec -it altair chmod u+s %s",lineaAleatoria("gtfobins/suidRutas.txt"));
    if(!ejecutar_comando_simple(comandoSuid)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de escalada.");
        return;
    }
}

void crear_sudo(){
    return;
}

void crear_vulnerabilidad_elevacion(){
    int tipoVuln = rand() % 2;
    tipoVuln = 0; //eliminar
    if (tipoVuln == 0){
        //Vulnerabilidad con SUID
        crear_suid();
    }else {
        //Vulnerabilidad con Sudo
        
    }
}


void crear_nueva_maquina(const char *nombreMaquina){
    char copiarMaquina[100]; 
    sprintf(copiarMaquina, "cp -r ./ejemploDocker ./dockers/%s", nombreMaquina);
    if(ejecutar_comando_simple(copiarMaquina)){
        establecer_puerto(nombreMaquina);
        anadir_flags(nombreMaquina);
        cambiar_estilo(nombreMaquina);
        //crear_vulnerabilidad_elevacion();
    } else {
        printf("La maquina no se ha podido crear.\n");
        cancelar_maquina(false);
    }
}

void iniciar_nueva_maquina(){
    printf("Creadndo la nueva maquina...\n");
    if (ejecutar_comando_simple("cd dockers/altair/ && ./start.sh 1>/dev/null 2/dev/null")){
        char *puerto = comando_devolver_texto("docker port altair | grep -m 1 -oP '(?<=:)[0-9]+'");                
        printf("La maquina esta corriendo en el puerto %s.\n", puerto);
    }else {
        printf("La maquina no se ha podido crear.\n");
        cancelar_maquina(false);
    }
}