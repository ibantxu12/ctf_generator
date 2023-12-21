#define VULNERABILIDADES_H

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
    Cera la vulnerabilidad de Secret.
*/
bool crearSecret(const char *);

/*
    crea la vulnerabilidad del login.
*/
bool crearVulnerabilidadLogin(const char *);

/*
    Crea las vunerabilidades de elevacion de privilegios.
*/
bool crearVulnerabilidadElevacion(const char *);

/*
    Crea las vunerabilidades de ejecucion de comandos.
*/
bool crearVulnerabilidadEjecucion(const char *nombreMaquina);
/*
    Añade una nueva linea al archivo de Write-Up.
*/
bool nuevaLineaEnWriteUp(const char* , const char *);

/*
    Añade una nueva vulnerabilidad al archivo de Write-Up.
*/
bool nuevaVulnEnWriteUp(const char* , const char *);