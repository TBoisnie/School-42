#!/bin/sh

sed -i "s/_k8s_influxdb_ip_/$SVC_INFLUXDB_SERVICE_HOST/g" /usr/share/grafana/conf/provisioning/datasources/datasources.yaml
sed -i "s/_k8s_telegraf_db_name_/grafana_metrics/g" /etc/telegraf.conf

telegraf --config /etc/telegraf.conf &
/usr/sbin/grafana-server --homepath=/usr/share/grafana --config=/etc/grafana.ini &

sleep 10

while 
	pgrep -x "/usr/sbin/grafana-server" > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done