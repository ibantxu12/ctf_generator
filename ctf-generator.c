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
void mostrarAyuda();

/*
    Elimina la maquina cuando se ejucata con -c
*/
void cancelarMaquina(bool);

/*
    Para la maquina si esta corriendo con -s
*/
void pararMaquina();

/*
    Ejecuta la maquina si no esta corriendo con -r
*/
void ejecutarMaquina();

/*
    Crea el numero de maquinas que le pase el usuario.
*/
void crearVariasMaquinas(int);

/*
    Devuelve las flags y si se han conseguido o no.
*/
void verFlags(char *, char *, bool *, bool *);

/*
    Muestra por pantalla que flags se han conseguido.
*/
void mostrarObjetivos();

/*
    Verifica si la falg que le llega es correcta y la marca como completada en el archivo correspondiente.
*/
void introduccirFlag(char*);

/*
    Ejecuta un comando en el host y devuelve true si ha funcionado con exito.
*/
bool ejecutarComando(char*);

/*
    Ejecuta un comando y devuelve su salida.
*/
char *devolverTextoComando(char *);

/*
    Comprueba que el host tenga instalado docker y el usuario tenga los permisos necesarios.
*/
bool requisitosCorrectos();

/*
    Comprueba si un comando ejecutado devuelve texto (true) o devuelve una cadena vacia (false).
*/
bool haySalidaComando(char*);

/*
    Comprueba si la maquina esta correindo.
*/
bool maquinaCorriendo();

/*
    Recive un nombre de archivo, una cadena a cambiar y la cadena que la remplaza.
    Remplaza la cadena a cambiar por la nueva.
*/
bool modificarLinea(const char *, const char *, const char *);

/*
    Establece un pureto a la maquina.
*/
bool establecerPuerto(const char *nombreMaquina);

/*
    Genera una falg con numeros aleatorios.
*/
char *generarFlag();

/*
    Crea las dos claves (user y root) y las añade a la maquina y al archivo de conf.
*/
bool anadirFlags(const char *);

/*
    Cambia la pariencia de la pagina.
*/
bool cambiarEstilo(const char *);

/*
    Devuleve una linea aleatoria de un archivo dado.
*/
char *lineaAleatoria(const char *);

/*
    Elige aleatoriamente un motor de base de datos y asigna usuarios aleatorios.
*/
bool elegirBdd(const char *nombreMaquina);

/*
    Crea la vulnerablidad con suid.
*/
bool crearSuid(const char *);

/*
    Crea la vulnerablidad con sudo.
*/
bool crearSudo(const char *);

/*
    Crea la vulnerabilidad con usuario y contraseña relajado.
*/
bool usypassRelajado(const char *);

/*
    Crea la vulnerabilidad con SQL Injection.
*/
bool sqlInjection(const char *);

/*
    crea la vulnerabilidad del login.
*/
bool crearVulnerabilidadLogin(const char *);

/*
    Crea las vunerabilidades de elevacion de privilegios.
*/
bool crearVulnerabilidadElevacion(const char *);

/*
    Crea la maquina vulnerable.
*/
bool crearNuevaMaquina(const char *);

/*
    Ejecuta la nueva maquina.
*/
void iniciarNuevaMaquina();





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

void cancelarMaquina(bool preguntar){
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

void crearVariasMaquinas(int cantidadMaquinas){
    char nombreCarpeta[50];

    for (int i = 1; i <= cantidadMaquinas; i++) {
        snprintf(nombreCarpeta, sizeof(nombreCarpeta), "mvuln%d", i);
        if (crearNuevaMaquina(nombreCarpeta)) {
            printf("Maquina '%s' creada con éxito.\n", nombreCarpeta);
        }else {
            printf("No se pudo crear la maquina '%s'. Deshaciendo... \n", nombreCarpeta);
            cancelarMaquina(false);
        }
        
    }
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

bool ejecutarComando(char *comando){
    int resultado = system(comando);

    if (resultado != 0) {
        return false;
    } else {
        return true;
    }

    printf("El contenedor %s ha sido detenido.\n");
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

bool establecerPuerto(const char *nombreMaquina){
    char rutaStar[200];
    char puertoc[20];
    sprintf(rutaStar,"./dockers/%s/start.sh",nombreMaquina);
    sprintf(puertoc,"%d",puerto);
    return modificarLinea(rutaStar,"##puerto##",puertoc);
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

bool anadirFlags(const char *nombreMaquina){
    char *flagUser = generarFlag();
    char *flagRoot = generarFlag();
    char rutaDockerfile[200];
    char rutaConf[200];
        
    sprintf(rutaDockerfile,"./dockers/%s/Dockerfile",nombreMaquina);
    if (!modificarLinea(rutaDockerfile,"##rootFlag##",flagRoot) || !modificarLinea(rutaDockerfile,"##userFlag##",flagUser)){
        printf("ERROR: Las flags no se han podido añadir. Eliminando la maquina...\n");
        cancelarMaquina(false);
        return false;
    }
    sprintf(rutaConf,"echo '%s,un\n%s,rn\n' > ./dockers/%s/conf/flags",flagUser,flagRoot,nombreMaquina);
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
    sprintf(nombrearchivo, "./dockers/%s/src/webContent/index.html",nombreMaquina);
    return modificarLinea(nombrearchivo,"##estilo##",numeroestilo);
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
    char *lineanueva = malloc(len);
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

bool elegirBdd(const char *nombreMaquina){
    int numbdd = (rand() % 3) + 1;
    int numeroUsuarios = 5; //Numero de usaurios a crear
    char copiarBDD[100];
    char rutalogin[100];
    char usuariosAleatorios[500];
    char rutainstall[100];
    sprintf(copiarBDD,"cp -r ./bddsConf/bdd%d ./dockers/%s/src/scripts",numbdd,nombreMaquina);
    sprintf(rutalogin, "./dockers/%s/src/webContent/login.php", nombreMaquina);
    sprintf(rutainstall, "./dockers/%s/src/scripts/install.sh", nombreMaquina);
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
    sprintf(usuariosAleatorios,"('%s', '%s')",lineaAleatoria("./listas/usuarios.txt"),lineaAleatoria("./listas/contrasenas.txt"));
    for (int i = 0; i < (numeroUsuarios - 1); i++) {
        sprintf(usuariosAleatorios,"%s,\n('%s', '%s')",usuariosAleatorios,lineaAleatoria("./listas/usuarios.txt"),lineaAleatoria("./listas/contrasenas.txt"));
    }
    sprintf(usuariosAleatorios,"%s;",usuariosAleatorios);
    return modificarLinea(rutainstall,"##usuarios##",usuariosAleatorios);
}

bool usypassRelajado(const char *nombreMaquina){
    char anadirUsuario[100];
    char rutainstall[100];
    sprintf(anadirUsuario,"INSERT INTO usuarios (usuario, contrasena) VALUES %s",lineaAleatoria("./listas/usuarioyPass.txt"));
    sprintf(rutainstall, "./dockers/%s/src/scripts/install.sh", nombreMaquina);
    if(!modificarLinea(rutainstall,"-- relajados --",anadirUsuario)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de login.");
        return false;
    }
    return true;
}

bool sqlInjection(const char *nombreMaquina){
    char crearSQLI[100];
    char rutalogin[100];
    sprintf(rutalogin, "./dockers/%s/src/webContent/login.php", nombreMaquina);
    if(!modificarLinea(rutalogin,"##sqlinjectionP##","$sql = \"SELECT * FROM usuarios WHERE usuario = '$usuario' AND contrasena = '$contrasena'\"; /*") || !modificarLinea(rutalogin,"##sqlinjectionF##","*/")){
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

bool crearSuid(const char *nombreMaquina){
    char cambiarPermisos[100];
    char rutainstall[100];
    char *archivoVuln = lineaAleatoria("./listas/suid.txt");
    sprintf(cambiarPermisos,"chmod u+s %s && chmod +x %s",archivoVuln,archivoVuln);
    sprintf(rutainstall, "./dockers/%s/src/scripts/install.sh", nombreMaquina);
    if(!modificarLinea(rutainstall,"##elevacion##",cambiarPermisos)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de escalada.");
        return false;
    }
    return true;
}

bool crearSudo(const char *nombreMaquina){
    char anadirSudoers[100];
    char rutainstall[100];
    sprintf(anadirSudoers,"echo 'ALL ALL=(ALL) NOPASSWD: %s' >> /etc/sudoers",lineaAleatoria("./listas/sudo.txt"));
    sprintf(rutainstall, "./dockers/%s/src/scripts/install.sh", nombreMaquina);
    if(!modificarLinea(rutainstall,"##elevacion##",anadirSudoers)){
        printf("ERROR: no se ha podido generar la vulnerabilidad de escalada.");
        return false;
    }
    return true;
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


bool crearNuevaMaquina(const char *nombreMaquina){
    char copiarMaquina[100]; 
    sprintf(copiarMaquina, "cp -r ./ejemploDocker ./dockers/%s", nombreMaquina, nombreMaquina);
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
    printf("Creadndo la nueva maquina...\n");
    if (ejecutarComando("cd dockers/altair/ && ./start.sh 1>/dev/null 2>/dev/null")){
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