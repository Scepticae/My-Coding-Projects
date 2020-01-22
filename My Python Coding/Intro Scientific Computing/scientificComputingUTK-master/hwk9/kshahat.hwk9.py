#!/usr/local/bin python3

#Kirolos Shahat
#NETID: kshahat
#Homework number 9
#
# Template script for Problem 14 from Problemt Set 6.1 (p. 214 of textbook)
#
from romberg import *
from numpy import *
import matplotlib.pyplot as plt

# The integrand function and what it would evaluate to
def f(x):
  # The function will evaluate to zero if x is zero
  if x == 0: return 0
  # If x is not zero then the integrand is (x^4 * e^x) / ((e^x - 1) ^ 2)
  else: return  (x**4 * exp(x))/((exp(x) - 1)**2)   # define the integrable function here

# The u values that the function will be evaluated with
u = arange(0,1.01,0.05)
print ("    u\t   g(u)")
gu = [] #list that will contain all of g(u)s (y-coordinates for your plot)

# Iterating through the u list
for i in u:
  # if the current i value is 0 then the integral will evaluate to 0
  if i == 0: g = 0.0;
  # Otherwise perform romberg integration
  else:
    I,nPanels = romberg(f, 0, 1/i)  # perform romberg integration on f here (get result in
                                    # I, nPanels is the number of panels used but is not
                                    # used for output).
    # g(i) is i^3 multiplied by the romberg integration of f(x)
    g = I * i**3          # evaluate g(i) here
  print ('{:6.2f}{:13.6f}'.format(i,g))
  gu.append(g)
#
# Place the code that creates the required plot using pylab here.
# Be sure to label axes and provide the same title as shown
# in the "prob6_1-14.png" image file on BB

# Setting the y axis label
plt.ylabel('g(u)')
# Setting the x axis label
plt.xlabel('u')
# Setting the graph title
plt.title('Problem 6.1.14')
# Plotting u and g(u) lists on the graph using a blue line
plt.plot(u, gu, 'b')
# Setting the ranges of the x and y axis
plt.axis([0.0, 1.0, 0.00, 0.35])
# Displaying the graph
plt.show()

#
# Table written to stdout for verification purposes:
#
#  u	     g(u)
# 0.00     0.000000
# 0.05     0.003247
# 0.10     0.025274
# 0.15     0.070997
# 0.20     0.122878
# 0.25     0.167686
# 0.30     0.202568
# 0.35     0.228858
# 0.40     0.248618
# 0.45     0.263608
# 0.50     0.275136
# 0.55     0.284136
# 0.60     0.291265
# 0.65     0.296992
# 0.70     0.301651
# 0.75     0.305487
# 0.80     0.308678
# 0.85     0.311359
# 0.90     0.313631
# 0.95     0.315573
# 1.00     0.317244
