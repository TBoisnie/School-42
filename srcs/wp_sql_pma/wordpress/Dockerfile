#
# Un wordpress ouvert sur le port 5050,
# 	fonctionnant avec une base de donnée Mysql.
# Les deux devront être dans deux containers distincts.
# Le wordpress devra comporter plusieurs utilisateurs et un administrateur.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
# 	en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	telegraf \
	openrc \
	nginx \
	wget mysql-client \
	php7 php7-fpm php7-common php7-session php7-iconv php7-json php7-gd \
	php7-curl php7-xml php7-mysqli php7-imap \
	php7-cgi fcgi php7-pdo php7-pdo_mysql \
	php7-soap php7-xmlrpc php7-posix php7-mcrypt \
	php7-gettext php7-ldap php7-ctype php7-dom

RUN wget -O /tmp/wordpress.tar.gz https://wordpress.org/latest.tar.gz \
	&& tar -xf /tmp/wordpress.tar.gz --strip-components=1 -C /srv \
	&& rm /tmp/wordpress.tar.gz

COPY config/default			/etc/nginx/conf.d/default.conf
COPY config/php-fpm.conf	/etc/php7/php-fpm.d/www.conf
COPY config/wordpress.sql	/tmp/
COPY config/wp-config.php	/srv/
COPY telegraf.conf			/etc/
COPY wordpress.sh			/tmp/

RUN chmod +x /tmp/wordpress.sh

EXPOSE 80

CMD /tmp/wordpress.sh