#!/usr/bin/env sh

echo "[Server] K3s installation..."
curl -sfL https://get.k3s.io | sh -s - \
	--node-ip "$1" \
	--write-kubeconfig-mode "644"

echo "[Server] Waiting token generation..."
until [ -f "/var/lib/rancher/k3s/server/node-token" ]
do
	sleep 5
done

echo "[Server] Waiting nodes..."
sleep 15
k3s kubectl wait --for=condition=Ready nodes --all

echo "[Server] Deploying applications..."
k3s kubectl apply -f $2

echo "[Server] Waiting pods..."
sleep 15
k3s kubectl wait --for=condition=Ready pods --all

echo "[Server] Ready. \o/"
