#!/bin/bash
IMAGE_NAME=mvuln2
PORT=${1:-82}  # Lee el primer argumento como puerto, o usa 80 por defecto si no se proporciona ninguno.

if [ "$(docker images -q $IMAGE_NAME)" ]; then
    echo "La imagen $IMAGE_NAME ya existe."
else
    docker build -t $IMAGE_NAME .
    echo "La imagen $IMAGE_NAME se ha construido."
fi

if [ "$(docker ps -q -f name=$IMAGE_NAME)" ]; then
    echo "El contenedor $IMAGE_NAME ya está en ejecución."
else
    docker run -d --name $IMAGE_NAME -p $PORT:80 $IMAGE_NAME
    echo "El contenedor $IMAGE_NAME se ha iniciado en el puerto $PORT."
fi
