# Samuel Leonard
# COSC 420
# Project 4
# Genetic Algorithms

import sys
import numpy as np
import matplotlib.pyplot as plt
from random import getrandbits, seed
from math import pow


# Holds the command line args
class DataInputs:
    # Constructor
    def __init__(self, l, n, g, p_m, p_c, gen_seed, exp):
        self.l = l
        self.n = n
        self.g = g
        self.p_m = p_m
        self.p_c = p_c
        self.gen_seed = gen_seed
        self.exp = exp

        # Seed the Random Number Generator
        np.random.seed(int(self.gen_seed))
        seed(int(self.gen_seed))


# Defines the Bit-String Characteristics
class BitString:
    # Constructor
    def __init__(self, n_data):
        self.int_val = int(getrandbits(n_data.l))
        self.bit_string = (str(bin(self.int_val))[2:]).zfill(n_data.l)
        self.fit_score = 0.0
        self.norm_val = 0.0
        self.run_tot = 0.0
        self.str_length = n_data.l

    # Calculate Fitness
    def calc_fit(self):
        # Plug Integer Value in Fitness Function
        fit_val = pow((self.int_val / pow(2, self.str_length)), 10)
        return fit_val


# Normalize the fit values for each N
def norm_fit(p, tot_fit):
    tmp = 0.0
    for num in p:
        num.norm_val = num.fit_score / tot_fit

        # Set Each Bit String's Run Total
        tmp += num.norm_val
        num.run_tot = tmp


# Selects the parents
def select_parents(p):
    selected = False  # Determines whether Parents have been Selected
    num1 = False
    num2 = False

    # Get the First Parent
    rand_1 = np.random.uniform()
    for i in p:
        if rand_1 <= i.run_tot:
            num1 = p.index(i)
            break
    # Get the Second Parent
    while selected is False:
        rand_2 = np.random.uniform()
        for i in p:
            if (rand_2 <= i.run_tot) and (p.index(i) != num1):
                i.used = True
                num2 = p.index(i)
                selected = True
                break
    # Return the Indices of the Parents
    return num1, num2


# Performs Crossover if Needed
def crossover(par, p, dat):
    child1 = BitString(dat)
    child2 = BitString(dat)
    cross_check = np.random.uniform()

    # Check to see if Crossover is done
    if cross_check <= dat.p_c:
        # Get the Crossover Bit
        rand_bit = np.random.randint(0, dat.l)

        # Copy the Bit Strings to Crossover Point
        child1.bit_string = p[par[0]].bit_string[:rand_bit] + p[par[1]].bit_string[rand_bit:]
        child2.bit_string = p[par[1]].bit_string[:rand_bit] + p[par[0]].bit_string[rand_bit:]
    else:
        child1.bit_string = p[par[0]].bit_string
        child2.bit_string = p[par[1]].bit_string

    # Perform Bit Mutation if Necessary
    child1.bit_string = bit_flip(child1.bit_string, dat)
    child2.bit_string = bit_flip(child2.bit_string, dat)

    # Convert to Integer Value
    child1.int_val = int(child1.bit_string, base=2)
    child2.int_val = int(child2.bit_string, base=2)

    # Calculate New Fitness Score
    child1.fit_score = child1.calc_fit()
    child2.fit_score = child2.calc_fit()

    # Return Children
    return child1, child2


# Performs Mutation if Needed
def bit_flip(p, dat):
    l_p = list(p)
    for i in range(dat.l):
        rand_mut = np.random.uniform()
        if rand_mut <= dat.p_m:
            if p[i] == '1':
                l_p[i] = '0'
            else:
                l_p[i] = '1'
    p = ''.join(l_p)
    return p


# Initialize Population
def build_pop(dat_inputs):
    new_pop = []
    for i in range(dat_inputs.n):
        new_string = BitString(dat_inputs)
        new_string.fit_score = new_string.calc_fit()
        new_pop.append(new_string)
    return new_pop


# Calculate the Total Fitness
def total_fitness(population):
    tmp_total = 0.0
    for i in population:
        tmp_total += i.fit_score
    return tmp_total


# Display the different fitness values
def output_fit(p, dat, n_gen):
    f = open("ga_data.csv", "a")
    f.write("l:  " + str(dat.l) + "\n")
    f.write("N:  " + str(dat.n) + "\n")
    f.write("G:  " + str(dat.g) + "\n")
    f.write("P_m:  " + str(dat.p_m) + "\n")
    f.write("P_c:  " + str(dat.p_c) + "\n")
    f.write("#Exp:  " + str(dat.exp) + ",  #Gen:  " + str(n_gen) + "\n")
    f.write("Individual, Fitness Value, Normalized Fitness, Running Total\n")
    for i in p:
        f.write(str(p.index(i)) + "," + str(format(i.fit_score, '5g')) + "," + str(format(i.norm_val, '5g')) + "," + str(format(i.run_tot, '5g')) + "\n")
    f.write("\n\n")
    f.close()


# Find the Statistics
def find_gen_stats(p, tot_fit, dat):
    best_fit = 0.0
    bit_count = 0
    avg_bit_count = 0.0

    # Find Average Fitness
    avg_fit = tot_fit / dat.n
    # Find Best Individual Fitness
    for x in p:
        if x.fit_score > best_fit:
            best_fit = x.fit_score

        # Count Number of Correct Bits for Individual
        corr_bits = list(x.bit_string)
        for i in corr_bits:
            if i == '1':
                bit_count += 1
        avg_bit_count += bit_count / dat.l
    avg_corr_bits = avg_bit_count / dat.n
    return avg_fit, best_fit, avg_corr_bits


# Main Function
def main():
    # Read in the inputs
    dat_inputs = DataInputs(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]), float(sys.argv[4]),
                            float(sys.argv[5]), int(sys.argv[6]), int(sys.argv[7]))
    avg_fits = []
    best_fits = []
    bit_counts = []

    # Initialize the Population
    population = build_pop(dat_inputs)

    # Calculate the Total Fitness
    tot_fit = total_fitness(population)

    # Calculate the Norms
    norm_fit(population, tot_fit)

    # Display Initial Statistics
    ret_stats = find_gen_stats(population, tot_fit, dat_inputs)
    avg_fits.append(ret_stats[0])
    best_fits.append(ret_stats[1])
    bit_counts.append(ret_stats[2])

    # Write First Generation Stats to CSV File
    output_fit(population, dat_inputs, 0)

    # Run the Number of Generations
    for num_gen in range(dat_inputs.g - 1):
        new_pop = []

        # Do for Each Pair within the Generation
        for num_pair in range(int(dat_inputs.n / 2)):
            # Selection of Parents
            parents = select_parents(population)

            # Check and Perform Crossover if Needed
            children = crossover(parents, population, dat_inputs)
            new_pop.append(children[0])
            new_pop.append(children[1])

        # Update the Population
        tot_fit = total_fitness(new_pop)
        norm_fit(new_pop, tot_fit)
        population = new_pop

        # Find Statistics for Generation
        ret_stats = find_gen_stats(population, tot_fit, dat_inputs)
        avg_fits.append(ret_stats[0])
        best_fits.append(ret_stats[1])
        bit_counts.append(ret_stats[2])

        # Write Generation Results to CSV File
        output_fit(population, dat_inputs, num_gen + 1)

    # Create Graphs
    avg_fit_graph = plt.figure()
    plt.plot(avg_fits)
    plt.title('Average Fitness vs. Generations')
    plt.xlabel('Generations')
    plt.ylabel('Average Fitness')

    best_fit_graph = plt.figure()
    plt.plot(best_fits)
    plt.title('Best Fitness vs. Generations')
    plt.xlabel('Generations')
    plt.ylabel('Best Fitness')

    correct_bit_graph = plt.figure()
    plt.plot(bit_counts)
    plt.title('Correct Bits vs. Generations')
    plt.xlabel('Generations')
    plt.ylabel('Correct Bits')

    # Save Graphs
    avg_fit_graph.savefig("avg_fit_" + str(dat_inputs.exp) + "_" + str(dat_inputs.gen_seed) + ".png")
    best_fit_graph.savefig("best_fit_" + str(dat_inputs.exp) + "_" + str(dat_inputs.gen_seed) + ".png")
    correct_bit_graph.savefig("bit_count_" + str(dat_inputs.exp) + "_" + str(dat_inputs.gen_seed) + ".png")


main()



