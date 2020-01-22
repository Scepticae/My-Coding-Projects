"""
Samuel Leonard
COSC 420
Project 5
Particle Swarm Optimization
"""

import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FFMpegWriter
import celluloid as cell
import math

# Seed Random Generator
np.random.seed(619)


class World:
    # Constructor
    def __init__(self, size):
        self.width = self.set_range(size)
        self.height = self.set_range(size)
        self.max_dist = math.sqrt(math.pow((2 * size), 2) + math.pow((2 * size), 2)) / 2.0

    @staticmethod
    def set_range(s):
        low = -s
        high = s
        return low, high


class Particle:
    # Constructor
    def __init__(self, size):
        self.pos = np.array(self.init_pos(size))
        self.vel = np.array([0, 0])
        self.per_best = self.pos
        self.per_best_val = 0.0

    # Sets Particle Initial Position
    @staticmethod
    def init_pos(d):
        x = np.random.uniform(-d, d)
        y = np.random.uniform(-d, d)
        return x, y


# Calculate the Personal Best Position
def calc_best_pos1(p, m_dist):
    p_dist = math.sqrt(math.pow((p.pos[0] - 20), 2) + math.pow((p.pos[1] - 7), 2))
    qual_pos = 100 * (1.0 - (p_dist / m_dist))
    return qual_pos


# Calculate the Personal Best Position
def calc_best_pos2(p, m_dist):
    p_dist = math.sqrt(math.pow((p.pos[0] - 20), 2) + math.pow((p.pos[1] - 7), 2))
    n_dist = math.sqrt(math.pow((p.pos[0] + 20), 2) + math.pow((p.pos[1] + 7), 2))
    qual_pos = 9 * max(0.0, 10.0 - math.pow(p_dist, 2)) + 10 * (1.0 - (p_dist / m_dist)) + 70 * (1.0 - (n_dist / m_dist))
    return qual_pos


# Update Velocity
def update_vel(p, inert, cog, soc, g_best, max_vel):
    rand = np.random.random()
    rand2 = np.random.random()
    new_vel = np.array([0, 0])

    new_vel[0] = (inert * p.vel[0]) + (cog * rand) * (p.per_best[0] - p.pos[0]) + (soc * rand2) * \
        (g_best[0] - p.pos[0])
    new_vel[1] = (inert * p.vel[1]) + (cog * rand) * (p.per_best[1] - p.pos[1]) + (soc * rand2) * \
        (g_best[1] - p.pos[1])

    # Scale the Velocities
    velocity = math.pow(new_vel[0], 2) + math.pow(new_vel[1], 2)
    max_vel_squared = math.pow(max_vel, 2)
    if velocity > max_vel_squared:
        new_vel[0] = (max_vel / math.sqrt(velocity)) * new_vel[0]
        new_vel[1] = (max_vel / math.sqrt(velocity)) * new_vel[1]
    return new_vel


# Update Position
def update_pos(member):
    new_x = member.pos[0] + member.vel[0]
    new_y = member.pos[1] + member.vel[1]
    return new_x, new_y


# Main Program
def main():
    num_epochs = int(sys.argv[1])
    num = 0
    err_rate = False
    targ_err_rate = 0.01  # Error Rate that Suggests Convergence
    glob_best = np.array([0, 0])  # Keeps the Global Best Position
    glob_best_val = 0.0
    tmp_best_pos = np.array([0, 0])
    swarm = []
    error_x_arr = []  # Keeps the X error values
    error_y_arr = []  # Keeps the Y error values
    percent_conv = []  # Keeps track of Converged Particles

    # Plot and Camera Configurations
    title = "Epochs: " + sys.argv[1] + " Num_P: " + sys.argv[2] + " I: " + sys.argv[3] + " Cog: " + sys.argv[4] + \
            " Soc: " + sys.argv[5] + " Max_vel: " + sys.argv[7] + " Prob: " + sys.argv[8]
    fig = plt.figure()
    camera = cell.Camera(fig)
    plt.xlim(-50, 50)
    plt.ylim(-50, 50)
    plt.title(title, loc='center')

    # Initialize the World
    world = World(int(sys.argv[6]))

    # Create the Population
    for i in range(int(sys.argv[2])):
        new_member = Particle(int(sys.argv[6]))
        swarm.append(new_member)

    # Run through Number of Epochs
    while num != num_epochs and err_rate is False:
        tmp_best_val = 0.0
        error_x = 0.0
        error_y = 0.0
        conv_parts = 0

        # Calculate the Position Quality for Each Particle
        for member in swarm:
            if int(sys.argv[8]) == 1:
                quality = calc_best_pos1(member, world.max_dist)
            else:
                quality = calc_best_pos2(member, world.max_dist)

            # Check for New Personal Best
            if quality > member.per_best_val:
                member.per_best_val = quality
                member.per_best = member.pos

            # Keep the Quality Value
            if member.per_best_val > tmp_best_val:
                tmp_best_val = member.per_best_val
                tmp_best_pos = member.per_best

        # Check to See if Personal Best is a Global Best
        if tmp_best_val > glob_best_val:
            glob_best_val = tmp_best_val
            glob_best = tmp_best_pos

        # Calculate Velocity and Update Position
        for member in swarm:
            # Update the Velocity
            member.vel = update_vel(member, float(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5]), glob_best,
                                    int(sys.argv[7]))

            # Update Position
            member.pos = update_pos(member)

            # Add the Error for x and y
            member_error_x = math.pow((member.pos[0] - glob_best[0]), 2)
            member_error_y = math.pow((member.pos[1] - glob_best[1]), 2)
            error_x += member_error_x
            error_y += member_error_y

            # Check if Particle is Close to Global Best
            if member_error_x <= 0.1 and member_error_y <= 0.2:
                conv_parts += 1

        # Calculate Percentage and Save in Array Converged Particles
        p_conv = conv_parts / int(sys.argv[2])
        percent_conv.append(p_conv)

        # Compute Average Error for x and y
        error_x = math.sqrt((1 / (2 * int(sys.argv[2]))) * error_x)
        error_x_arr.append(error_x)
        error_y = math.sqrt((1 / (2 * int(sys.argv[2]))) * error_y)
        error_y_arr.append(error_y)

        # Check if the Error Rates Indicate Convergence
        if error_x < targ_err_rate and error_y < targ_err_rate:
            err_rate = True

        # Build Animation for Particle Swarm
        plt.plot(20, 7, 's', color='black')
        if int(sys.argv[8]) == 2:
            plt.plot(-20, -7, 's', color='red')
        for i in swarm:
            plt.scatter(i.pos[0], i.pos[1])
        camera.snap()

        num += 1

    # Save the Animation File
    animation = camera.animate()
    # animation.save('pso2_14.html')

    # Create Graph for Error Rate vs Iterations
    error_fig = plt.figure()
    plt.title(title, loc='center')
    plt.plot(error_x_arr, color='black', label='error_x')
    plt.plot(error_y_arr, color='red', label='error_y')
    plt.legend()
    # plt.savefig('err2_14.png')

    # Create Graph for Percentage of Converged Particles
    converged_fig = plt.figure()
    plt.title(title, loc='center')
    plt.plot(percent_conv, color='blue', label='percent_conv')
    plt.legend()
    # plt.savefig('part_conv2_14.png')
    plt.show()

    # Print the Best Value, Best Position
    print(glob_best_val, glob_best)


# Runs Main Program
if __name__ == '__main__':
    main()
