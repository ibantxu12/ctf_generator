#!/bin/bash

##elevacion##
##ejecucion##

## script para instalacion de sqlite

sudo apt -y update
apt -y install sqlite3 php-sqlite3

sqlite3 /var/www/html/loginweb.db <<EOF

