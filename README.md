# 42 - Unix - FT Ping

Reimplementation in `c` of the `ping` command with some flags support.

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
	sudo ./bins/ft_ping -h
	```

## Examples

```sh
sudo ./bins/ft_ping -h

Usage
	ft_ping [options...] <destination...>

Parameters:
	<destination>           dns name or ip address
Options:
	-d                      use SO_DEBUG socket option
	-f                      flood ping
	-h,-?                   print help and exit
	-n                      do not resolve host addresses
	-q                      quiet output
	-r                      use SO_DONTROUTE socket option
	-v                      verbose output
	--count=<count>         stop after sending <count> packets
	--interval=<interval>   wait <interval> seconds between sending each packet
	--linger=<linger>       number of seconds to wait for response
	--pattern=<pattern>     fill ICMP packet with given <pattern> (hex)
	--preload=<preload>     send <preload> packets as fast as possible before falling into normal mode of behavior
	--size=<size>           send <size> data octets
	--timeout=<timeout>     stop after <timeout> seconds
	--tos=<tos>             specify <tos> as type of service
	--ttl=<ttl>             specify <ttl> as time-to-live

sudo ./bins/ft_ping --preload=3 --count=5 google.com

PING google.com (142.250.200.14): 56 data bytes
64 bytes from 142.250.200.14: icmp_seq=0 ttl=245 time=371.839 ms
64 bytes from 142.250.200.14: icmp_seq=1 ttl=245 time=385.130 ms
64 bytes from 142.250.200.14: icmp_seq=2 ttl=245 time=385.083 ms
64 bytes from 142.250.200.14: icmp_seq=3 ttl=245 time=385.020 ms
64 bytes from 142.250.200.14: icmp_seq=4 ttl=245 time=228.762 ms
--- google.com ping statistics ---
5 packets transmitted, 5 packets received, 0% packet loss, time 1461.2 ms
round-trip min/avg/max/stddev = 228.762/351.167/385.130/61.417 ms

sudo ./bins/ft_ping --count=3 --ttl=5 google.com

PING google.com (142.250.200.14): 56 data bytes
36 bytes from 1.17.3.109.rev.sfr.net (109.3.17.1): Time to live exceeded
36 bytes from 1.17.3.109.rev.sfr.net (109.3.17.1): Time to live exceeded
36 bytes from 1.17.3.109.rev.sfr.net (109.3.17.1): Time to live exceeded
--- google.com ping statistics ---
3 packets transmitted, 0 packets received, +3 fails, 100% packet loss, time 2083.3 ms
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
