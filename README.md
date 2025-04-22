# 42 - Security - FT SSL

Re/Implementation in `C` of some few hashing / encryption functions (_md5_, _sha256_ and _whirlpool_).

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# Re : Run "fclean" then "all"
	```

1. Execute

	```sh
	# Run
	./bins/ft_ssl -h
	```

## Examples

```sh
./bins/ft_ssl md5 -h
usage: ft_ssl <algorithm> [-hpqr] [-s <str>]... [file]...

Arguments:
  algorithm     Hashing algorithm (md5, sha256)
  file          File to read from
Flags:
  -h            Display this help and exit
  -p            Echo STDIN to STDOUT and append the checksum to STDOUT
  -q            Quiet mode
  -r            Reverse the format of the output
  -s <str>      Print the sum of the given <str>

./bins/ft_ssl md5 -s 'Hello World!'
MD5 ("Hello World!") = ed076287532e86365e841e92bfc50d8c

./bins/ft_ssl sha256 -s 'Hello World!'
SHA256 ("Hello World!") = 7f83b1657ff1fc53b92dc18148a1d65dfc2d4b1fa3d677284addd200126d9069

./bins/ft_ssl whirlpool -s 'Hello World!'
WHIRLPOOL ("Hello World!") = d4b3ad3619bc70157376c5426b558dbdad30654cf441ab21d7c08e993873256becc80f32448d0218d5b1aab30bf4209e20e3928df002d3cbcfbe501a184680a8
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
