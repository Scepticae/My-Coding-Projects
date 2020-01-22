import sys

class State:
	def __init__(self):
		self.edges = []

class EClose:
	def __init__(self):
		self.marked = 0
		self.eTs = []

#Define the E-Closure function
def e_Closure(st, e, eInput):
	stack = []
	tmp = []
	T = []
	#Put the State in T
	for x in st:
		tmp.append(x)
		T.append(int(x))

	#Put States in the Stack
	for numEl in st:
		stack.append(int(numEl))
	
	#Put all states in T that have epsilon closures
	while len(stack) > 0:
		num = stack.pop()
		for el in e[num-1].edges[eInput-1]:
			if el not in tmp:
				if el is not '':
					tmp.append(el)
					stack.append(int(el))
					T.append(int(el))

	return T

#Variables
i = 0
states = []
fStates = []
iState = []
dStates = []
inSet = []

#Reads in the NFA
for line in sys.stdin:
	a = line.strip()

	#Gets the initial state
	if i == 0:
		b = a.split(':')
		b = b[1].strip()
		iState.append(b)
	#Stores the final states
	elif i == 1:
		fsHeader = line
		c = a.split(':')
		p = c[1].strip()
		rB = p.strip('{}')
		rB = rB.split(',')
		fStates.append(rB)
	#Gets the total number of states
	elif i == 2:
		d = a.split(':')
		tStates = int(d[1])
	#Stores the number of inputs including epsilon
	elif i == 3:
		e = a.split()
		vLength = len(e)
		inputs = e[1:vLength]
		inHeader = line
	#Processes the rest of the input and builds the NFA
	else:
		f = a.split()
		newState = State()
		for n in f:
			n = n.strip('{}')
			n = n.split(',')
			newState.edges.append(n)
		states.append(newState)
	#Keeps a line count
	i += 1

#Create node for first dStates
ecclose = EClose()

#Calculate E-Closure for the initial state
ecclose.eTs = sorted(e_Closure(iState, states, vLength))
tmpSet = ecclose.eTs

#Put first set of states T in dStates
dStates.append(ecclose)

#Create sub-set construction
checked = 0
done = 0
while checked == 0:
	dStates[done].marked = 1
	tmpSet = dStates[done].eTs
	for each in range(1,vLength-1):
		for sEl in tmpSet:
			if states[sEl-1].edges[each] is not ['']:
				for allEdges in states[sEl-1].edges[each]:
					if allEdges not in str(tmpSet):
						if allEdges not in str(inSet):
							inSet.append(allEdges)
		ecclose = EClose()
		ecclose.eTs = sorted(e_Closure(inSet, states, vLength))
		if ecclose.eTs != []:
			if ecclose.eTs not in dStates:
				dStates.append(ecclose)
		inSet = []
	checked = 1
	for checkMark in dStates:
		if checkMark.marked == 0:
			checked = 0
	done = done + 1
	
	#fail safe for program running too long
	if done == 20:
		checked = 1

#Prints the output of the executable
print 'reading NFA ... done.'
print ''
print 'creating corresponding DFA ...'
j = 1
for y in dStates:
	print 'new DFA state:  ' + str(j) + '     -->  {' + str(y.eTs) + '}'
	j = j + 1
print ''
print 'final DFA:'
print 'Initial State: ' + str(iState)
print fsHeader + 'Total States:   ' + str(tStates)
print inHeader