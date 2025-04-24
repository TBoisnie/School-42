# .htpasswd

We can access `.htpasswd` file, which contains admin credentials in a non-secure form, allowing us to connect on the `/admin` page.

## How-To

1. Go to `/robots.txt`
1. Go to `/whatever/`
1. Open file `htpasswd`

	```
	root:437394baff5aa33daa618be47b75cb49
	```

1. Reverse hash the password using a MD5 reverse table

	```
	437394baff5aa33daa618be47b75cb49 => qwerty123@
	```

1. Go to `/admin`
1. Login using previous credentials

	```
	username: root
	password: qwerty123@
	```

## Fix

- Do not store use `MD5` to encrypt password, it is NOT secure !
- Use a `.htaccess` file to deny access to `.htpasswd` file.

	```txt
	# /whatever/.htaccess
	deny from all
	```

## Details

- `.htpasswd` is used to store HTTP credentials, however, since it is in a non-secure form, we shouldn't be allowed to access it from the web.
- `.htaccess` is a file used to modify server configuration at directory level _(restraint files access, rewrite URL, ...)_.
- `/admin` is just a commonly used path to access administation panel.

## Resources

- Apache : [.htpasswd](https://httpd.apache.org/docs/2.4/programs/htpasswd.html)
- Apache : [.htaccess](https://httpd.apache.org/docs/2.4/howto/htaccess.html)
- Decrypt : [MD5 Decrypt](https://md5decrypt.net/)
