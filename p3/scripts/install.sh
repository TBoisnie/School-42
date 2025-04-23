#!/usr/bin/env sh

echo "================================================================================"
echo "== Packages: Install"
echo "================================================================================"
echo "- Docker & Kubectl -------------------------------------------------------------"
sudo pacman -Syu --needed --noconfirm docker kubectl

echo "- User Group -------------------------------------------------------------------"
sudo usermod -aG docker $USER

echo "- Start Services ---------------------------------------------------------------"
sudo systemctl start docker

./k3d.sh
./argocd.sh
