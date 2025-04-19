#
# Un grafana, accessible sur le port 3000,
#   fonctionnant avec une base de donnée influxDB.
# Celui-ci devra vous permettre de monitorer tous vos containers.
# Les deux devront aussi être dans deux containers distincts.
# Vous devrez créer un dashboard par container.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
#   en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	telegraf grafana

COPY config/datasources.yaml	/usr/share/grafana/conf/provisioning/datasources/
COPY config/dashboards.yaml		/usr/share/grafana/conf/provisioning/dashboards/
COPY config/dashboards/			/var/lib/grafana/dashboards/
COPY telegraf.conf				/etc/
COPY grafana.sh					/tmp/

RUN chmod +x /tmp/grafana.sh

EXPOSE 3000

CMD /tmp/grafana.sh