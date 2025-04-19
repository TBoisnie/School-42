#
# Un serveur FTPS ouvert sur le port 21.
#
# Chacun de vos containers devra pouvoir redémarrer automatiquement
# 	en cas de crash ou d’arrêt.
#

FROM alpine:latest

RUN apk --update --no-cache --allow-untrusted \
	--repository http://dl-3.alpinelinux.org/alpine/edge/testing/ add \
	telegraf vsftpd openssl

COPY config/vsftpd.conf	/etc/vsftpd/
COPY telegraf.conf		/etc/
COPY ftps.sh 			/tmp/

RUN	chmod +x /tmp/ftps.sh

EXPOSE 21 21100-21110

CMD /tmp/ftps.sh