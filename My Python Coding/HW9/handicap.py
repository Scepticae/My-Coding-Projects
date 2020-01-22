#Samuel Leonard
#sleonar5
#HW 9
#handicap.py

import sys
from datetime import date
from golfer import Golfer
from golfer import Course

#Method to calculate the score differential
def calcDiff(sc, r, sl):
	diff = (sc - r) * 113 / sl
	return diff

#Create empty dictionaries	
courses = {}
golfers = {}

#Read in from a the course file and assign the values
with open(sys.argv[2], 'r') as f:
	for line in f:
		rawData = line.strip().split()
		if rawData != []:
			if rawData[0] == 'Course':
				course = " "
				courseName = course.join(rawData[1:])
			elif rawData[0] == 'Rating':
				rating = float(rawData[1])
				slope = float(rawData[3])
				
				#Now that the course and the rating and slope have been
				#determined set the course object and put in dictionary
				newCourse = Course()
				newCourse.name = courseName
				newCourse.rating = rating
				newCourse.slope = slope
				
				#Put in the dictionary
				courses[newCourse.name] = newCourse
				
		else:
			del(line)
		
#Read in the golfer file
with open(sys.argv[1], 'r') as f:
	for line in f:
		golferInfo = line.split()
		
		#Get the size of golferInfo and a separator
		lineSize = len(golferInfo)
		spacer = " "
		
		#Get the Date, Name, Score and Course Name from score file
		scoreDate = date(int(golferInfo[2]), int(golferInfo[0]), int(golferInfo[1]))
		tempName = golferInfo[3]
		tempScore = int(golferInfo[4])
		
		#Piece together the course name
		tempCourse = spacer.join(golferInfo[5:])
		
		#Calculate the differential
		tempDiff = calcDiff(tempScore, courses[tempCourse].rating, courses[tempCourse].slope)
		
		#Create the Golfer and set the values
		newGolfer = Golfer()
		newGolfer.name = tempName
		
		#Search for person in dictionary, if there put new diff and date in
		#if not, create new dictionary entry
		if newGolfer.name in golfers:
			golfers[newGolfer.name].setTuple(tempDiff, scoreDate)
		else:
			newGolfer.setTuple(tempDiff, scoreDate)
			golfers[newGolfer.name] = newGolfer
		
	#Sort each golfer's scores in the dictionary by date
	sortedGolfers = []
	for v in golfers.values():
		v.calcHcap()
		sortedGolfers.append(v)
	
	#Sort and Print the list of golfers and their handicaps
	sortedGolfers = sorted(sortedGolfers, key = lambda v: v.hcap)
	for val in sortedGolfers:
		print '{:>5.2f}'.format(val.hcap) + " " + val.name
	
		