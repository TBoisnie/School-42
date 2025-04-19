#
# Phpmyadmin, tournant sur le port 5000 et relié a la base de donnée MySQL.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
# 	en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	telegraf \
	wget \
	openrc \
	nginx \
	php7 php7-fpm php7-opcache php7-gd \
	php7-mysqli php7-zlib php7-curl \
	php7-mbstring php7-json php7-session \
	php7-openssl php7-xml

RUN wget -O /tmp/phpmyadmin.tar.gz http://files.directadmin.com/services/all/phpMyAdmin/phpMyAdmin-5.0.2-all-languages.tar.gz \
	&& tar -xf /tmp/phpmyadmin.tar.gz --strip-components=1 -C /srv \
	&& rm /tmp/phpmyadmin.tar.gz

COPY config/default			/etc/nginx/conf.d/default.conf
COPY config/php-fpm.conf	/etc/php7/php-fpm.d/www.conf
COPY config/config.inc.php	/srv/
COPY telegraf.conf			/etc/
COPY phpmyadmin.sh			/tmp/

RUN chmod +x /tmp/phpmyadmin.sh

EXPOSE 80

CMD /tmp/phpmyadmin.sh
