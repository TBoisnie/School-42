#!/bin/sh

sed -i "s/_k8s_telegraf_db_name_/ftps_metrics/g" /etc/telegraf.conf

addgroup -g 433 -S $FTP_USER
adduser -u 431 -D -G $FTP_USER -h /home/$FTP_USER -s /bin/false $FTP_USER
echo "$FTP_USER:$FTP_PASS" | /usr/sbin/chpasswd

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-subj '/C=FR/ST=75/L=Paris/O=42/CN=tboisnie' \
	-keyout /etc/ssl/ftps.key \
	-out /etc/ssl/ftps.crt

telegraf --config /etc/telegraf.conf &
/usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf &

sleep 10

while 
	pgrep -x "/usr/sbin/vsftpd" > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done