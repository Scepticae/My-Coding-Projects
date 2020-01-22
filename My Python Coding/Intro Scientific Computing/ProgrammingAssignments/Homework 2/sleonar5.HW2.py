#!/usr/bin/env python3

# Samuel Leonard
# sleonar5
# HW 2

# ASSIGNMENT DESCRIPTION
# This script uses LU Decomposition on a Hilbert matrix
# to determine the largest n for which the solution holds
# within six significant figures of the actual solution.

####################################################################
# problem2_1_15  (Problem Set 2.1, No. 15 on page 53 of textbook)
# This problem requires the LUdecomp.py module (provided).
#
# Fill in the following template. Add the code that creates the
# Matrix (a) and the vector (b). Then add the code that computes
# the LU decomposition and produces a solution vector (see the
# provided LUdecomp.py module for correct function calls to do that).
####################################################################

from numpy import zeros, ones, array, float64, inf
from numpy import linalg
from LUdecomp import *

norm = linalg.norm  # Python allows you to rename functions.
                    # Here, 'linalg.norm' is renamed to just 'norm'.
TOL = 1e-6  # Sets the tolerance allowable for the solution
err = 0
n = 0
while err < TOL:
  n += 1
  a = zeros((n,n),dtype=float64)
  b = zeros((n),dtype=float64)
  soln = ones((n), dtype=float64) # The correct solution is all 1's
  
  # Use the loops below to define the matrix 'a' and vector 'b':
  
  # Creates the coefficient matrix and b vector 
  for i in range(n):
    for j in range(n):

      a[i,j] = 1/(i+j+1)  # Stores the values for the coefficient matrix
      b[i] = b[i] + a[i,j]  # Stores the b-vector values

  # Call appropriate functions from the LUdecomp.py module to
  # solve the equations A x = b with the b-vector being overridden
  # by the solution vector x.

  # Computes the LU Decomposition and Overrides the 'a' matrix
  a = LUdecomp(a)
  
  # Produces the Solution Vector and Overrides the 'b' vector
  b = LUsolve(a, b)

  #
  # Your solution should be stored in 'b' (if you used a 
  #  different variable name, modify the code below accordingly).
  #
  print("\n", n, " equations. ", "The solution is:\n", b)
  err = norm(b-soln, ord=inf)
  print("Error (inf-norm of difference)): ", err)

print("^^^(Greater than TOL = ", TOL, ")^^^\n")
print("********************************************\n")
print("Max number of equations while error remains less than ", TOL, " is: ", n-1, "\n") 
print("********************************************")
