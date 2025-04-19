#!/bin/sh

sed -i "s/_k8s_telegraf_db_name_/mysql_metrics/g" /etc/telegraf.conf

if [ ! -d '/run/mysqld' ]; then
  mkdir -p /run/mysqld
fi

if [ -d '/var/lib/mysql' ]; then
  mysql_install_db --user=root --datadir='/var/lib/mysql'

  MYSQL_DATABASE=${MYSQL_DATABASE:-""}
  MYSQL_USER=${MYSQL_USER:-""}
  MYSQL_PASS=${MYSQL_PASS:-""}

  tfile=`mktemp`
  if [ ! -f "$tfile" ]; then
      return 1
  fi

  cat << EOF > $tfile
FLUSH PRIVILEGES;
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY "toor" WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY "toor" WITH GRANT OPTION;
FLUSH PRIVILEGES;
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
FLUSH PRIVILEGES;
EOF

  if [ "$MYSQL_DATABASE" != "" ]; then
    echo "CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\` CHARACTER SET utf8 COLLATE utf8_general_ci;" >> $tfile
    if [ "$MYSQL_USER" != "" ]; then
      echo "GRANT ALL ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASS';" >> $tfile
    fi
    echo "FLUSH PRIVILEGES;" >> $tfile
  fi

  /usr/bin/mysqld --user=root --datadir='/var/lib/mysql' --bootstrap --verbose=0 < $tfile
  rm -f $tfile
fi

telegraf --config /etc/telegraf.conf &
exec /usr/bin/mysqld --user=root --datadir='/var/lib/mysql' --console &

sleep 10

while 
	pgrep -x "/usr/bin/mysqld" > /dev/null && \
	pgrep -x "telegraf" > /dev/null;
	do
	sleep 30;
done