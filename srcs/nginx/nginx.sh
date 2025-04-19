#!/bin/sh

sed -i "s/_k8s_telegraf_db_name_/nginx_metrics/g" /etc/telegraf.conf

adduser -D -g 'www' www

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-subj '/C=FR/ST=75/L=Paris/O=42/CN=tboisnie' \
	-keyout /etc/ssl/localhost.key \
	-out /etc/ssl/localhost.crt

adduser -D "$SSH_USER"
echo "$SSH_USER:$SSH_PASS" | chpasswd

openrc
touch /run/openrc/softlevel
rc-update add sshd
rc-update add nginx
rc-service sshd start
rc-service nginx start

telegraf --config /etc/telegraf.conf &

sleep 10

while 
	rc-status | grep nginx | grep started > /dev/null && \
	rc-status | grep sshd | grep started > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done