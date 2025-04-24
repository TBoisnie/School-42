# File Flood

A flag is hidden in a bunch of directories / files, we just have to find it...

## How-To

1. Go to `/.robots.txt`
1. Go to `/.hidden`
1. Open a terminal and execute provided script

	```sh
	pip3 install requests beautifulsoup4 lxml
	python3 SuperFlagFinder.py "192.168.1.73"
	```

## Fix

- Use a `.htaccess` file

	```txt
	deny from all
	```

## Details

- Flooding with directories / files is useless, using scripts we can automate
the all search process, making the flood irrelevant.
- A first approach was to use `wget` to download all README files, then `grep`
for flag, but it was extremely slow.

	```sh
	mkdir "downloads"
	cd "$_"
	wget -r -np -nd -e robots=off -A "README*" http://192.168.1.73/.hidden/
	grep -r "flag" ./
	```

## Resources

- GNU : [wget](https://www.gnu.org/software/wget/)
- GNU : [grep](https://www.gnu.org/software/grep/)
- Python : [Python](https://www.python.org/downloads/)
- Python : [Requests](https://requests.readthedocs.io/en/latest/)
- Python : [BeautifulSoup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/)
