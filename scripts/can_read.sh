#!/bin/sh

# Set device mode
#curl "http://192.168.4.1/loopback";	echo
curl "http://192.168.4.1/hardware";	echo

# Recv CAN FRAME (in BASE64 encoding)
curl "http://192.168.4.1/read";
echo

