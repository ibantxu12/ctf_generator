#!/bin/bash

echo 'ALL ALL=(ALL) NOPASSWD: /usr/bin/dpkg' >> /etc/sudoers
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
	usuario VARCHAR(255) NOT NULL,
	contrasena VARCHAR(255) NOT NULL,
	ingresos_anuales VARCHAR(255)
);

INSERT INTO usuarios (usuario, contrasena, ingresos_anuales) VALUES
('javier', 'C!ud@d^Exp!or@r', '105000'),
('teresa', '456B@!l@r^Mús!c@', '45000'),
('martina', 'T3mp0@P3rf3ct0', '25000'),
('javier', 'Aventura#V!aj3s', '35000'),
('pedro', '7Feliz*Dia8', '95000');

INSERT INTO usuarios (usuario, contrasena) VALUES ('root', 'vagrant');
-- postgres --
EOF
