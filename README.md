# 42 - Core - FT Services

Installation and configuration of a `Kubernetes` cluster, using `Docker` images (`Nginx`, `FTPS`, `SSH`, `Grafana`, `InfluxDB`, `Wordpress`, `PostgreSQL`, `PhpMyAdmin`, `MetalLB`).

## Requirements

- [Kubernetes](https://kubernetes.io/)
- [Docker](https://www.docker.com/)

## Getting Started

1. Installation and configuration

	```sh
	./setup.sh
	```

1. Browse

	- See `setup.sh` output

1. Authenticate

	- Nginx : _(Browser)_
	- SSH : _(Command line)_
		- `ssh_user` / `ssh_pass`
	- FTPS : _(Filezilla)_
		- `ftp_user` / `ftp_pass`
	- Wordpress : _(Browser)_
		- `wp_user` / `wp_pass`
		- `wp_author` / `wp_pass`
		- `wp_editor` / `wp_pass`
		- `wp_subscriber` / `wp_pass`
	- Phpmyadmin : _(Browser)_
		- `root` / `toor`
		- `mysql_user` / `mysql_pass`
	- Grafana : _(Browser)_
		- `admin` / `admin`

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
