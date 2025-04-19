#
# Un serveur Nginx ouvert sur les ports 80 et 443.
#
# Vous devrez vous assurer de pouvoir accéder a votre Nginx en connexion SSH.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
# 	en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	openrc telegraf nginx openssh openssl

COPY config/default	/etc/nginx/conf.d/default.conf
COPY telegraf.conf	/etc/
COPY nginx.sh		/tmp/

RUN chmod +x /tmp/nginx.sh

EXPOSE 22 80 443

CMD /tmp/nginx.sh