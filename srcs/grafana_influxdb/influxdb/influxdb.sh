#!/bin/sh

sed -i "s/\$SVC_INFLUXDB_SERVICE_HOST/127.0.0.1/g" /etc/telegraf.conf
sed -i "s/_k8s_telegraf_db_name_/influxdb_metrics/g" /etc/telegraf.conf

telegraf --config /etc/telegraf.conf &
influxd run -config /etc/influxdb.conf &

sleep 10

while 
	pgrep -x "influxd" > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done