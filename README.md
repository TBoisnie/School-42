# 42 - CLoud - Inception of Things

Creation of VM-clusters using `Vagrant`, `Kubernetes`, `K3s`, `K3d`, CI/CD using `ArgoCD`.

> [!IMPORTANT]
> Project has been made on in Arch Linux environment.
> Therefore, scripts use `pacman` to install dependencies.

## Requirements

- [VirtualBox](https://www.virtualbox.org/)
- [Vagrant](https://developer.hashicorp.com/vagrant)
- [OpenSSH](https://www.openssh.com/)

## Getting Started

### Part 1

1. Build

	```sh
	# Change directory
	cd ./p1

	# Run
	vagrant up
	```

1. Verify

	```sh
	# Connect to the VM
	vagrant ssh tboisnieS

	# Inside the VM
	kubectl get nodes -o wide # Should display tboisnieS (Server) and tboisnieSW (Worker)
	ifconfig eth1 # IPv4 should be 192.168.42.110 on Server, and 192.168.42.111 on Worker.
	```

### Part 2

1. Build

	```sh
	# Change directory
	cd ./p2

	# Run
	vagrant up
	```

1. Verify

	```sh
	# Connect to the VM
	vagrant ssh tboisnieS

	# Inside the VM
	kubectl get all # Should see 1 x app-1, 3 x app-2 and 1 x app-3.
	curl -H "Host:app2.com" 192.168.42.110 # Should render ./confs/shared/app-2/index.html (likewise for app1 and app3)
	```

### Part 3

1. Configure

	```sh
	# Public GitHub repository URL
	REPO_URL="https:\/\/github\.com\/TBoisnie\/42-InceptionOfThings-App\.git"

	# Push files
	cd ./confs
	git init && git add wil.yaml && git commit -m "Added wil.yaml"
	git remote add origin "git@github.com:TBoisnie/42-InceptionOfThings-App.git"
	git push -u origin main

	# Update ArgoCD
	sed -i "s/YOUR_REPO_URL/$REPO_URL/g" ./confs/argocd.app.yaml
	```

1. Run

	```sh
	./scripts/install.sh
	```

1. Access

	- `ArgoCD` : __https://localhost:8080__
	- Application : __http://localhost:8888__

1. Update app version

	```sh
	# From v1 to v2
	sed -i "s/playground:v1/playground:v2/g" ./confs/wil.yaml

	# Push
	cd ./confs && git add wil.yaml && git commit -m "Switch to v2" && git push -u origin main
	```

1. Verify

	```sh
	# Should now show app v2
	curl http://localhost:8888/
	```

### Bonus

1. Run

	```sh
	./scripts/install.sh
	```

1. Update repository visibility on local GitLab when asked for : `https://localhost`

1. Access

	- `ArgoCD` : __https://localhost:8080__
	- Application : __http://localhost:8888__

1. Update app version

	```sh
	# From v1 to v2
	sed -i "s/playground:v1/playground:v2/g" ./confs/wil.yaml

	# Push
	cd ./confs && git add wil.yaml && git commit -m "Switch to v2" && git push -u origin main
	```

1. Verify

	```sh
	# Should now show app v2
	curl http://localhost:8888/
	```

## Troubleshoots

- VirtualBox IPs out of range

	```sh
	sudo echo "* 0.0.0.0/0 ::/0" >> /etc/vbox/networks.conf
	```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
