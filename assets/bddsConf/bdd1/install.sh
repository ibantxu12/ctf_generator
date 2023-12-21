#!/bin/bash

##elevacion##
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


