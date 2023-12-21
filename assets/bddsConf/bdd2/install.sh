#!/bin/bash

##elevacion##
##ejecucion##

## script para instalacion de postgresql

sudo apt -y update
apt -y install postgresql postgresql-contrib libpq-dev php-pgsql
service postgresql start

sudo -u postgres psql <<EOF
ALTER USER postgres PASSWORD 'almendraextintor1';

CREATE DATABASE loginweb;
\c loginweb

CREATE USER userweb WITH PASSWORD 'userWebExtintor';
GRANT CONNECT ON DATABASE loginweb TO userweb;


