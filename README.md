# 42 - Core - Transcendence

Creation of a website in `Typescript` (`NestJS`, `Vue3`), `PostgreSQL` database and using `Docker` to containerize it.

Features :
- User authentication : OAuth2 (42), 2FA (Google)
- User profile : Avatar, Identity
- User relations : Friends, Ignores
- User status : Online, Offline, InGame
- Chat :
	- Rooms : Visibility (Public, Protected, Private),  Administration (Mute, Ban), Invitation
	- One-To-One : Block (won't receive any more notifications / messages)
- Pong : Normal or Ranked Games (with or without Mods), Duel or Match making, Ladder / History

## Requirements

- [Docker](https://www.docker.com/)

## Getting Started

1. Configure

	```sh
	# Change directory
	cd ./srcs

	# Edit
	cp ./docker/.env.template ./docker/.env
	vim ./docker/.env
	```

1. Build

	```sh
	# Run
	docker compose up
	```

1. Access : __http://localhost:3000__

## Resources

- https://api.intra.42.fr/apidoc/guides/getting_started
- https://nestjs.com
- https://v3.vuejs.org/
- https://socket.io/

## Authors

- [BOISNIER Thomas](https://github.com/TBoisnie)
- [GERMAIN Thomas](https://github.com/thomasgermain07)
- [MAOKHAM Viviane](https://github.com/v-maokham)
- [PERROT Quentin](https://github.com/qperrot)
