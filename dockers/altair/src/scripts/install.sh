#!/bin/bash

echo 'ALL ALL=(ALL) NOPASSWD: /usr/bin/dd' >> /etc/sudoers
##ejecucion##

## script para instalacion de mariaDB

sudo apt -y update
apt -y install mariadb-server mariadb-client php-mysql
service mariadb start

mysql -u root <<EOF
ALTER USER 'root'@'localhost' IDENTIFIED BY 'almendraextintor1';
CREATE DATABASE loginweb;
USE loginweb;

CREATE USER 'userweb'@'localhost' IDENTIFIED BY 'userWebExtintor';
GRANT SELECT ON loginweb.* TO 'userweb'@'localhost';

FLUSH PRIVILEGES;


CREATE TABLE usuarios (
	id INT AUTO_INCREMENT PRIMARY KEY,
	direccion VARCHAR(255),
	usuario VARCHAR(255) NOT NULL,
	ciudad VARCHAR(255),
	contrasena VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (direccion, usuario, ciudad, contrasena) VALUES
('valencia', 'lucia', 'londres', 'Aventura#V!aj3s'),
('alicante', 'ismael', 'londres', 'S0l3dad@Pl3n!tud4');

INSERT INTO usuarios (usuario, contrasena) VALUES ('mcUser', 'medocheck123');
-- postgres --
EOF
