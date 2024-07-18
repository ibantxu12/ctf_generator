apt-get update
apt-get install ruby-full -y
apt-get install build-essential -y
apt-get install wkhtmltopdf -y
apt-get install libimage-exiftool-perl -y
gem install bundler
useradd -m etzio
cd /opt/scripts
unzip pdfapp.zip
cd pdfapp
echo "gem 'thin'" >> Gemfile
chmod 777 pdf/
bundle install
a2enmod proxy
a2enmod proxy_http
archivo_config="/etc/apache2/sites-available/000-default.conf"
contenido_config="<VirtualHost *:80>
        ServerAdmin webmaster@localhost
        DocumentRoot /var/www/html
        ErrorLog ${APACHE_LOG_DIR}/error.log
        CustomLog ${APACHE_LOG_DIR}/access.log combined
        ProxyPass /pdf http://localhost:9292
        ProxyPassReverse /pdf http://localhost:9292
</VirtualHost>"
echo "$contenido_config" > "$archivo_config"