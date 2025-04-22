# Level 02

## Requirements

- [WireShark](https://www.wireshark.org/download.html)

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level02@192.168.1.32
	Password: f2av5il02puano7naaf6adaaf
	```

1. Checking files.

	```sh
	> pwd
	/home/user/level02

	> ls -laRth
	.:
	total 24K
	dr-x------ 1 level02 level02  120 Mar  5  2016 .
	-r-x------ 1 level02 level02 3.5K Aug 30  2015 .bashrc
	----r--r-- 1 flag02  level02 8.2K Aug 30  2015 level02.pcap
	d--x--x--x 1 root    users    340 Aug 30  2015 ..
	-r-x------ 1 level02 level02  220 Apr  3  2012 .bash_logout
	-r-x------ 1 level02 level02  675 Apr  3  2012 .profile
	```

1. Let's look at what is a `.pcap` file ?

	```
	PCAP files contain packet data of a network and are used to analyze the network characteristics.
	```

1. Fine, so we will need a software (like `WireShark`) to open and analyse it.

	```sh
	# Open a new terminal
	> cd ./level02/resources

	# Install WireShark
	> ./install.sh

	# Copy `~/level02.pcap` from target to attacker's machine
	> scp -P 4242 level02@192.168.1.32:~/level02.pcap .
	Password: f2av5il02puano7naaf6adaaf

	# Open with WireShark
	> wireshark -r level02.pcap
	```

1. After a quick scan, we can notice that there is only TCP communication. So let's first filter to hide the `ACK`s since they don't provide relevant informations here.

	```
	#On the top bar, apply the filter
	tcp.flags.push == 1
	```

1. Great, it's a bit cleaner. Now, just by looking through the packets' data, we notice something interesting.

	```
	# N	Time		Source			Destination		Protocol	Length	Info
	 43	13.827653	59.233.235.223	59.233.235.218	TCP			79		12121 → 39247 [PSH, ACK] Seq=215 Ack=186 Win=14496 Len=13 TSval=46283874 TSecr=18594183

	# HexDump
	0000   00 24 1d 0f 00 ad 08 00 27 cc 8a 1e 08 00 45 00   .$......'.....E.
	0010   00 41 d4 b3 40 00 40 06 16 77 3b e9 eb df 3b e9   .A..@.@..w;...;.
	0020   eb da 2f 59 99 4f ba a8 fb 18 9d 18 15 7b 80 18   ../Y.O.......{..
	0030   01 c5 27 9d 00 00 01 01 08 0a 02 c2 3c 62 01 1b   ..'.........<b..
	0040   b9 87 00 0d 0a 50 61 73 73 77 6f 72 64 3a 20      .....Password:
	```

1. Then, `59.233.235.218` send multiple packets to `59.233.235.223`. By combining those packets' data, we get:

	```
	# Hex
	66 74 5f 77 61 6e 64 72 7f 7f 7f 4e 44 52 65 6c 7f 4c 30 4c 0d

	# Converted to ASCII
	f t _ w a n d r <del> <del> <del> N D R e l <del> L 0 L
	```

1. LGTM! Let's try it.

	```sh
	> su flag02
	Password: ft_waNDReL0L
	Don't forget to launch getflag !
	```

1. Get the flag.

	```sh
	> getflag
	Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
	```

## Documentation

- Tool: [WireShark](https://www.wireshark.org/docs/)
- Tool: [ASCII Decoder](https://www.dcode.fr/ascii-code)
