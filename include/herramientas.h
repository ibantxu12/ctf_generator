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