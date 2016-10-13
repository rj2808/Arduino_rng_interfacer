

import serial, time
arduino = serial.Serial('/dev/cu.usbmodem1411', 19200, timeout=.01)

time.sleep(1) #give the connection a second to settle
bytesToRead = arduino.inWaiting()
print bytesToRead
data = arduino.read(bytesToRead)
if data:
	print data #strip out the new lines for now
		# (better to do .read() in the long run for this reason

