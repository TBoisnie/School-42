# HTTP Header

We can set custom `Referer` and `User-Agent` HTTP Header to access the flag.

## How-To

1. Go to `/?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f` (link in the footer)
1. Inspect code

	```html
	...
	<!--
	You must come from : "https://www.nsa.gov/".
	-->
	...
	<!--
	Let's use this browser : "ft_bornToSec". It will help you a lot.
	-->
	...
	```

1. Use the following command

	```sh
	curl --referer 'https://www.nsa.gov/' --user-agent 'ft_bornToSec' 'http://192.168.56.106/index.php?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f' | grep flag
	```

## Fix

- Do no really on HTTP Header values.

## Details

- At first I thought the link was a flag, but it is not a security breach, just a link...

## Resources

- MDN : [Referer](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Referer)
- MDN : [User Agent](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/User-Agent)
- Curl : [Referer](https://everything.curl.dev/http/modify/referer.html)
- Curl : [User Agent](https://everything.curl.dev/http/modify/user-agent.html)
