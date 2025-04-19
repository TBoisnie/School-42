#
# Un wordpress ouvert sur le port 5050,
# 	fonctionnant avec une base de donnée Mysql.
# Les deux devront être dans deux containers distincts.
# Le wordpress devra comporter plusieurs utilisateurs et un administrateur.
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
	telegraf mysql mysql-client

COPY config/mariadb-server.cnf	/etc/my.cnf.d/
COPY telegraf.conf				/etc/
COPY mysql.sh					/tmp/

RUN chmod +x /tmp/mysql.sh

VOLUME ["/var/lib/mysql"]

EXPOSE 3306

CMD /tmp/mysql.sh