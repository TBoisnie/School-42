# Level 09

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level09@192.168.1.32
	Password: 25749xKZ8L7DkSCwJkT9dyv6f
	```

1. Check files.

	```sh
	> ls -l
	total 12
	-rwsr-sr-x 1 flag09 level09 7640 Mar  5  2016 level09
	----r--r-- 1 flag09 level09   26 Mar  5  2016 token
	```

1. Same thing as previous level, let's run it.

	```sh
	> ./level09
	You need to provied only one arg.
	```

1. Well, unlike previously, we now have to provide an argument, so let's check `token`

	```sh
	> cat token | hd
	00000000  66 34 6b 6d 6d 36 70 7c  3d 82 7f 70 82 6e 83 82  |f4kmm6p|=..p.n..|
	00000010  44 42 83 44 75 7b 7f 8c  89 0a                    |DB.Du{....|
	0000001a
	```

1. Fine, looks like a random token value, but contains some binary data, so can't really use it for now. Go back to our `level09` executable.

	```sh
	> ./level09 token
	tpmhr

	# Looks like it is incrementing characters by their position
	> ./level09 aaaaaaaaaaaaaaaaaaaaaaa
	abcdefghijklmnopqrstuvw

	# Maybe using it on "token" content
	> ./level09 $(cat token) | hd
	00000000  66 35 6d 70 71 3b 76 83  45 8b 89 7b 8e 7b 91 91  |f5mpq;v.E..{.{..|
	00000010  54 53 95 57 89 90 95 a3  a1 0a                    |TS.W......|
	0000001a
	```

1. Nah. But we are right about the logic, every byte is incremented by its position. What about reversing it ?

	```sh
	# Start by getting content as HEX
	> cat token | hexdump -e '32/1 "%02x " "\n"'
	66 34 6b 6d 6d 36 70 7c 3d 82 7f 70 82 6e 83 82 44 42 83 44 75 7b 7f 8c 89 0a

	# The last character has to be ignore since it is "0x0a" a.k.a. `\n` (line feed) in ASCII

	# Now decrement each values
	> INDEX=0; for x in $(cat token | hexdump -e '32/1 "%02x " "\n"' | sed 's/[[:space:]]*$//' | rev | cut -d ' ' -f 2- | rev); do printf "%02x " $((16#$x - INDEX)); INDEX=$((INDEX + 1)); done; echo
	66 33 69 6a 69 31 6a 75 35 79 75 65 76 61 75 73 34 31 71 31 61 66 69 75 71

	# Convert each HEX to ASCII
	> INDEX=0; for x in $(cat token | hexdump -e '32/1 "%02x " "\n"' | sed 's/[[:space:]]*$//' | rev | cut -d ' ' -f 2- | rev); do printf "\x$(printf %x $((16#$x - INDEX)))"; INDEX=$((INDEX + 1)); done; echo
	f3iji1ju5yuevaus41q1afiuq
	```

1. Get the flag.

	```sh
	> su flag09
	Password: f3iji1ju5yuevaus41q1afiuq
	Don't forget to launch getflag !

	> getflag
	Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
	```

## Documentation

- Command: [hexdump](https://man7.org/linux/man-pages/man1/hexdump.1.html)
- Command: [sed](https://man7.org/linux/man-pages/man1/sed.1.html)
- Command: [rev](https://man7.org/linux/man-pages/man1/rev.1.html)
- Command: [cut](https://man7.org/linux/man-pages/man1/cut.1.html)
- Command: [printf](https://www.man7.org/linux/man-pages/man1/printf.1.html)
