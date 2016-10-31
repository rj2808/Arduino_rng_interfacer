import serial, time, sys
import matplotlib.pyplot as plt
import math
class mySerial(serial.Serial):
    def __del__(self):
        pass
arduino = mySerial('/dev/cu.usbmodem1421', 115200)
import numpy as np

time.sleep(1) #give the connection a second to settle
#bytesToRead = arduino.inWaiting()
#print bytesToRead
#data = arduino.read(bytesToRead)	
#if data:
#	print data #strip out the new lines for now
		# (better to do .read() in the long run for this reason
v = arduino.read()
print v

def random1(p):
	#arduino.reset_input_buffer()

	while 1 :
		bytesavailable = arduino.inWaiting()
		arduino.write(str(chr(4)))

		#print bytesavailable
		#bytesavailable = arduino.readline()

		if (bytesavailable) >= p :
			#q = int(bytesavailable[-p:], 2)
			q =  int(str(arduino.read(p)), 2)/(2.0**p - 1.0)
			time.sleep(.1)
			if q < 0 :
				continue
			break
	return q


timer = np.array([0])
p = np.array([])
n = 0
A = np.array([10])
t1 = time.time()
while n < 10 :
	#propensity = .0001 * A[n]
	p = np.append(p, [random1(16)])
	#q = (-1/propensity)*math.log(p[n])
	#timer  = np.append(timer, timer[n] + [q])
	#A = np.append(A, [A[n] - 1]) 
	#print timer[n]
	print n

	n += 1
t2 = time.time()
print t2 - t1
#plt.plot(timer, A)
plt.hist(p, 'auto')
plt.show()
arduino.close()

