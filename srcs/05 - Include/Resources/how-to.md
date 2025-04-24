# Include

The `page` GET attribute uses an unprotected `include`, allowing us to modify it and access other file, or, in even worse case, access a reverse-shell.

## How-To

1. Access `/index.php?page=../../../../../../../etc/passwd`

## Fix

- Check `$GET['page']` before using it to include partial

	```php
	$pages = [
		'index' => 'pages/home',
		'survey' => 'pages/survey',
		'home' => 'pages/home',
		'member' => 'users/member'
	];
	$page = $GET['page'] ?? 'index';

	if (array_key_exists($page, $pages))
	{
		include($pages[$page]. '.php');
	}
	else
	{
		include('errors/404.php');
	}
	```

## Details

- The `/etc/passwd` file typically has file system permissions that allow it to be readable by all users of the system (world-readable).

## Resources

- Wiki : [/etc/passwd](https://en.wikipedia.org/wiki/Passwd)
- PHP : [array_key_exists()](https://www.php.net/manual/en/function.array-key-exists.php)
