# Ctf-generator

Ctf-generator es un programa que genera maquinas web con vulnerabilidades aleatorias. Tiene dos finalidades, una es utilizarla para entrenar generando una maquina y obteniendo sus flags. Y la otra consiste en crear las máquinas y almacenarlas para que se puedan crear retos para terceras personas.

## Instalación

Necesitaremos tener instalado y funcionando Docker en nuestra máquina.

Después de descargar el repositorio habrá que otorgar permisos de ejecución a los siguientes archivos:

- /ctf-generator: ejecutable del programa.

- /dockers/altair/start.sh: Archivo que ejecuta la máquina, no siempre es necesario, según el sistema operativo. Primero se debe ejecutar el programa una vez para que aparezca.

- /dockers/altair/stop.sh: Archivo que, para la máquina, no siempre es necesario, según el sistema operativo. Primero se debe ejecutar el programa una vez para que aparezca.

- /dockers/mvulnX/start.sh: Siendo X el número incremental que se ha creado, esta carpeta aparecerá después de crear máquinas con el comando -m.

- /dockers/mvulnX/stop.sh: Siendo X el número incremental que se ha creado, esta carpeta aparecerá después de crear máquinas con el comando -m.

## Ejecución

Ejecutando el archivo ctf-generator obtendremos una máquina a explotar. Con el comando -f ingresaremos las flags para completar la máquina.

También podemos generarlo con -m, así obtendremos varias máquinas que se almacenaran en la carpeta dockers con el nombre mvunX (Siendo X un número incremental). Para ejecutar y parar estas máquinas existen los archivos "start.sh" y stop.sh".

## Uso

Si se ejecuta el comando sin ningún argumento generará una maquina en el puerto 80, siempre y cuando no esté ya creada. El programa tiene los siguientes argumentos:  
    - "-p, --port PUERTO": Especifica el puerto, por defecto 80.  
    - "-f,   --flag FLAG": Sirve para introducir la flag y comprobar que se ha obtenido correctamente, si no se especifica FLAG las muestra.  
    - "-c, --cancel ": Elimina la máquina. Sirve principalmente para rendirse, ya que la maquina se elimina automáticamente cuando obtienes las flags.  
    - "-s, --stop": Para la máquina, pero no la elimina, puedes continuarla.  
    - "-r, --run": Ejecuta la maquina en el caso de estar parada.  
    - "-m, --multi CANTIDAD": Es la segunda funcionalidad del programa, crea el número especificado de máquinas y las almacena en la carpeta "Dockers".  