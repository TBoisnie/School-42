#
# Un grafana, accessible sur le port 3000,
#	fonctionnant avec une base de donnée influxDB.
# Celui-ci devra vous permettre de monitorer tous vos containers.
# Les deux devront aussi être dans deux containers distincts.
# Vous devrez créer un dashboard par container.
#
# En cas de crash ou d’arrêt d’un des deux containers de base de données, vous
# 	devrez vous assurer que celles-ci puissent persister et ne soient pas perdu.
# En cas de suppression, les volumes où la data est sauvegardée doivent persister.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
# 	en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	telegraf influxdb

COPY telegraf.conf	/etc/
COPY influxdb.sh	/tmp/

RUN chmod +x /tmp/influxdb.sh

EXPOSE 8086

CMD /tmp/influxdb.sh