#!/usr/local/bin/python3

# Kirolos Shahat
# August 2013 High Temps for Knoxville,TN
# Hwk 1 for COSC 370
#
from numpy import arange
import matplotlib.pyplot as plt
xData = arange(1,32)    # Ranges for x and y axes must match
tData = [86,87,84,86,86,86,84,83,90,89,88,85,86,79,83,81, \
         75,80,81,85,81,88,89,87,84,85,86,88,88,90,90]
avg = [86.]  # First value for monthly avg high temp is just Day 1 temp
## 1) CALCULATE A RUNNING MONTHLY AVERAGE AND PRINT IT OUT IN A TABLE
##    IT DOES NOT MATTER HOW THE TABLE IS FORMATTED
#we will start with the total number of days being 1
numDays = 1
#And the initial total temperature is just the first element of tData
totalTemp = tData[0]

#initializing the table view
print("Day |  High  | Average")
print("----------------------")
#printing out the first day high and average temperatures with the decimal precision being two
print("", numDays, " | ", "{0:.2f}".format(tData[numDays-1]), "|", "{0:.2f}".format(totalTemp))

#iterating over the elements in tData excluding the first because it is already included
for t in tData[1:]:
    #adding the current temperature to the total temperature
    totalTemp+= t
    #incrementing the total number of days
    numDays+=1
    #and the average of all of the temperatures is the current temp. total divided by the current days
    curAvg = totalTemp/numDays
    #adding the new average to the end of the list
    avg.append(curAvg)
    #updating the table with the current day's high temperature and the monthly average thus far
    print("", numDays, " | " if numDays < 10 else "| ", "{0:.2f}".format(tData[numDays-1]), "|", "{0:.2f}".format(curAvg))

## 2) CREATE A GRAPH FOR THE DATA USING MATPLOTLIB
##	- PLOT RED POINTS WITH BLUE LINE FOR ORIGINAL DATA
plt.plot(xData, tData, 'ro')
plt.plot(xData, tData, 'b-')
#plt.plot(tData, xData, )
##	- SHOW CHANGE IN AVERAGE HIGH WITH GREEN DASHED LINE
plt.plot(xData, avg, 'g--')
##	- SET DISPLAY RANGES FOR X AND Y AXES
##		- X SHOULD RANGE FROM 0 TO 32
##		- Y SHOULD RANGE FROM 70 TO 95
plt.axis([0,32,70,95])
##	- ENABLE GRID DISPLAY
plt.grid()
##	- LABEL AXES AND SET TITLE
plt.xlabel('Day') #x-axis
plt.ylabel('High Temp') #y-axis
plt.title('High Temperatures for Knoxville, TN - August 2013') #title
##  - USE MATPLOTLIB.PYPLOT.TEXT() TO LABEL THE MONTHLY AVERAGE LINE
plt.text(15, 86, "Monthly Avg", color="green")  # monthly average line title
plt.show()
