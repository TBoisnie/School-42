#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

# ---------------------------------------
# REQUIREMENTS
# ---------------------------------------
apt-get update
apt-get -y dist-upgrade

apt-get -y install wget

# ---------------------------------------
# NGINX
# ---------------------------------------
echo "--------------------- NGINX ---------------------"
cd ~
# -- install
apt-get -y install nginx

# -- vhost
mkdir /srv/localhost
rm /etc/nginx/sites-available/default
rm /etc/nginx/sites-enabled/default
mv /tmp/localhost /etc/nginx/sites-available/
ln -s /etc/nginx/sites-available/localhost /etc/nginx/sites-enabled/

# ---------------------------------------
# SSH
# ---------------------------------------
echo "--------------------- SSH ---------------------"
cd ~
# -- install
apt-get -y install libnss3-tools

cd /tmp
wget -O mkcert https://github.com/FiloSottile/mkcert/releases/download/v1.4.1/mkcert-v1.4.1-linux-amd64
chmod +x mkcert
mv mkcert /usr/local/bin

# -- certificate
cd /etc/ssl
mkcert -install
mkcert localhost

# ---------------------------------------
# MYSQL
# ---------------------------------------
echo "--------------------- MYSQL ---------------------"
cd ~
# -- install
apt-get -y install mariadb-server

service mysql start

# -- secure
mysql -u root -e "UPDATE mysql.user SET Password=PASSWORD('toor') WHERE User='root';"
mysql -u root -e "DELETE FROM mysql.user WHERE User='';"
mysql -u root -e "DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');"
mysql -u root -e "DROP DATABASE IF EXISTS test;"
mysql -u root -e "DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';"
mysql -u root -e "FLUSH PRIVILEGES;"

# ---------------------------------------
# PHP
# ---------------------------------------
echo "--------------------- PHP ---------------------"
cd ~
# -- install
apt-get -y install php7.3-fpm php-mysql php-cli \
				php-mbstring php-gd php-xml php-intl php-zip php-curl

service php7.3-fpm start

# ---------------------------------------
# WORDPRESS
# ---------------------------------------
echo "--------------------- WORDPRESS ---------------------"
cd /srv/localhost
# -- database
mysql -u root -ptoor -e "CREATE DATABASE wordpress;"
mysql -u root -ptoor -e "CREATE USER 'wpuser'@'localhost' IDENTIFIED BY 'wppass';"
mysql -u root -ptoor -e "GRANT ALL ON wordpress.* TO 'wpuser'@'localhost' IDENTIFIED BY 'wppass' WITH GRANT OPTION;"
mysql -u root -ptoor -e "FLUSH PRIVILEGES;"

# -- install
wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp

wp core download --allow-root
wp config create --allow-root --dbname=wordpress --dbuser=wpuser --dbpass=wppass
wp core install --allow-root --url=localhost --title=MyAmazingWebsite --admin_user=wpadmin --admin_password=wpadminpass --admin_email=mail@fake.org

# -- Rights
chown -R www-data:www-data /srv/localhost/
chmod -R 755 /srv/localhost/

# ---------------------------------------
# PHPMYADMIN
# ---------------------------------------
echo "--------------------- PHPMYADMIN ---------------------"
cd /tmp
# -- install
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.2/phpMyAdmin-4.9.2-english.tar.gz
tar -zxvf phpMyAdmin-4.9.2-english.tar.gz
mv phpMyAdmin-4.9.2-english /srv/localhost/phpmyadmin
rm phpMyAdmin-4.9.2-english.tar.gz

# -- config
mv /srv/localhost/phpmyadmin/config.sample.inc.php /srv/localhost/phpmyadmin/config.inc.php

# ---------------------------------------
# START
# ---------------------------------------
echo "--------------------- START ---------------------"
service nginx restart
bash
