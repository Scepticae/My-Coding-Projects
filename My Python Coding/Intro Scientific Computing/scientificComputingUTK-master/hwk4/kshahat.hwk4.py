#!/usr/local/bin python3

#Kirolos Shahat
# prob2-3-19 (hwk #4)
#
#  Problem 2.3.19 (pg. 101)
#
#  1) Implement the Ax(v) function below so that it will initialize
#     and return the matrix-vector product Ax, where A is given at
#     the top of page 101 in the textbook.
#
#  2) Use the provided conjGrad.py module to solve the system described
#     in problem #19 (uncomment and fill in the '??' lines).
#
# The correct solution is:
#
# [ 21.42857143 38.39285714  57.14285714   47.32142857   75.
#   90.17857143 92.85714286 124.10714286 128.57142857]
#
########################################################################

from numpy import zeros,array,linalg
from conjGrad import *

# Refer to pg. 101 for what the matrix Ax should be

def Ax(v):
    Ax = zeros((9))*1.0
    # fill in the 9 rows of Ax
    #Defining matrix multiplication of Ax with V based off of the matrix in problem statement
    Ax[0] = -4.0 * v[0] + 1.0 * (v[1] + v[3])
    Ax[1] = -4.0 * v[1] + 1.0 * (v[0] + v[2] + v[4])
    Ax[2] = -4.0 * v[2] + 1.0 * (v[1] + v[5])
    Ax[3] = -4.0 * v[3] + 1.0 * (v[0] + v[4] + v[6])
    Ax[4] = -4.0 * v[4] + 1.0 * (v[1] + v[3] + v[5] + v[7])
    Ax[5] = -4.0 * v[5] + 1.0 * (v[2] + v[4] + v[8])
    Ax[6] = -4.0 * v[6] + 1.0 * (v[3] + v[7])
    Ax[7] = -4.0 * v[7] + 1.0 * (v[4] + v[6]  + v[8])
    Ax[8] = -4.0 * v[8] + 1.0 * (v[5] + v[7])
    return Ax

b = array([0,0,100,0,0,100,200,200,300])*(-1.0)
x = zeros((9))*1.0
tol = 1e-06

#Conjugate Gradient Method being called with the parameters Ax as the function
#x being the temperature variables and b being the - solution vector, and a 1e-06 tolerance.
s1,numIter = conjGrad(Ax, x, b, 1e-06)
print("\nThe solution is:\n",s1)
print("\nNumber of iterations =",numIter, "using Tol: ", 1e-06)

print("\n CG Convergence Test")
print("Iterations   Tolerance")
#
# Use the loop below to call conjGrad with various tolerances,
# compare the number of iterations.
#
for tol in [1e-02, 1e-04, 1e-06, 1e-08, 1e-10, 1e-12, 1e-14, 1e-16]:
  x = zeros((9),dtype=float)
  #calling the conjGrad function with a varying tolerance and printing out the new solutions.
  s2,numIter = conjGrad(Ax, x, b, tol)
  print('%6d      %8.1e'%(numIter,tol))

print("\nError between vectors obtained with tol=1e-06 and tol=1e-16: ", linalg.norm(s1-s2), "\n")
