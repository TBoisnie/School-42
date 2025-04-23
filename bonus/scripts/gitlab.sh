#!/usr/bin/env sh

echo "================================================================================"
echo "== Gitlab: Install"
echo "================================================================================"
echo "- Create namespace -------------------------------------------------------------"
sudo kubectl create namespace gitlab
sudo kubectl config set-context --current --namespace gitlab

echo "- Create cluster ---------------------------------------------------------------"
sudo kubectl apply -n gitlab -f ../confs/gitlab.config.yaml
sudo kubectl wait -n gitlab --for=condition=Ready --timeout=-1s pod --all
# Note: GitLab might not be accessible yet (bad gateway > 404 page not found > 502),
#       just WAIT a bit
sleep 600

echo "================================================================================"
echo "== GitLab: Application"
echo "================================================================================"
echo "- Generate App -----------------------------------------------------------------"
cd ../confs
rm -rf .git
rm -rf .git-credentials
git init
git branch -m main
git config user.name tboisnie
git config user.email tboisnie@student.42.fr
git config http.sslVerify false
echo "http://root:P%40ssword@localhost" >> ./.git-credentials
git config credential.helper 'store --file ./.git-credentials'
git add wil.yaml
git commit -m "First commit"
git remote add origin "http://localhost/root/42-InceptionOfThings-App.git"
git push -u origin main
cd -

echo "================================================================================"
echo "== GitLab: Dashboard"
echo "================================================================================"
echo "--------------------------------"
echo "Host: https://localhost/"
echo "Username: root"
echo "Password: P@ssword"
echo "--------------------------------"

echo "================================================================================"
echo "== GitLab: WARNING"
echo "================================================================================"
echo "Please set repository visibility to 'public' using GitLab Dashboard before continuing..."
echo "Press <Enter> to continue..."
read unused
