#!/bin/bash
## script para instalacion de postgresql

sudo apt -y update
apt -y install postgresql postgresql-contrib libpq-dev php-pgsql
service postgresql start

sudo -u postgres psql <<EOF
ALTER USER postgres PASSWORD 'almendraextintor1';

CREATE DATABASE loginweb;
\c loginweb

CREATE TABLE usuarios (
    id serial PRIMARY KEY,
    usuario VARCHAR(255) NOT NULL,
    contrasena VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (usuario, contrasena) VALUES
##usuarios##

CREATE USER userweb WITH PASSWORD 'userWebExtintor';
GRANT CONNECT ON DATABASE loginweb TO userweb;
GRANT SELECT ON usuarios TO userweb;

EOF