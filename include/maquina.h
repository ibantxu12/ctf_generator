#define MAQUINA_H
extern int puerto;
/*
    Crea la maquina vulnerable.
*/
bool crearNuevaMaquina(const char *);

/*
    Ejecuta la nueva maquina.
*/
void iniciarNuevaMaquina();

/*
    Establece un pureto a la maquina.
*/
bool establecerPuerto(const char *nombreMaquina);

/*
    Crea las dos claves (user y root) y las añade a la maquina y al archivo de conf.
*/
bool anadirFlags(const char *);

/*
    Cambia la pariencia de la pagina.
*/
bool cambiarEstilo(const char *);

/*
    Elige aleatoriamente un motor de base de datos y asigna usuarios aleatorios.
*/
bool elegirBdd(const char *nombreMaquina);