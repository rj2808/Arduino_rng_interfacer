t = 1
n = 0
A = 0
p=1
lower=0
upper=1
output_array=[]
def user_choice():
	global p, lower, upper
	lower = raw_input("Enter the lower limit of the range: ")
	upper = raw_input("Enter the upper limit of the range: ")
	p=log(upper, 2)

t1 = time.time()
while n < 30 :
	while t :
        bytes_serial_monitor=arduino.readline()
        if len(bytes_serial_monitor)>=p:
            q=lower+(upper-lower)*int(bytes_serial_monitor[-p:],2)
        #bytesavailable = arduino.inWaiting()
        #if bytesavailable >= p :
        #q = lower+(upper-lower)*int(str(arduino.read(p)), 2)/(2.0**p - 1.0)
        #arduino.flush()
        t = 0
	t=1
	A+=q
	q=0
	n += 1
t2 = time.time()
print t2 - t1
print A/30
