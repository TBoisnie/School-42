# 42 - Core - WebServ

Implementation in `C++` of a basic configurable HTTP Server (impired by `Nginx`) with support for `PHP-CGI`.

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [Clang](https://clang.llvm.org/)
- [PHP-CGI](https://www.php.net/) _(Optional: If using provided custom test configuration)_

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./srcs

	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# Re : Run "fclean" then "all"
	```

1. Update configuration file

	```sh
	# Add custom hosts
	vim /etc/hosts

	127.0.0.1 dev.local
	127.0.0.1 test.local
	127.0.0.1 default.local
	127.0.0.2 dev2.local
	127.0.0.2 default2.local
	```

	```sh
	# Edit
	vim ../tests/custom/custom.conf
	```

1. Execute

	```sh
	# Run
	./webserv ../tests/custom/custom.conf
	```

1. Access : __http://127.0.0.1:8080__

## Resources

- https://tools.ietf.org/html/rfc7230
- https://tools.ietf.org/html/rfc7231
- https://tools.ietf.org/html/rfc7232
- https://tools.ietf.org/html/rfc7235

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
- [GERMAIN Thomas](https://github.com/thomasgermain07)
