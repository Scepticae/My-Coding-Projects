# Author: Samuel Leonard
# Class: COSC 420
# NetID: sleonar5
# Assignment: Activation/Inhibition Cellular Automaton

import sys
from math import pow, log2
import random
import numpy as np

# Global Variables
cor = np.zeros(15, dtype=np.float)  # Correlation
mi = np.zeros(15, dtype=np.float)  # Mutual Information
ent = np.zeros(15, dtype=np.float)  # Entropy
n_squared = 900  # Accounts for 30 by 30 matrix elements
coeff2 = 1.0 / n_squared

# Parameter variables
r1 = 0
r2 = 0
j1 = 0
j2 = 0
h = 0
exp_name = "default"
heats = 4
timeout = 0

# Setup initial array and initialize to ones
mat = (30, 30)  # 30x30 Matrix Array
mat = np.ones(mat, dtype=np.int)  # Initially Filled with Ones


# Random State Selector
def rand_num():
    num = random.randint(0, 1)
    if num == 0:
        return -1
    else:
        return num


# Populates the Matrix with Random 1 or -1 values
def pop_array():
    for y in range(30):
        for x in range(30):
            mat[y][x] = rand_num()


# Prints the Pixel Values to the .pgm File
def pix_val():
    s = "P2\n30 30\n255\n"
    for y in range(30):
        for x in range(30):
            if mat[y][x] == -1:
                s += "255 "
            else:
                s += "0 "
        s += "\n"
    return s


# Calculates the Distance between Cells
def calc_dist(xcell1, xcell2, ycell1, ycell2):
    adj_x = abs(xcell2 - xcell1)
    if adj_x > 15:  # Adjusts for Torsion
        adj_x = 30 - adj_x
    adj_y = abs(ycell2 - ycell1)
    if adj_y > 15:  # Adjusts for Torsion
        adj_y = 30 - adj_y
    return adj_x + adj_y


# Calculate Mutual Information
def calc_mi(je, ce):
    mutual_info = (2 * ce) - je
    return mutual_info


# Calculate the Average Cell Entropy
def calc_ent(nums):
    prob_plus1 = coeff2 * nums
    prob_minus1 = 1 - prob_plus1
    if prob_plus1 == 0:
        h_s = -1 * (prob_minus1 * log2(prob_minus1))
    elif prob_minus1 == 0:
        h_s = -1 * (prob_plus1 * log2(prob_plus1))
    else:
        h_s = -1 * ((prob_plus1 * log2(prob_plus1)) + (prob_minus1 * log2(prob_minus1)))
    return h_s


# Calculate the Joint Entropy
def calc_j_ent(pe, ne, ent_dist):
    ent_pos = (1 / (n_squared * 4 * ent_dist)) * pe
    ent_neg = (1 / (n_squared * 4 * ent_dist)) * ne
    neg_pos_ent = 1 - ent_pos - ent_neg
    if ent_pos == 0:
        h_l = -1 * ((ent_neg * log2(ent_neg)) + (neg_pos_ent * log2(neg_pos_ent)))
    elif ent_neg == 0:
        h_l = -1 * ((ent_pos * log2(ent_pos)) + (neg_pos_ent * log2(neg_pos_ent)))
    elif ent_pos == 0 and ent_neg == 0:
        h_l = -1 * (neg_pos_ent * log2(neg_pos_ent))
    else:
        h_l = -1 * ((ent_pos * log2(ent_pos)) + (ent_neg * log2(ent_neg)) + (neg_pos_ent * log2(neg_pos_ent)))
    return h_l


# Calculates the Correlation for Distances between Cells
def calc_cor():
    sum_ones = 0
    sum_i = 0
    # Loop that Iterates through the 14 Possible Radii
    for rad in range(15):
        sum_ij = 0
        pos_sum = 0
        neg_sum = 0
        # Loop through Each Cell i
        for y in range(30):
            for x in range(30):
                if rad == 0:
                    sum_i += mat[y][x]  # Sums all the i Cells for Correlation
                    # Calculate the Probability of Cell Being a One
                    if mat[y][x] == 1:
                        sum_ones += 1
                else:
                    # Loop through Each Cell j
                    for y2 in range(30):
                        for x2 in range(30):
                            # Check for Duplicate Counts
                            dist = calc_dist(x, x2, y, y2)
                            # Add Cell Value to Correlation Array
                            if dist == rad:
                                cell_prod = mat[y][x] * mat[y2][x2]
                                sum_ij += cell_prod
                                # Sum the Positive and Negative State Entropy
                                if mat[y][x] == 1 and mat[y2][x2] == 1:
                                    pos_sum += 1
                                elif mat[y][x] == -1 and mat[y2][x2] == -1:
                                    neg_sum += 1
        # Correlation Formula for Calculation
        if rad > 0:
            c_length = 4.0 * rad
            coeff1 = 1.0 / (n_squared * c_length)
            first_coeff = coeff1 * sum_ij
        else:
            first_coeff = 1
        second_coeff = pow((coeff2 * sum_i), 2)
        # Calculate Correlation for Given Distance
        cor[rad] += abs(first_coeff - second_coeff)
        # Calculate Joint Entropy for Given Distances
        if rad == 0:
            entropy = calc_ent(sum_ones)
            ent[rad] += entropy
            mi[rad] += entropy
        else:
            temp = calc_j_ent(pos_sum, neg_sum, rad)
            ent[rad] += temp
            mi[rad] += calc_mi(temp, entropy)


# Updates the AICA with New States until Stabilized
def update_grid():
    global timeout
    flag = 0  # Checks for State Change
    while flag == 0:
        updated = list(range(900))  # Keeps a list of indices that need updated
        # Picks random non-updated cell and processes it based on other cells
        while len(updated) > 0:
            nearval = 0  # Holds Summed Values for Radius 1
            farval = 0  # Holds Summed Values for Radius 2
            cell_choice = random.choice(updated)  # Randomly Chooses Cell for Update
            cell_index = mat_pos(cell_choice)  # Finds the Cell Index, Returns Tuple
            xval = cell_index[0]
            yval = int(cell_index[1])
            for y in range(30):
                for x in range(30):
                    sel_rad = calc_dist(xval, x, yval, y)
                    if sel_rad != 0:
                        if sel_rad < r1:  # Puts Value in Near Field
                            nearval += mat[y][x]
                        elif sel_rad < r2:  # Puts Value in Far Field
                            farval += mat[y][x]
            state_change = calc_state_change(nearval, farval)
            temp = mat[yval][xval]  # Holds Cell State Before Update
            if state_change >= 0.0:
                mat[yval][xval] = 1
            else:
                mat[yval][xval] = -1
            if flag == 0:  # Checks to See if Cell Value Changed
                flag = check_prev_state(yval, xval, temp)
            updated.remove(cell_choice)  # Removes Updated Cell from List
        if flag == 0:  # If No Cell was Updated then Quit Outer Loop
            flag = 1
        else:  # Continue Loop if at Least One Cell was Updated
            flag = 0
    # Check for all black or all white
    count = 0
    for m in range(30):
        for n in range(30):
            if mat[m][n] == 1:
                count += 1
    # Calculate the Correlation after Stabilized Pattern
    if count == 900 or count == 0:
        timeout += 1
        if timeout == 10:
            exit(-1)
        pop_array()
        update_grid()
    else:
        calc_cor()


# Calculates the State Change for a Selected Cell
def calc_state_change(nv, fv):
    jval1 = nv * j1
    jval2 = fv * j2
    new_state = jval1 + jval2 + h
    return new_state


# Calculates the Matrix Cell Position from 1D Array
def mat_pos(cell_num):
    remainder = cell_num % 30
    num = cell_num - remainder
    val = num / 30
    return [remainder, val]


# Checks to see if Previous State was Different from New Value
def check_prev_state(yv, xv, tmp):
    if mat[yv][xv] != tmp:
        return 2
    else:
        return 0


# Average the Calculations
def avg_calcs():
    for i in range(15):
        cor[i] = cor[i] / heats
        ent[i] = ent[i] / heats
        mi[i] = mi[i] / heats


# Writes the Grid Information to a File for Display
def disp_grid():
    filename = exp_name + ".pgm"
    f = open(filename, "w")
    f.write(pix_val())


# Writes Calculations to Excel File
def output_calcs():
    f = open("myCalcs.csv", "a")
    f.write(exp_name + ",")
    f.write("R1=" + str(r1) + ",")
    f.write("R2=" + str(r2) + ",")
    f.write("J1=" + str(j1) + ",")
    f.write("J2=" + str(j2) + ",")
    f.write("h=" + str(h) + "\n")
    f.write("Distance,")
    f.write("rho_l,")
    f.write("H_l,")
    f.write("I_l\n")
    for i in range(15):
        f.write(str(i) + ",")
        f.write(str(cor[i]) + ",")
        f.write(str(ent[i]) + ",")
        f.write(str(mi[i]) + "\n")
    f.close()


# Main Function;
def main():
    global r1
    global r2
    global j1
    global j2
    global h
    global exp_name
    # Run a determined number of times for averages
    r1 = int(sys.argv[1])
    r2 = int(sys.argv[2])
    h = int(sys.argv[3])
    j1 = int(sys.argv[4])
    j2 = int(sys.argv[5])
    exp_name = "Exp_" + sys.argv[6]
    for i in range(heats):
        pop_array()
        update_grid()
    avg_calcs()
    disp_grid()
    output_calcs()


# Main Function Call
main()