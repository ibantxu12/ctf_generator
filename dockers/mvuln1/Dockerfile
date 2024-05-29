FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
COPY ./src/files.zip /home/files.zip
RUN chmod 770 /opt/scripts/install.sh
RUN /opt/scripts/install.sh
RUN echo 'l0tgq70an0qpvolrh11i7cttk9ulkl6b' > /root/root.txt
RUN echo 'tu98p0oudquaco7p63q3b054giqavl1u' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
