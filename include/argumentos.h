#define ARGUMENTOS_H

/*
    Muestra la ayuda cuando se ejeccuta el programa con -h
*/
void mostrarAyuda();

/*
    Verifica si la falg que le llega es correcta y la marca como completada en el archivo correspondiente.
*/
void introduccirFlag(char*);

/*
    Muestra por pantalla que flags se han conseguido.
*/
void mostrarObjetivos();

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
    Comprueba que el host tenga instalado docker y el usuario tenga los permisos necesarios.
*/
bool requisitosCorrectos();

/*
    Comprueba si la maquina esta correindo.
*/
bool maquinaCorriendo();

/*
    Crea el numero de maquinas que le pase el usuario.
*/
void crearVariasMaquinas(int);

