FROM ibantxu12/debian_vulnerable:latest
ENV HOSTNAME altair
ENV LANG C.UTF-8
COPY ./src/webContent/ /var/www/html/
RUN echo '##rootFlag##' > /root/root.txt
RUN echo '##userFlag##' > /home/user.txt && chown www-data:www-data /home/user.txt
EXPOSE 80
CMD ["/usr/sbin/apachectl", "-D", "FOREGROUND"]
