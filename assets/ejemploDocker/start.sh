#!/bin/bash
CONTAINER_NAME="altair"
IMAGE_NAME="altair"

if [ "$(docker images -q $IMAGE_NAME)" ]; then
    echo "La imagen $IMAGE_NAME ya existe."
else
    docker build -t $IMAGE_NAME .
    echo "La imagen $IMAGE_NAME se ha construido."
fi

if [ "$(docker ps -q -f name=$CONTAINER_NAME)" ]; then
    echo "El contenedor $CONTAINER_NAME ya está en ejecución."
else
    docker run -d --name $CONTAINER_NAME -p ##puerto##:80 $IMAGE_NAME
    echo "El contenedor $CONTAINER_NAME se ha iniciado."
fi
