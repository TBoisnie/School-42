# Cross-Site Scripting (Input)

We can inject code in the feedback `form` fields, which will be executed by anyone visiting the page in the future.

## How-To

1. Go to `/index.php?page=feedback`
2. Inspect the name `input` field
3. Modify it to allow more than 10 characters

	```html
	<!-- From -->
	<input name="txtName" type="text" size="30" maxlength="10">
	<!-- To -->
	<input name="txtName" type="text" size="30">
	```

4. Input `script` tag as name

	```html
	<!-- Works but does not reveal the flag -->
	<scRiPt> alert("Hi"); </sCripT>
	```

5. Input `script` as name or message will reveal the flag, which is stupid since it is not a breach...

## Fix

- Use a sanitize function to protect from user's `input`

	```php
	User : <?= htmlspecialchars($user) ?>
	Comment : <?= htmlspecialchars($comment) ?>
	```

## Details

- ...

## Resources

- MDN : [<input>](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/input)
- Wiki : [Cross-Site Scripting (XSS)](https://en.wikipedia.org/wiki/Cross-site_scripting)
- Owasp : [Cross-Site Scripting (XSS)](https://owasp.org/www-community/attacks/xss/)
