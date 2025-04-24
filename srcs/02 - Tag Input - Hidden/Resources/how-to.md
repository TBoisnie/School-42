# Tag Input - Hidden

We can modify `input` hidden value to send the recovery password to our email instead of the predefined one.

## How-To

1. Go to `/index.php?page=recover`
1. Inspect the submit `button`
1. Modify the `value` attribute of the `<input type='hidden' ...>` tag

	```html
	<!-- From -->
	<input type='hidden' name='mail' value='webmaster@borntosec.com' maxlength='15'>
	<!-- To -->
	<input type='hidden' name='mail' value='your-email@mail.com' maxlength='15'>
	```

1. Click on the submit `button`

## Fix

- Do not add mail as an `input` hidden field.
- Ask for the user to fill an `input` email field, and any other secret _(to avoid email spams in case email is corrupted)_.
- Check on server side wether using a database or an environment variable.

	```html
	<!-- Client -->
	<form action='#' method='POST'>
		<label for='username'>Username</label>
		<input type='text' name='username' id='username' required />
		<label for='email'>Email</label>
		<input type='email' name='email' id='email' required />
		<input type='submit' name='Submit' value='Submit' />
	</form>
	```

	```php
	// Server
	$username = $POST['username'];
	$email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_EMAIL, []);

	if ($email && $secret)
	{
		$password = bin2hex(random_bytes(16));
		$password_hash = password_hash($password, PASSWORD_DEFAULT);

		$stmt = $db->prepare("UPDATE users SET password=:password WHERE username=:username AND email=:email");
		$stmt->bindParam(':username', $username, PDO::PARAM_STR);
		$stmt->bindParam(':email', $email, PDO::PARAM_STR);
		$stmt->bindParam(':password', $password_hash, PDO::PARAM_STR);
		$stmt->execute();
		$updated = $stmt->rowCount();
		$stmt->closeCursor();

		if ($updated)
		{
			mail($email, 'Password Recovery', "New Password: $password");
		}
	}
	```

## Details

- Hidden `input` are like any `input`, their values are still modifiable from the user side, thus, you HAVE to validate it on server side.

## Resources

- MDN : [<input>](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input/hidden)
- PHP : [bin2hex()](https://www.php.net/manual/en/function.bin2hex.php)
- PHP : [filter_input()](https://www.php.net/manual/en/function.filter-input.php)
- PHP : [random_bytes()](https://www.php.net/manual/en/function.random-bytes)
- PHP : [mail()](https://www.php.net/manual/en/function.mail.php)
- PHP : [password_hash()](https://www.php.net/manual/en/ref.password.php)
- PHP : [PDO](https://www.php.net/manual/en/function.filter-input.php)
