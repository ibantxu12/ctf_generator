FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
COPY ./src/rce.php /var/www/html
RUN chmod 770 /opt/scripts/install.sh
RUN chmod 770 /opt/scripts/inicio.sh
RUN chown -R www-data:www-data /var/www/html/
RUN chmod 770 /var/www/html/
RUN /opt/scripts/install.sh
##ejecucion2##
RUN echo 'objwu3hpo860fy4uwqfghu5mui5k9v03' > /root/root.txt
RUN echo 'kwm32cuvpv0r51le88wvdl8zea7dk1za' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
