#!/usr/bin/env sh

echo "[Server] K3s installation..."
curl -sfL https://get.k3s.io | sh -s - server \
	--node-ip "$2" \
	--tls-san "$2" \
	--flannel-iface "eth1" \
	--write-kubeconfig-mode "644"

echo "[Server] Waiting token generation..."
until [ -f "/var/lib/rancher/k3s/server/node-token" ]
do
	sleep 5
done

echo "[Server] Sharing token..."
cp "/var/lib/rancher/k3s/server/node-token" $1

echo "[Server] Ready. \o/"
