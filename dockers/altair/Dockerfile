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
RUN echo 'exm4qao6i2l3y5z72kpb76xhryux1jlm' > /root/root.txt
RUN echo '7b8zj3hu92opv5e537fs2hrgjvv70djx' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
