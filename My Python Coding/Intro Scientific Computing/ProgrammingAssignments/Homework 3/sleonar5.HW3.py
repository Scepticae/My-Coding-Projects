#!/usr/bin/env python3

# Samuel Leonard
# sleonar5
# Homework 3

# ASSIGNMENT DESCRIPTION
# Using Choleski LU Decomposition solve for the displacements in problem 12
# Using Gaussian Elimination Solve for the Currents in Amperes for
# problems 17 and 18.

#######################################################
# probs2_2.py
# 
# Scripts corresponding to problems 12, 17, and 18 on
# pages 79-82.
######################################################
from numpy import array,zeros
from choleski import *
from gaussElimin import *

## problem2_2_12
######################################################
# 1. Populate k, W, and a below with the values from
#    problem 12 on page 79.
#
# Correct Output: 
# [ 1.66666667  2.66666667  2.66666667]
#
######################################################

s = 1.0  # Spring Stiffness
w = 1.0  # Weight

# Creates the Stiffness and Weight Arrays
k = array([s, 2*s, s, s, 2*s],float)
W = array([2*w, w, 2*w],float)

# Builds a 3x3 Matrix with Elements of 0
a = zeros((3,3))

# Populates the Matrix Elements with the 'k' values
a[0,0] = k[0] + k[1] + k[2] + k[4]
a[0,1] = -k[2]
a[1,0] = -k[2]
a[0,2] = -k[4]
a[2,0] = -k[4]
a[1,1] = k[2] + k[3]
a[1,2] = -k[3]
a[2,1] = -k[3]
a[2,2] = k[3] + k[4]

# Performs the 'L' portion of the Choleski Decomposition and
# Stores in 'L'
L = choleski(a)

# Uses L Matrix and W vector to solve for the Displacements
# and stores the solution vector in 'x'
x = choleskiSol(L,W)

# Displays the Results
print("Displacements are (in units of W/k):\n\n",x)
print("--------------------------------------------")


## problem2_2_17
######################################################
# 1. Populate a and b below with the values from
#    problem 17 on page 82.
#
# Correct Outputs:
# R = 5.0 ohms
# The currents are (in amps):
# [ 2.82926829 1.26829268 4.97560976]
# R = 10.0 ohms
# The currents are (in amps):
# [ 2.66666667 1.33333333 4.88888889]
# R = 20.0 ohms
# The currents are (in amps):
# [ 2.4516129 1.41935484 4.77419355]
#
######################################################

# 'R' stores an array with the different Ohm values
R = [5.0, 10.0, 20.0]

# Populates the Matrix for the different ohm values and
# solves for the currents using Gaussian Elimination
for r in R:
   a = zeros([3,3])
   a[0,:] = [50.0 + r, -r, -30.0]
   a[1,:] = [-r, 65.0 + r, -15.0]
   a[2,:] = [-30.0, -15.0, 45.0]
   b = array([0.0, 0.0, 120.0])  # Stores the 'b' vector
   
   # Displays the results for each ohm value tested
   print("\nR =",r,"ohms")
   print("The currents are (in amps):\n",gaussElimin(a,b))
print("--------------------------------------------")

## problem2_2_18
######################################################
# 1. Populate a and b below with the values from
#    problem 18 on page 82.
#
# Correct Output:
# The loop currents are (in amps):
# [-4.18239492 -2.66455194 -2.71213323 -1.20856463]
######################################################


# Builds a 4x4 matrix and fills it with 0's
a = zeros([4,4])

# Populates each row of the 'a' matrix using values from
# problem 18 and solves for the currents in amperes
a[0,:] = [80.0, -50.0, -30.0, 0.0]
a[1,:] = [-50.0, 100.0, -10.0, -25.0]
a[2,:] = [-30.0, -10.0, 65.0, -20.0]
a[3,:] = [0.0, -25.0, -20.0, 100.0]
b = array([-120.0, 0.0, 0.0, 0.0])  # Stores the 'b' vector

# Displays the Results
print("The currents are (in amps):\n",gaussElimin(a,b))

input("Press return to exit")
