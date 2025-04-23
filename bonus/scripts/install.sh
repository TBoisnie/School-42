#!/usr/bin/env sh

echo "================================================================================"
echo "== Packages: Install"
echo "================================================================================"
echo "- Docker & Kubectl -------------------------------------------------------------"
sudo pacman -Syu --needed --noconfirm docker kubectl git glab

echo "- User Group -------------------------------------------------------------------"
sudo usermod -aG docker $USER

echo "- Start Services ---------------------------------------------------------------"
sudo systemctl start docker

./k3d.sh
./gitlab.sh
./argocd.sh
