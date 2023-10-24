# Ctf-generator

Ctf-generator es un programa que genera maquinas web con vulnerabilidades aleatorias. Tiene dos finalidades, una es utilizarla para entrenar generando una maquina y obteniendo sus flags. Y la otra consiste en crear las máquinas y almacenarlas para que se puedan crear retos para terceras personas.

## Uso

Si se ejecuta el comando sin ningún argumento generará una maquina en el puerto 80, siempre y cuando no esté ya creada. El programa tiene los siguientes argumentos:  
    - "-p, --port PUERTO": Especifica el puerto, por defecto 80.  
    - "-f, --flag FLAG": Sirve para introducir la flag y comprobar que se ha obtenido correctamente, si no se especifica FLAG las muestra.  
    - "-c, --cancel ": Elimina la máquina. Sirve principalmente para rendirse, ya que la maquina se elimina automáticamente cuando obtienes las flags.  
    - "-s, --stop": Para la máquina, pero no la elimina, puedes continuarla.  
    - "-r, --run": Ejecuta la maquina en el caso de estar parada.  
    - "-m, --multi CANTIDAD": Es la segunda funcionalidad del programa, crea el número especificado de máquinas y las almacena en la carpeta "Dockers".  