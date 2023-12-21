#define HERRAMIENTAS_H


/*
    Ejecuta un comando en el host y devuelve true si ha funcionado con exito.
*/
bool ejecutarComando(char*);

/*
    Ejecuta un comando y devuelve su salida.
*/
char *devolverTextoComando(char *);

/*
    Comprueba si un comando ejecutado devuelve texto (true) o devuelve una cadena vacia (false).
*/
bool haySalidaComando(char*);

/*
    Recive un nombre de archivo, una cadena a cambiar y la cadena que la remplaza.
    Remplaza la cadena a cambiar por la nueva.
*/
bool modificarLinea(const char *, const char *, const char *);

/*
    Recive un nombre de archivo, una cadena a cambiar y otro archivo para introducir en el primero.
    Remplaza el contenido del segundo archivo por la cadena del primero.
*/
bool modificarLineaFichero(const char *, const char *, const char *);

/*
    Genera una falg con numeros aleatorios.
*/
char *generarFlag();

/*
    Devuleve una linea aleatoria de un archivo dado.
*/
char *lineaAleatoria(const char *);

/*
    Devuelve las flags y si se han conseguido o no.
*/
void verFlags(char *, char *, bool *, bool *);

/*
    Carga datos para los usuarios.
*/
bool cargarDatosDesdeArchivo(const char *);

/*
    Obtiene categoria aleatorioa.
*/
char* obtenerCategoriaAleatoria();

/*
    Obtiene dato aleatorio de una categoria especificada.
*/
char* obtenerDatoAleatorioDeCategoria(const char *);