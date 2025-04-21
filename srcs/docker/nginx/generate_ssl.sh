#!/usr/bin/env sh
set -e

mkdir -p /etc/ssl
echo "$SSL_CRT" >> /etc/ssl/camagru.crt
echo "$SSL_KEY" >> /etc/ssl/camagru.key

exec "$@"
