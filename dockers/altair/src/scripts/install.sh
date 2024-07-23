#!/bin/bash

groupadd login && usermod -a -G login www-data && chgrp login /usr/bin/ptx && chmod u+s /usr/bin/ptx && chmod g+x /usr/bin/ptx && chmod o-x /usr/bin/ptx
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
	usuario VARCHAR(255) NOT NULL,
	contrasena VARCHAR(255) NOT NULL
);

INSERT INTO usuarios (usuario, contrasena) VALUES
('patricia', 'N!ñ0#F3l!c!d@d#L@r3d0'),
('isabel', '567@m1g0#F!3st@'),
('carlos', 'Montañ@Ri0_12'),
('isabel', 'C!udad_P@s3o*V!d@'),
('carlos', 'L3ctur@8Libr0s'),
('marta', 'P!zza.H3lad0@'),
('jose', 'C@l!3#P@s30s'),
('lucia', '567@m1g0#F!3st@'),
('raquel', 'C@f3.Mañ@n@2023');

INSERT INTO usuarios (usuario, contrasena) VALUES ('root', 'mktt');
-- postgres --
EOF
