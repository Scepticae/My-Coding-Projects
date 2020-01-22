#Samuel Leonard
#sleonar5
#HW 9
#golfer.py

class Golfer():
	def __init__(self):
		self.name = 'golfer'
		self.scores = []
		self.hcap = 0
		
	def setTuple(self, diff, date):
		#Set up a tuple
		t = (diff, date)
		
		#Place the tuple in the list
		self.scores.append(t)
		
	def calcHcap(self):
		justScores = []
		avgScore = 0.0
		
		#Sort the scores according to date
		self.scores = sorted(self.scores, key = lambda t: t[1], reverse = True)
		
		#Strip the 20 most recent
		recentScores = self.scores[0:20]
		
		#Create a list with only the scores
		for k in recentScores:
			justScores.append(k[0])
		
		#Sort the scores in ascending order and get the 10 lowest
		justScores.sort()
		justScores = justScores[0:10]
		
		#Get the average score
		for k in justScores:
			avgScore = avgScore + k
		
		#Set the handicap
		self.hcap = (avgScore / 10) * 0.96
		
class Course:
	def __init__(self):
		self.name = 'course'
		rating = 0.00
		slope = 0.00