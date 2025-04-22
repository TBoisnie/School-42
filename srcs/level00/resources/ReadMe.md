# Level 00

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine

	```
	ssh -p 4242 level00@192.168.1.32
	Password: level00
	```

1. Check files

	```sh
	> pwd
	/home/user/level00

	> ls -laRth
	.:
	total 12K
	dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
	-r-xr-x---+ 1 level00 level00 3.5K Aug 30  2015 .bashrc
	d--x--x--x  1 root    users    340 Aug 30  2015 ..
	-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
	-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
	```

1. Nothing interesting here, so let's try with `find`

	```sh
	> find / -user $USER 2> /dev/null
	/dev/pts/0
	...
	/proc/2254/io
	```

1. Still nothing interesting... Maybe with our target `$USER` a.k.a. `flag00`

	```sh
	> find / -user flag00 2> /dev/null
	/usr/sbin/john
	/rofs/usr/sbin/john

	> cat /usr/sbin/john
	cdiiddwpgswtgt

	> cat /rofs/usr/sbin/john
	cdiiddwpgswtgt
	```

1. Great! We found something. Let's try it as `flag00` password

	```sh
	> su flag00
	Password: cdiiddwpgswtgt
	su: Authentication failure
	```

1. It might be encoded, let's just type it into `google.com` to see what it says

	```
	https://www.google.com/search?q=cdiiddwpgswtgt
	```

1. First result is about `Caesar Cypher`, so let's try to decode using this method

	```
	https://www.dcode.fr/chiffre-cesar

	->15 (<-11)	nottoohardhere
	->14 (<-12)	opuuppibseifsf
	->2 (<-24)	abggbbunequrer
	...
	```

1. The first result makes sence!

	```
	nottoohardhere
	```

1. Switch user

	```sh
	> su flag00
	Password: nottoohardhere
	Don't forget to launch getflag !
	```

1. Get the flag

	```sh
	> getflag
	Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
	```

## Documentation

- Command: [ls](https://man7.org/linux/man-pages/man1/ls.1.html)
- Command: [find](https://man7.org/linux/man-pages/man1/find.1.html)
- Command: [cat](https://man7.org/linux/man-pages/man1/cat.1.html)
- Command: [su](https://man7.org/linux/man-pages/man1/su.1.html)
