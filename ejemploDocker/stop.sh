#!/bin/bash
CONTAINER_NAME="altair"
IMAGE_NAME="altair"

if [ "$(docker ps -q -f name=$CONTAINER_NAME)" ]; then
    docker stop $CONTAINER_NAME
    docker rm $CONTAINER_NAME
    echo "El contenedor $CONTAINER_NAME se ha detenido y eliminado."
else
    echo "El contenedor $CONTAINER_NAME no está en ejecución."
fi

if [ "$(docker images -q $IMAGE_NAME)" ]; then v
    docker rmi $IMAGE_NAME
    echo "La imagen $IMAGE_NAME se ha eliminado."
else
    echo "La imagen $IMAGE_NAME no existe."
fi