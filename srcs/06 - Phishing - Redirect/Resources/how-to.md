# Phishing - Redirect

The `site` parameter on the redirect page _(accessible from social media links in the footer)_ is not protected, thus, we can create a link `a` which looks legitimate, send it to our target, so when our victim click on it, she will be redirected to our website _(phishing)_.

## How-To

1. Go to `/index.php?page=redirect&site=omg`

## Fix

- Use static link

	```html
	<a href="https://twitter.com/42">Twitter</a>
	<a href="https://facebook.com/42">Facebook</a>
	<a href="https://instagram.com/42">Instagram</a>
	```

- Validate `site` parameter before using it

	```php
	$socials = [
		'twitter' => 'https://twitter.com/42',
		'facebook' => 'https://facebook.com/42',
		'instagram' => 'https://instagram.com/42',
	];

	$site = $GET['site'] ?? '';

	if (array_key_exists($site, $socials))
	{
		header('Location: '. $socials[$site]);
		exit;
	}
	```

## Details

- Unless you collect some metrics, you do not need a page to redirect users, they are links _(`a`)_ to do that.

## Resources

- Wiki : [Phishing](https://en.wikipedia.org/wiki/Phishing)
- PHP : [header()](https://www.php.net/manual/en/function.header.php)
- PHP : [array_key_exists()](https://www.php.net/manual/en/function.array-key-exists)
