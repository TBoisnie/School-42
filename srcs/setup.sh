#!/bin/bash

# ---------------------------------------
# -- TOOLS
# ---------------------------------------
# -- Colors Variables
color_usage="\e[94m"
color_info="\e[93m"
color_wait="\e[90m"
color_none="\e[0m"

# -- Waiting function
waitPodMetalReady()
{
	while [[ $(kubectl get pods -n metallb-system -l component=$1 -o 'jsonpath={..status.conditions[?(@.type=="Ready")].status}') != "True" ]]; do
		echo -e $color_wait "Waiting Metal Pod ( $1 )..." $color_none;
		sleep 10;
	done
}
waitPodReady()
{
	while [[ $(kubectl get pods -l app=$1 -o 'jsonpath={..status.conditions[?(@.type=="Ready")].status}') != "True" ]]; do
		echo -e $color_wait "Waiting Pod ( $1 )..." $color_none;
		sleep 10;
	done
}

waitAPT()
{
	while sudo fuser /var/{lib/{dpkg,apt/lists},cache/apt/archives}/lock >/dev/null 2>&1; do
		echo -e $color_wait "Waiting APT to finish update..." $color_none;
		sleep 30;
	done
}

getServiceIP()
{
	kubectl get service -l app=$1 -o jsonpath='{..ip}'
}

# ---------------------------------------
# -- CLEANING
# ---------------------------------------
echo -e $color_info "Cleaning Minikube and Storage..." $color_none
minikube stop
minikube delete

# rm -r ~/.minikube

rm -r /mnt/k8s_influxdb
rm -r /mnt/k8s_mysql

# ---------------------------------------
# -- KUBERNETES (start)
# ---------------------------------------
echo -e $color_info "Starting Minikube..." $color_none

# export MINIKUBE_HOME="/tmp/tboisnie/"
# minikube start --cpus=2 --vm-driver=virtualbox
# eval $(minikube docker-env)

waitAPT
apt-get install conntrack
minikube start --vm-driver=none

# usermod -aG docker $(whoami)
# minikube start --vm-driver=docker
# Restart VM ?

# ---------------------------------------
# -- DOCKER
# ---------------------------------------
# -- Telegraf
cp telegraf.conf grafana_influxdb/influxdb/
cp telegraf.conf wp_sql_pma/mysql/
cp telegraf.conf ftps/
cp telegraf.conf nginx/
cp telegraf.conf wp_sql_pma/phpmyadmin/
cp telegraf.conf wp_sql_pma/wordpress/
cp telegraf.conf grafana_influxdb/grafana/

# -- Build
echo -e $color_info "Building docker images..." $color_none
docker build -qt influxdb grafana_influxdb/influxdb/
docker build -qt mysql wp_sql_pma/mysql/
docker build -qt ftps ftps/
docker build -qt nginx nginx/
docker build -qt phpmyadmin wp_sql_pma/phpmyadmin/
docker build -qt wordpress wp_sql_pma/wordpress/
docker build -qt grafana grafana_influxdb/grafana/

# -- Clean
rm grafana_influxdb/influxdb/telegraf.conf
rm wp_sql_pma/mysql/telegraf.conf
rm ftps/telegraf.conf
rm nginx/telegraf.conf
rm wp_sql_pma/phpmyadmin/telegraf.conf
rm wp_sql_pma/wordpress/telegraf.conf
rm grafana_influxdb/grafana/telegraf.conf

# ---------------------------------------
# -- KUBERNETES (apply)
# ---------------------------------------
# -- Addons
echo -e $color_info "Enabling Kubernetes addons..." $color_none
minikube addons enable metrics-server
minikube addons enable dashboard

# -- MetalLB
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/namespace.yaml
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/metallb.yaml
kubectl create secret generic -n metallb-system memberlist --from-literal=secretkey="$(openssl rand -base64 128)"
kubectl apply -f metallb.yaml
waitPodMetalReady 'speaker'
waitPodMetalReady 'controller'

# -- Apply
echo -e $color_info "Applying Kubernetes files..." $color_none
kubectl apply -f grafana_influxdb/influxdb/
waitPodReady 'influxdb'
kubectl apply -f wp_sql_pma/mysql/
waitPodReady 'mysql'
kubectl apply -f ftps/
waitPodReady 'ftps'
kubectl apply -f nginx/
waitPodReady 'nginx'
kubectl apply -f wp_sql_pma/phpmyadmin/
waitPodReady 'phpmyadmin'
kubectl apply -f wp_sql_pma/wordpress/
waitPodReady 'wordpress'
kubectl apply -f grafana_influxdb/grafana/
waitPodReady 'grafana'

# ---------------------------------------
# -- INFO
# ---------------------------------------
echo -e $color_usage
echo "-----------------------------------"
echo "Enable dashboard : 'minikube dashboard'"
echo ""
echo "Credentials :"
echo "-- FTPS : (Filezilla) ftp_user / ftp_pass"
echo "-- Nginx : (Browser) $(getServiceIP 'nginx')"
echo "-- SSH : ssh ssh_user@$(getServiceIP 'nginx') / ssh_pass"
echo "-- Wordpress : (Browser) $(getServiceIP 'wordpress'):5050"
echo "-- -- wp_user / wp_pass"
echo "-- -- wp_author / wp_pass"
echo "-- -- wp_editor / wp_pass"
echo "-- -- wp_subscriber / wp_pass"
echo "-- Phpmyadmin : (Browser) $(getServiceIP 'phpmyadmin'):5000"
echo "-- -- root / toor"
echo "-- -- mysql_user / mysql_pass"
echo "-- Grafana : (Browser) $(getServiceIP 'grafana'):3000"
echo "-- -- admin / admin"
echo "-----------------------------------"
echo -e $color_none

minikube dashboard

# kubectl exec deploy/dp-nginx -- pkill nginx
