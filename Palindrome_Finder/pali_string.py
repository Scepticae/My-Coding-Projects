#!/usr/bin/python3

# Read in string from user
def read_input():
  text = input()
  return text

# Find the largest palindrome
def find_pali(t):
  # Iterate through each occurrance of current letter
  for letter in range(len(t)):
    # Compare letters from current letter to first occurrance
    # with letters from first occurrance to current letter
    for b_letter in reversed(range(letter, len(t))):
      print(t[letter], t[b_letter])
      # At any point there is not a match exit from loop
  # Keep the longest string or strings

# Print the string or strings to display
def print_str(s):
  print(s)

# Main Program Driver for Testing
def main():
  pali_str = read_input()
  find_pali(pali_str)
  print_str(pali_str)

# babal

if __name__=='__main__':
  main()
