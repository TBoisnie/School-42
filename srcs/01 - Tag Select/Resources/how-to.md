# Tag Select

We can modify `grade` to send a value which should not be allowed.

## How-To

1. Go to `/index.php?page=survey`
1. Inspect a `select` on the left
1. Modify the `value` attribute of any `option` tag

	```html
	<!-- From -->
	<option value="7">7</option>
	<!-- To -->
	<option value="10000">7</option>
	```

1. Select the modified `option` to trigger JS submit

## Fix

- Check the `valeur` field on server side

	```php
	$rate = filter_input(INPUT_POST, 'valeur', FILTER_VALIDATE_INT, [
		'options' => [
			'min_range' => 1,
			'max_range' => 10
		]
	]);
	```

## Details

- `select` tag allows us to choose from a predefined list of values _(like `radio`, `input` with `datalist`, etc)_, making the process of filling a form more user-friendly.However, it still be a user `input`, so you HAVE to validate it on server side.

## Resources

- MDN : [<select>](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/select)
- PHP : [filter_input()](https://www.php.net/manual/en/function.filter-input.php)
