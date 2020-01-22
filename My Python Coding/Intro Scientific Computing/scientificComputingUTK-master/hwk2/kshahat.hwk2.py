#!/usr/local/bin/python3

# Kirolos Shahat

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
#tolerance of the solution
TOL = 1.0e-6
err = 0
n = 0
while err < TOL:
  n +=1
  a = zeros((n,n),dtype=float64)
  b = zeros((n),dtype=float64)
  soln = ones((n), dtype=float64) # The correct solution is all 1's

  # Use the loops below to define the matrix 'a' and vector 'b':
  for i in range(n):
    for j in range(n):
      #the element Aij is equal to 1 divided by the sum of the row number and column number plus 1
      #to make it 1 indexed rather than 0 indexed. No need to cast the elements into floats
      #due to the automatic conversion into type float by division operator
      a[i,j] = 1/(i + j + 1)
      #Bi is the sum of all of the column elements of row i in the matrix A
      b[i] += a[i, j]

  # Call appropriate functions from the LUdecomp.py module to
  # solve the equations A x = b with the b-vector being overridden
  # by the solution vector x.

  #Getting the LU decomposition matrix that is equal to the matrix A
  a = LUdecomp(a)
  #Solving using the LU decomposition direct method
  b = LUsolve(a,b)

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
