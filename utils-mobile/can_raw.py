#!/usr/bin/python3

from base64 import b64decode as b64d
from requests import get
from time import sleep
from os import system as e
from time import ctime
from json import dumps
from binascii import hexlify as hexd

CAN_SET_MODE = "http://192.168.4.1/hardware"	# Set Hardware Mode
CAN_READ_CMD = "http://192.168.4.1/read"

mode = get(CAN_SET_MODE)
print("Mode Set:  {}".format(mode.text))

can_raw_frames = {}
counter = 0

def decode_frame(frame):
	global counter
	can_raw_frames.update({counter:hexd(frame).decode()})
	print("\tID: {} -> DATA: {}".format(counter, can_raw_frames[counter]))
	counter += 1

e('clear')

while True:
	data = get(CAN_READ_CMD)
	try:
		frame = b64d(data.text)
		decode_frame(frame)
		sleep(0.05)

	except KeyboardInterrupt as kbi:
		with open("raw.log", "wb") as log:
			log.write(dumps(can_raw_frames).encode())
		print("[+] Raw Log Dumped")
		break

	except 	Exception as ex:
		print("[!] Oh shoot -> {}".format(ex))
		pass
