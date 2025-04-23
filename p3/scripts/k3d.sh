#!/usr/bin/env sh

echo "================================================================================"
echo "== K3d: Install"
echo "================================================================================"
# https://k3d.io/v5.4.7/#install-current-latest-release
if ! command -v k3d &> /dev/null
then
	curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash
fi

echo "================================================================================"
echo "== K3d: Configure"
echo "================================================================================"
# https://k3d.io/v5.4.7/usage/commands/k3d_cluster_create/
k3d cluster create --config ../confs/k3d.config.yaml
