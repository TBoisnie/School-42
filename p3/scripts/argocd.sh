#!/usr/bin/env sh

echo "================================================================================"
echo "== ArgoCD: Install"
echo "================================================================================"
echo "Creating 'argocd' namespace..."
kubectl create namespace argocd
echo "Seting context..."
kubectl config set-context --current --namespace=argocd
echo "Applying install..."
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
echo "Waiting install finish..."
kubectl wait -n argocd --for=condition=Ready --timeout=-1s pod --all

echo "================================================================================"
echo "== ArgoCD: Application"
echo "================================================================================"
# https://argo-cd.readthedocs.io/en/stable/operator-manual/declarative-setup/#applications
echo "Creating 'dev' namespace..."
kubectl create namespace dev
echo "Applying application..."
kubectl apply -n argocd -f ../confs/argocd.app.yaml
echo "Waiting application..."
kubectl wait -n dev --for=condition=Ready --timeout=-1s pod --all

echo "================================================================================"
echo "== ArgoCD: Dashboard"
echo "================================================================================"
# https://argo-cd.readthedocs.io/en/stable/getting_started/#port-forwarding
# https://argo-cd.readthedocs.io/en/stable/getting_started/#4-login-using-the-cli
echo "Forwarding port..."
kubectl port-forward -n argocd svc/argocd-server 8080:443 &> /dev/null &
echo "--------------------------------"
echo "Host: https://locahost:8080"
echo "Username: admin"
echo "Password: $(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath='{.data.password}' | base64 -d)"
echo "--------------------------------"
