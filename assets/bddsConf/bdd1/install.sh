#!/bin/bash

##elevacion##

## script para instalacion de mariaDB

sudo apt -y update
apt -y install mariadb-server mariadb-client php-mysql
service mariadb start

mysql -u root <<EOF
ALTER USER 'root'@'localhost' IDENTIFIED BY 'almendraextintor1';
CREATE DATABASE loginweb;
USE loginweb;

CREATE TABLE usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    usuario VARCHAR(255) NOT NULL,
    contrasena VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (usuario, contrasena) VALUES
##usuarios##

-- relajados --

CREATE USER 'userweb'@'localhost' IDENTIFIED BY 'userWebExtintor';
GRANT SELECT ON loginweb.* TO 'userweb'@'localhost';

FLUSH PRIVILEGES;
EOF