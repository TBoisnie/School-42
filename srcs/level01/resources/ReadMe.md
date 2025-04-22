# Level 01

## Requirements

- [JohnTheRipper](https://github.com/openwall/john)

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level01@192.168.1.32
	Password: x24ti5gi3x0ol2eh4esiuxias
	```

1. Checking files like in `level00` doesn't show anything interesting.

	```sh
	> pwd
	/home/user/level01

	> ls -laRth
	...

	> find / -user $USER 2> /dev/null
	...

	> find / -user flag01 2> /dev/null
	```

1. We are looking for a user's password, so let's check `/etc/shadow` and `/etc/passwd`.

	```sh
	> cat /etc/shadow
	cat: /etc/shadow: Permission denied

	> cat /etc/passwd
	root:x:0:0:root:/root:/bin/bash
	...
	level00:x:2000:2000::/home/user/level00:/bin/bash
	level01:x:2001:2001::/home/user/level01:/bin/bash
	level02:x:2002:2002::/home/user/level02:/bin/bash
	...
	flag00:x:3000:3000::/home/flag/flag00:/bin/bash
	flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
	flag02:x:3002:3002::/home/flag/flag02:/bin/bash
	...
	```

1. Amazing! We have something to work with. Since password are hashed, we need something to crack it. One of the most famous tool for it is called: John The Ripper.

	```sh
	# Open a new terminal
	> cd ./level01/resources

	# Install JohnTheRipper
	> ./install.sh

	# Copy `/etc/passwd` from target to attacker's machine
	> scp -P 4242 level01@192.168.1.32:/etc/passwd .
	Password: x24ti5gi3x0ol2eh4esiuxias

	# Use JohnTheRipper to crack the password
	> john ./passwd
	...
	abcdefg          (flag01)
	...
	```

1. Got it! We can now login.

	```sh
	> su flag01
	Password: abcdefg
	Don't forget to launch getflag !
	```

1. Get the flag.

	```sh
	> getflag
	Check flag.Here is your token : f2av5il02puano7naaf6adaaf
	```

## Documentation

- None
