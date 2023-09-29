FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
RUN chmod 770 /opt/scripts/install.sh
RUN /opt/scripts/install.sh
RUN echo '##rootFlag##' > /root/root.txt
RUN echo '##userFlag##' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
