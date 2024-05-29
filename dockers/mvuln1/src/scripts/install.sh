#!/bin/bash

echo 'ALL ALL=(ALL) NOPASSWD: /usr/bin/su' >> /etc/sudoers
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
	telefono VARCHAR(255),
	usuario VARCHAR(255) NOT NULL,
	ciudad VARCHAR(255),
	contrasena VARCHAR(255) NOT NULL,
	hobby VARCHAR(255)
);

INSERT INTO usuarios (telefono, usuario, ciudad, contrasena, hobby) VALUES
('', 'luis', 'berlin', 'C@l!3#P@s30s', 'futbol'),
('698153440', 'sofia', 'londres', 'D3scubr!r.4v3ntur@_', 'pintura'),
('622394816', 'elisa', '', 'S0l3dad@Pl3n!tud4', 'jardineria'),
('672349812', 'antonio', 'nueva york', 'S0l3dad@Pl3n!tud4', 'tenis'),
('689132330', 'emma', 'roma', '123S@ber.Con0c!m!3nt0', 'musica'),
('689132330', 'jose', 'berlin', '5V!@j3s^Mund!@l', 'futbol'),
('689009988', 'lourdes', 'amsterdam', '2023M!3d!t@c!ón', 'futbol');

INSERT INTO usuarios (usuario, contrasena) VALUES ('moves', 'moves');
GRANT SELECT ON usuarios TO userweb; 
EOF
CREATE TABLE usuarios (
	id serial PRIMARY KEY,
	direccion VARCHAR(255),
	contrasena VARCHAR(255) NOT NULL,
	musica VARCHAR(255),
	usuario VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (direccion, contrasena, musica, usuario) VALUES
('pamplona', 'C!ud@d^Exp!or@r', 'clásica', 'lorena'),
('madrid', 'F3l!c!d@d.T!3mp0', 'folk', 'clara'),
('pamplona', 'P!zza.H3lad0@', 'hip-hop', 'carlos');

INSERT INTO usuarios (usuario, contrasena) VALUES ('root', '123qweASD#');
GRANT SELECT ON usuarios TO userweb; 
EOF
