#!/bin/bash
IMAGE_NAME=mvuln1

if [ "$(docker ps -q -f name=$IMAGE_NAME)" ]; then
    docker stop $IMAGE_NAME
    docker rm $IMAGE_NAME
    echo "El contenedor $IMAGE_NAME se ha detenido y eliminado."
else
    echo "El contenedor $IMAGE_NAME no está en ejecución."
fi

if [ "$(docker images -q $IMAGE_NAME)" ]; then v
    docker rmi $IMAGE_NAME
    echo "La imagen $IMAGE_NAME se ha eliminado."
else
    echo "La imagen $IMAGE_NAME no existe."
fi