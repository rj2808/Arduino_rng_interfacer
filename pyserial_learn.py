import serial, time, sys
arduino = serial.Serial('/dev/cu.usbmodem1421', 250000, timeout=.01)
import numpy as np

#time.sleep(1) #give the connection a second to settle
#bytesToRead = arduino.inWaiting()
#print bytesToRead
#data = arduino.read(bytesToRead)	
#if data:
#	print data #strip out the new lines for now
		# (better to do .read() in the long run for this reason
A = 0
t1 = time.time()
while n < 30 :
	while 1 :
		q = Random(16)
		if q != 0 :
			A += q
			q = 0
			break
	n += 1
t2 = time.time()
print t2 - t1
print A/30


def Random(p) :
	while 1 :
		bytesavailable = arduino.inWaiting()
		if bytesavailable >= p :
			q =  int(str(arduino.read(p)), 2)/(2.0**p - 1.0)
			arduino.flush()
			return q

