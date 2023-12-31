#define MAQUINA_H


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
bool establecerPuerto(const char *);

/*
    Establece nombre de la maquina.
*/
bool establecerNombre(const char *);

/*
    Crea las dos claves (user y root) y las añade a la maquina y al archivo de conf.
*/
bool anadirFlags(const char *);

/*
    Cambia la pariencia de la pagina.
*/
bool cambiarEstilo(const char *);

/*
    Modifica el archivo para añadir los nuevos usuarios.
*/
bool crearUsuarios(const char *,const char *,const char *);

/*
    Configura lo necesario para el funcionamiento de MYSQL.
*/
bool configurarMYSQL(const char *,const char *);

/*
    Configura lo necesario para el funcionamiento de PGSQL.
*/
bool configurarPGSQL(const char *,const char *);

/*
    Configura lo necesario para el funcionamiento de SQLite.
*/
bool configurarSQLite(const char *,const char *);

/*
    Elige aleatoriamente un motor de base de datos y asigna usuarios aleatorios.
*/
bool elegirBdd(const char *);

/*
    Crea el encabezado aleatorio.
*/
bool generarEncabezado(const char *);

/*
    Crea el menú aleatorio.
*/
bool generarMenu(const char *);

/*
    Crea el contenido aleatorio.
*/
bool generarContenido(const char *);

/*
    Crea el pie aleatorio.
*/
bool generarPie(const char *);

/*
    Llama a las funciones que crean el inicio.
*/
bool crearEstructuraInicio(const char *);

/*
    Cambia el estilo del inicio.
*/
bool cambiarEstiloInicio(const char *nombreMaquina);
