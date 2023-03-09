#!/bin/sh

# Set device mode
#curl "http://192.168.4.1/loopback";	echo
curl "http://192.168.4.1/hardware";	echo

# Send CAN FRAME (in BASE64 encoding)
#curl "http://192.168.4.1/write?len=21&data=9gAAAAiOhzL6Jo6%2bhg==";echo
#sleep 1
curl "http://192.168.4.1/write?len=21&data=AAAAAAAAAAAAAAAAAA==";echo
