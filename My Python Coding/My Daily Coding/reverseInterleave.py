#!/usr/bin/python3

from math import ceil

# Program Description:
# This program takes an array and reverse interleaves the second half
# of the array with the first half.

def reverseInterleave(n_array):
  n_queue = []

  # Populate the Queue
  for index in range(int(ceil(len(n_array)/2))):
    n_queue.append(n_array[index])
    n_queue.append(n_array[(len(n_array)-1)-index])

  # Dequeue items back in the array
  for index in range(len(n_array)):
    n_array[index] = n_queue.pop(0)

  return n_array


# Driver to test program
def main():
  str_array = ["Hello", "what", "you", "doing?", "are", "Sam"]
  numbers = [1, 2, 3, 4, 5, 6, 7]
  ri_strings = reverseInterleave(str_array)
  ri_numbers = reverseInterleave(numbers)
  print(ri_strings)
  print(ri_numbers)


if __name__ == "__main__":
  main()