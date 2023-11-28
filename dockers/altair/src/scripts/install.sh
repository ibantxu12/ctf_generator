#!/bin/bash

echo 'ALL ALL=(ALL) NOPASSWD: /usr/bin/script' >> /etc/sudoers


## script para instalacion de sqlite

sudo apt -y update
apt -y install sqlite3 php-sqlite3

sqlite3 /var/www/html/loginweb.db <<EOF

CREATE TABLE usuarios (
	id INTEGER PRIMARY KEY,
	contrasena TEXT NOT NULL,
	usuario TEXT NOT NULL
);

INSERT INTO usuarios (contrasena, usuario) VALUES
('7Feliz*Dia8', 'andres'),
('S0l@Aman3c3r*Lu7', 'emma'),
('2023M!3d!t@c!ón', 'guillermo'),
('D3scubr!r.4v3ntur@_', 'pablo'),
('C@l!3#P@s30s', 'angel'),
('Casa#Playa2023', 'laura'),
('C@f3.Mañ@n@2023', 'andres');

INSERT INTO usuarios (usuario, contrasena) VALUES ('admin', 'admin');
-- postgres --
EOF
