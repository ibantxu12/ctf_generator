FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
COPY ./src/files.zip /home/files.zip
RUN chmod 770 /opt/scripts/install.sh
RUN /opt/scripts/install.sh
RUN echo 'eu5g9isg4rlpokviiqjy8s9empdhfioj' > /root/root.txt
RUN echo 'mo5xbp7m1gtyvr9z4s5bqcjlgn9850zh' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
