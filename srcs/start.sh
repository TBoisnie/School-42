#!/usr/bin/env bash

echo "Add write authorization to public/"
chmod -R 777 www/public

echo "Starting containers"
docker compose up -d

echo "Run 'docker-compose down' to stop containers"
