# Cookie

Cookie is not set with HttpOnly, nor Secure, so we can modify its value to be identified as an admin.

## How-To

1. Open `Dev Tools` _(F12)_
1. Go to `Storage` tab
1. Select `Cookies` on the left panel
1. Select `I_am_admin` cookie value
1. Decrypt it using MD5 reverse table

	```
	68934a3e9455fa72420237eb05902327 => false
	```

1. Encrypt `true` using MD5

	```
	true => b326b5062b2f0e69046810717534cb09
	```

1. Change the cookie value with the `true` as MD5
1. Refresh the page

## Fix

- Do not use MD5
- Use `sessions` to store critical informations on server side, never on client side
- Use `HttpOnly`, and `Secure` cookies.

	```php
	setcookie('name', 'value', $expires_at, $path, $domain, $secure = true, $httponly = true);
	```

## Details

- Cookies are not meant to store critical informations about users. Even more if they are not HttpOnly and Secure.

## Resources

- PHP : [Session](https://www.php.net/manual/en/book.session.php)
- PHP : [setcookie()](https://www.php.net/manual/en/function.setcookie.php)
