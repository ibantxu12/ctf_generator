#!/bin/bash

service postgresql start
echo 'a'
systemctl enable mongod --now
cd /home/secret
su -c 'node index.js &' -s /bin/bash etzio
/usr/sbin/apachectl -D FOREGROUND