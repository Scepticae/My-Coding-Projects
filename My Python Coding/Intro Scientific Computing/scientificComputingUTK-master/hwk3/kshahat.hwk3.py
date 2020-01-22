#!/usr/local/bin python3

#Kirolos Shahat
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
#k1 = k2 = k3 = k5 = 1
#k2 = k5 = 2
k   =  array([1, 2, 1, 1, 2],float)
#W1 = W3 = 2
#W2 = 1
W   =  array([2, 1, 2],float)
a   =  zeros((3,3))

#A =[   [(k1 + k2 + k3 + k5)      -k3          -k5   ]
#       [         -k3           (k3+k4)        -k4   ]
#       [         -k5             -k4       (k4 + k5)]  ]

a[0,0] =  k[0] + k[1] + k[2] + k[4]
a[0,1] =  -k[2]
a[1,0] =  -k[2]
a[0,2] =  -k[4]
a[2,0] =  -k[4]
a[1,1] =  k[2] + k[3]
a[1,2] =  -k[3]
a[2,1] =  -k[3]
a[2,2] =  k[3] + k[4]
#since A = A^T we can use the choleski decomposition to solve the system effeciently
L = choleski(a)
x = choleskiSol(L,W)
print("Displacements are (in units of W/k):\n\n",x)
print("--------------------------------------------")

## problem2_2_17
######################################################
# 1. Populate a and b below with the values from
#    problem 17 on page 82.
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

#the resistance in the network
R = [5.0, 10.0, 20.0]
#iterating through each resistance
for r in R:
   a = zeros([3,3])
   #converting the equations into 3x3 Matrix A
   a[0,:] = array([50 + r, -r, -30], float)
   a[1,:] = array([-r, 65 + r, -15], float)
   a[2,:] = array([-30, -15, 45], float)
   #the right hand side of the system
   b = array([0,0,120], float)
   print("\nR =",r,"ohms")
   #solving the system using gaussian elimination
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

a = zeros([4,4])
#Converting the equatioins into a 4x4 matrix A by combining like terms
a[0,:] = array([50 + 30, -50, -30, 0], float)
a[1,:] = array([-50, 50 + 15 + 25 + 10, -10, -25], float)
a[2,:] = array([-30, -10, 30+10+20+5, -20], float)
a[3,:] = array([0, -25, -20, 20 + 25 + 10 + 30 + 15], float)
#the right hand side of the system
b = array([-120, 0, 0, 0], float)
#solving the system using gaussian elimination
print("The currents are (in amps):\n",gaussElimin(a,b))

input("Press return to exit")
