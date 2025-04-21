# 42 - Web - HyperTube

Creation of a streaming website using `TypeScript`, `React`, `NestJS`, `PostgreSQL` and `Docker`.

Features :
- User authentication : Credentials, OAuth (42, Google, GitHub)
- Search movies torrents : 2 sources used (ThePirateBay, YTS)
- Search movies details : From OMDB API
- Movies download : From `magnet` links (using `TorrentStream` library), Cached for 30 days
- Movies streaming : Native `mp4` or `webm`, Converted `mkv` into `mp4` (using `fluent-ffmpeg` library)
- Movies subtitles : Native `vtt`, Converted `srt` (using `srt-to-vtt` library)
- Comments : Add and delete on movies
- Internationalization : French, English, Spanish, German
- ...

## Requirements

- [Docker](https://www.docker.com/)
- [OpenSSL](https://www.openssl.org/)

## Getting Started

1. Configure

	```sh
	# Certificates
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt -config openssl.cnf

	# Environment
	cp .env.template .env
	vim .env
	```

1. Build

	```sh
	# Run
	docker compose up --build
	```

1. Access : __https://localhost:5173__

## Authors

- [BOISNIER Thomas](https://github.com/TBoisnie/) _(Torrents search/download, Movies streaming/subtitles/details, Comments)_
- [PARIS Lilian](https://github.com/lparis42/) _(Users authentication/profile)_
