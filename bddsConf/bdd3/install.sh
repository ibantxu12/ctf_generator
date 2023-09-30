#!/bin/bash

##elevacion##


## script para instalacion de sqlite

sudo apt -y update
apt -y install sqlite3 php-sqlite3

sqlite3 /var/www/html/loginweb.db <<EOF

CREATE TABLE usuarios (
    id INTEGER PRIMARY KEY,
    usuario TEXT NOT NULL,
    contrasena TEXT NOT NULL
);

INSERT INTO usuarios (usuario, contrasena) VALUES
##usuarios##

-- relajados --

EOF