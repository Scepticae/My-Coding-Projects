#!/opt/local/bin/python3.3

# Samuel Leonard
# sleonar5
# Homework 1

# August 2013 High Temps for Knoxville,TN
# Hwk 1 for COSC 370


from numpy import arange
import matplotlib.pyplot as plt


xData = arange(1,32)    # Ranges for x and y axes must match
tData = [86,87,84,86,86,86,84,83,90,89,88,85,86,79,83,81, \
         75,80,81,85,81,88,89,87,84,85,86,88,88,90,90]
avg = [86.]  # First value for montly avg high temp is just Day 1 temp


## 1) CALCULATE A RUNNING MONTHLY AVERAGE AND PRINT IT OUT IN A TABLE
##    IT DOES NOT MATTER HOW THE TABLE IS FORMATTED
# Prints Out a Table for the Day, High Temperature and Running Monthly Average
print("\nAugust Daily Temperatures and Averages")
print("Day  High Temp(F)  Monthly Avg Temp(F)")
print('{:>2d}'.format(1), '{:>10.2f}'.format(tData[0]), '{:>16.2f}'.format(avg[0]))
tmp_total = tData[0]
for date in range(1, len(xData)):
    tmp_total = tmp_total + tData[date]
    tmp_avg = tmp_total / (date + 1)
    avg.append(tmp_avg)
    print('{:>2d}'.format(date + 1), '{:>10.2f}'.format(tData[date]), '{:>16.2f}'.format(avg[date]))


## 2) CREATE A GRAPH FOR THE DATA USING MATPLOTLIB
##	- PLOT RED POINTS WITH BLUE LINE FOR ORIGINAL DATA
# Plots the Data in a Graph for the Days of August vs. the High Temperatures
# Plots Points Using Red Circles and a Blue Line
plt.plot(xData, tData, 'ro', xData, tData, 'b')

##	- SHOW CHANGE IN AVERAGE HIGH WITH GREEN DASHED LINE
# Adds the Running Monthly Average Plot to the Graph
# Plots the Points Using a Dashed, Green Line
plt.plot(xData, avg, 'g--')

##	- SET DISPLAY RANGES FOR X AND Y AXES
##		- X SHOULD RANGE FROM 0 TO 32
##		- Y SHOULD RANGE FROM 70 TO 95
# Conforms the X-Axis between 0 and 32 and the Y-Axis between 70 and 95
plt.axis([0, 32, 70, 95])

##	- ENABLE GRID DISPLAY
# Function to Display Grid Lines on the Graph
plt.grid(True)

##	- LABEL AXES AND SET TITLE
# Displays the Title, Y-Axis Label, and X-Axis Label on the Graph
plt.title("High Temperatures for Knoxville, TN - August 2013")
plt.ylabel("High Temp")
plt.xlabel("Day")

##	- USE MATPLOTLIB.PYPLOT.TEXT() TO LABEL THE MONTHLY AVERAGE LINE
# Places the Monthly Avg Label in Green next to the Green, Dashed Line
plt.text(15, 86, 'Monthly Avg', color='green')

##  - SHOW THE GRAPH
# Function to Show or Display the Graph
plt.show()

# Keeps the Program Running until Return is Pressed
input("Press Return")