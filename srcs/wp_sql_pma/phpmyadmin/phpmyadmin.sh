#!/bin/sh

sed -i "s/_k8s_telegraf_db_name_/pma_metrics/g" /etc/telegraf.conf

sed -i "s/_k8s_pma_db_host_/${SVC_MYSQL_PORT_3306_TCP_ADDR}/g" /srv/config.inc.php
sed -i "s/_k8s_pma_db_port_/${SVC_MYSQL_PORT_3306_TCP_PORT}/g" /srv/config.inc.php
    
openrc
touch /run/openrc/softlevel
rc-update add php-fpm7
rc-update add nginx
rc-service php-fpm7 start
rc-service nginx start

telegraf --config /etc/telegraf.conf &

sleep 10

while 
    rc-status | grep nginx | grep started > /dev/null && \
    rc-status | grep php-fpm7 | grep started > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done