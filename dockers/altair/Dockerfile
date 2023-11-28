FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
RUN chmod 770 /opt/scripts/install.sh
RUN /opt/scripts/install.sh
RUN echo 'pbbc4v366y2walp8o482n8h0lde50nyg' > /root/root.txt
RUN echo '221yg3elc5pp0ldn8cpt8daon6qnex3n' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
