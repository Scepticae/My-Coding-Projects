#Samuel Leonard
#sleonar5
#HW 9
#tail.py

import sys

#Read in from file
with open(sys.argv[1], 'r') as f:
	read_data = f.readlines()

#Get the number of lines
x = len(read_data)
	
#Number of lines to read from end of file
n = sys.argv[2]

#Find the starting index
index = x - int(n)

for i in range(index, x):
	print read_data[i].strip()


