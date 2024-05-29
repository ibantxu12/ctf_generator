FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
COPY ./src/scripts /opt/scripts
COPY ./src/files.zip /home/files.zip
RUN chmod 770 /opt/scripts/install.sh
RUN chmod 770 /opt/scripts/inicio.sh
RUN /opt/scripts/install.sh
RUN echo '7nvtepo3zqz20e0yhpycn0en1cq7nh00' > /root/root.txt
RUN echo 'hww2glo5zjc5x4p88dzt5scw9usxg50n' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/bin/bash","-c","/opt/scripts/inicio.sh"]
