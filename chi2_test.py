import numpy as np
from scipy.stats import chi2

# if the computed chi2 value less than critial value, null hypothesis true i.e random number are from uniform distribution.
array=[]
with open("VON_NEUMANN_10000.txt", "r") as ins:
    for line in ins:
        array.append(float(line))       # makes list out of the read numbers

n_bins=100.0                              # number of bins for frequency count
upper=1.0                                 # upper limit of random numbers
lower=0.0                                 # lower limit of random numbers
steps=(upper-lower)/n_bins
ranges=[]                       # all the ranges arranged in tuples
for i in range(100):
    ranges.append((lower+i*steps, lower+(i+1)*steps))

observed_counts=[0]*len(ranges)       # all elements of the list initialised to 0

for elem in array:
    for m in range(len(ranges)):
        if(elem>=ranges[m][0] and elem<ranges[m][1]):
            observed_counts[m]+=1.0
            break
        else:
            continue

unif_int=len(array)/n_bins
expected_counts=[unif_int]*len(ranges)
chi2_val=0.0
for r in range(len(ranges)):
    chi2_val+=((observed_counts[r]-expected_counts[r])**2)/(expected_counts[r]) # computes the chi^2 value

critical_val=chi2.ppf(q = 0.95, df = len(ranges)-1)                 # computes the critical value for the confidence interval
print "The critical value is: "+str(critical_val)
print "The chi2 value obtained is: "+str(chi2_val)
if chi2_val<critical_val: 
    print "The numbers generated are random enough, for the given confidence interval"
else: 
    print "The numbers generated are not random enough, try a different confidence interval"
    