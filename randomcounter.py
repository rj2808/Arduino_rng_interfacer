count_0=0
count_1=0
out = 01010011100101001100

string = str(out)
for elem in string :
	if elem == "1": 
		count_1 += 1
	elif elem == "0": 
		count_0 += 1

print count_1
print count_0
 
