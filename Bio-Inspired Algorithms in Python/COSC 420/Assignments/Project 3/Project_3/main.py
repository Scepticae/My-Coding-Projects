"""
Author: Samuel Leonard
Net ID: sleonar5
Project: Hopfield Networks
"""

# Library Imports
import numpy as np
from random import choice
import matplotlib.pyplot as plt


# Constants
NUM_ELS = 50
NUM = 100
TRIES = 100

# Global Arrays
stability = np.zeros(NUM_ELS, dtype=np.float)
unstable = np.zeros(NUM_ELS, dtype=np.float)


# Initialize 50 vectors Range 0-99
def init_vectors():
    patterns = np.zeros((NUM_ELS, NUM), dtype=np.float)
    pattern = np.zeros(NUM, dtype=np.float)
    for n in range(NUM_ELS):
        for i in range(NUM):
            pattern[i] = choice([-1, 1])
        patterns[n] = pattern

    # Set the Weight Matrix
    set_weights(patterns)


# Compute the Weights
def set_weights(p):
    weights = np.zeros((NUM, NUM), dtype=np.float)

    # Use wij formula
    for n in range(NUM_ELS):
        s = np.outer(p[n], p[n])
        s -= np.identity(NUM)
        s /= NUM
        weights += s

        # Test for Pattern Stability
        test_stability(p, weights, n+1)


# Test the Stability
def test_stability(p, w, num_imp):
    global stability
    global unstable

    count = 0  # Set the count back to 0

    # Check All Patterns for Stability
    for n in range(num_imp):
        h = np.sign(np.dot(w, p[n]))
        h[h == 0.0] = 1.0
        if np.array_equal(p[n], h):
            count += 1

    # Calculate and Store the Number of Stable and Prob of Unstable
    prob_unstable = 1.0 - (count / num_imp)
    stability[num_imp-1] += count
    unstable[num_imp-1] += prob_unstable


# Generate Graphs
def gen_graphs():
    global stability
    global unstable

    # Plot Unstable Fraction
    img = plt.figure()
    plt.plot(unstable)
    plt.xlabel('p')
    plt.ylabel('Unstable')
    plt.show()
    # img.savefig("unstable.png")

    # Plot Number of Stable Patterns as Patterns Increase
    img1 = plt.figure()
    plt.plot(stability, 'r')
    plt.ylabel('Num Stable')
    plt.xlabel('p')
    plt.show()
    # img1.savefig("stable.png")


# Main
def main():
    global stability
    global unstable
    for i in range(TRIES):
        init_vectors()

    # Average the number of P tries
    stability /= TRIES
    unstable /= TRIES

    # Generate the Graphs
    gen_graphs()


# Call Main Function
if __name__ == '__main__':
    main()
