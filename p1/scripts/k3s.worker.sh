#!/usr/bin/env sh

echo "[Worker] Waiting server token..."
until [ -f "$1" ]
do
	sleep 5
done

echo "[Worker] K3s installation..."
curl -sfL https://get.k3s.io | sh -s - agent \
	--server "https://$2:6443/" \
	--node-ip "$3" \
	--token-file "$1" \
	--flannel-iface "eth1"

echo "[Worker] Ready \o/"
