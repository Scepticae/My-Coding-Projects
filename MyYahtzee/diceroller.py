import numpy as np
import die_graphics as dg
from graphics import GraphWin, Point

class Dice_roller:
    num_dice = 0
    die = []

    def __init__(self, num):
        self.num_dice = num
        self.die = np.zeros(num)

    def roll_dice(self):
        for die in range(self.num_dice):
            self.die[die] = np.random.randint(1, 7)

# Driver for Dice Roller
def main():
    die_number = 0
    choice = True
    dice = []

    # Test the Window Display
    win = GraphWin("My Graphics Window", 1600, 600)
    win.setBackground('red')

    # Test the User Input for Number of Dice
    die_number = int(input('Enter number of dice to roll: '))
    my_dice = Dice_roller(die_number)

    # Get Dice Graphic for Number of Dice
    for i in range(die_number):
        die = dg.Dice(100)
        dice.append(die)

    # Test Rolling and Displaying Dice
    choice = int(input('Enter 1 to roll dice or 0 to quit: '))
    while choice == True:
        for j in range(5):
            offset = 0
            my_dice.roll_dice()
            for i in range(die_number):
                dice[i].draw_dice(win, Point(200 + offset, 200), int(my_dice.die[i]))
                offset = offset + 120
        choice = int(input('Enter 1 to roll again or 0 to quit: '))

if __name__ == "__main__":
    main()