#!/bin/sh

sed -i "s/_k8s_telegraf_db_name_/wp_metrics/g" /etc/telegraf.conf

sed -i "s/_k8s_wp_db_name_/${WP_DB_NAME}/g" /srv/wp-config.php
sed -i "s/_k8s_wp_db_user_/${WP_DB_USER}/g" /srv/wp-config.php
sed -i "s/_k8s_wp_db_pass_/${WP_DB_PASS}/g" /srv/wp-config.php
sed -i "s/_k8s_wp_db_host_/${SVC_MYSQL_SERVICE_HOST}/g" /srv/wp-config.php

MYSQL_CONNECT="mysql -h $SVC_MYSQL_SERVICE_HOST -u $WP_DB_USER -p$WP_DB_PASS"

if [ "$($MYSQL_CONNECT -B -N -e "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = '$WP_DB_NAME' AND table_name = 'wp_users';")" == "0" ]; then
	echo "Populate Wordpress Database."
	$MYSQL_CONNECT $WP_DB_NAME < /tmp/wordpress.sql
fi

openrc
touch /run/openrc/softlevel
rc-update add php-fpm7
rc-update add nginx
rc-service php-fpm7 restart
rc-service nginx restart

telegraf --config /etc/telegraf.conf &

sleep 10

while 
    rc-status | grep nginx | grep started > /dev/null && \
    rc-status | grep php-fpm7 | grep started > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done