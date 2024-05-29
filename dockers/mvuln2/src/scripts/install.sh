#!/bin/bash

echo 'ALL ALL=(ALL) NOPASSWD: /usr/bin/timeout' >> /etc/sudoers
apt update
apt install nodejs -y
apt install unzip -y
apt install gnupg curl -y
curl -fsSL https://pgp.mongodb.com/server-7.0.asc | sudo gpg -o /usr/share/keyrings/mongodb-server-7.0.gpg --dearmor
echo "deb [signed-by=/usr/share/keyrings/mongodb-server-7.0.gpg] http://repo.mongodb.org/apt/debian bullseye/mongodb-org/7.0 main" | sudo tee /etc/apt/sources.list.d/mongodb-org-7.0.list
echo "deb http://security.ubuntu.com/ubuntu focal-security main" | sudo tee /etc/apt/sources.list.d/focal-security.list
output=$(apt update 2>&1)
key=$(echo "$output" | grep "NO_PUBKEY" | awk '{print $NF}')
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys $key
apt update
apt install libssl1.1 -y
apt install mongodb-org -y
useradd -m etzio

cd /home
unzip files.zip
mv local-web/ secret

a2enmod proxy
a2enmod proxy_http
archivo_config="/etc/apache2/sites-available/secret.conf"
contenido_config="<VirtualHost *:80>
    ServerName secret.ibc
    DocumentRoot /home/secret

    ProxyPass / http://localhost:3000/
    ProxyPassReverse / http://localhost:3000/
</VirtualHost>"
echo "$contenido_config" | sudo tee "$archivo_config" > /dev/null
a2ensite secret

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


CREATE TABLE usuarios (
	id serial PRIMARY KEY,
	telefono VARCHAR(255),
	hobby VARCHAR(255),
	email VARCHAR(255),
	nacionalidad VARCHAR(255),
	contrasena VARCHAR(255) NOT NULL,
	nivel_educativo VARCHAR(255),
	deporte VARCHAR(255),
	hijos VARCHAR(255),
	usuario VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (telefono, hobby, email, nacionalidad, contrasena, nivel_educativo, deporte, hijos, usuario) VALUES
('611223344', 'pintura', 'pedro@example.com', 'canadiense', 'Chocol@t3.Cafe', 'doctorado', '', '3', 'david'),
('', 'ciclismo', 'juan@example.com', 'austriaco', 'Cam!n0.D3sc@ns0', 'diploma', 'tenis', '7', 'lucia'),
('', 'musica', 'david@example.com', 'canadiense', 'N!ñ0#F3l!c!d@d#L@r3d0', 'bachillerato', 'baloncesto', '9', 'lucia'),
('622394816', 'musica', 'sara@example.com', 'checho', 'D3scubr!r.4v3ntur@_', 'bachillerato', 'ciclismo', '8', 'isabel'),
('689132330', 'ajedrez', 'luis@example.com', 'checho', '2023Mar*Barco', 'doctorado', 'padel', '8', 'elena'),
('657121265', 'futbol', 'pedro@example.com', 'austriaco', 'Mus!ca5*Ba!lar', 'bachillerato', 'ciclismo', '1', 'jorge'),
('689009988', 'lectura', 'david@example.com', 'aleman', 'R10+Sol.Luna', 'licenciatura', 'escalada', '', 'felipe');

-- relajados --
GRANT SELECT ON usuarios TO userweb; 
EOF
