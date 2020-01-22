#!/usr/bin/python3

import sys

def corr_paren(filename):
  paren_count = 0

  f = open(filename)
  for line in f:
    extract = line.strip()
    for c in extract:
      if c == '(': paren_count += 1
      elif c == ')': paren_count -=1

      if paren_count < 0:
        print("Error: close paren before open")
        sys.exit()

  if paren_count > 0: print("Error: Still open parenthesis")
  else: print("Parenthesis were placed correctly.")

def main():
  corr_paren(sys.argv[1])

if __name__ == '__main__':
  main()
