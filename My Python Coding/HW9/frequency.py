#Samuel Leonard
#sleonar5
#HW 9
#frequency.py

import sys

#Read in the file
with open(sys.argv[1], 'r') as f:
	read_data = f.read()
	
#Break the string up into individual words and get number
#of words
words = read_data.split()
x = len(words)

#create a dictionary
tel = {words[0]: 1}

for i in range(1, x):
	if words[i] in tel:
		tel[words[i]] = tel[words[i]] + 1
	else:
		tel[words[i]] = 1

#Sort the dictionary by values and print the pairs using
#correct format		
for k, v in sorted(tel.iteritems(), key = lambda(k,v):(v,k)):
	print k.ljust(20), str(v).rjust(5)