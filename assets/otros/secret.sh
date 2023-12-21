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