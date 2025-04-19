# 42 - Core - FT Server

Installation and configuration of an all-in-one web environment (Nginx / Wordpress / PhpMyAdmin / MySQL / SSH) into a Docker container.

## Requirements

- [Docker](https://www.docker.com/)

## Getting Started

1. Build

	```sh
	# Change directory
	cd ./srcs

	# Build
	docker build -t ft_server .
	```

1. Run

	```sh
	docker run -dt -p 80:80 -p 443:443 ft_server
	```

1. Browse

	- Wordpress : `http(s)://docker-ip`
		- Username : wpadmin
		- Password : wpadminpass
	- PhpMyAdmin : `http://docker-ip/phpmyadmin`
		- Username : wpuser
		- Password : wppass

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
