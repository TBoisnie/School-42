#!/usr/bin/env sh

echo "================================================================================"
echo "== ArgoCD: Install"
echo "================================================================================"
echo "- Creating 'argocd' namespace --------------------------------------------------"
sudo kubectl create namespace argocd
echo "- Seting context ---------------------------------------------------------------"
sudo kubectl config set-context --current --namespace=argocd
echo "- Applying install -------------------------------------------------------------"
sudo kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
echo "- Waiting install finish -------------------------------------------------------"
sudo kubectl wait -n argocd --for=condition=Ready --timeout=-1s pod --all

echo "================================================================================"
echo "== ArgoCD: Application"
echo "================================================================================"
# https://argo-cd.readthedocs.io/en/stable/operator-manual/declarative-setup/#applications
echo "- Creating 'dev' namespace -----------------------------------------------------"
sudo kubectl create namespace dev
echo "- Setting host ip --------------------------------------------------------------"
IP=$(ip a | grep "inet " | head -n2 | tail -n1  | awk '{print $2}' | awk -F '/' '{print $1}')
sed -i "s/{HOST_PLACEHOLDER}/$IP/" ../confs/argocd.config.yaml
echo "- Applying application ---------------------------------------------------------"
sudo kubectl apply -n argocd -f ../confs/argocd.config.yaml

echo "================================================================================"
echo "== ArgoCD: Dashboard"
echo "================================================================================"
# https://argo-cd.readthedocs.io/en/stable/getting_started/#port-forwarding
# https://argo-cd.readthedocs.io/en/stable/getting_started/#4-login-using-the-cli
echo "- Forwarding port --------------------------------------------------------------"
sudo kubectl port-forward -n argocd svc/argocd-server 8080:443 &> /dev/null &
echo "--------------------------------"
echo "Host: http://localhost:8080/"
echo "Username: admin"
echo "Password: $(sudo kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath='{.data.password}' | base64 -d)"
echo "--------------------------------"
