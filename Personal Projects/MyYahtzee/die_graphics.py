from graphics import *

class Dice:
    def __init__(self, size):
        self.size = size
        self.rad = self.size * 0.1
        self.dot_color = 'black'
        self.die_color = 'white'

    def place_dots(self, die_num, a_point, b_point):
        if die_num == 1:
            self.dice1(a_point, b_point)
        elif die_num == 2:
            self.dice2(a_point, b_point)
        elif die_num == 3:
            self.dice3(a_point, b_point)
        elif die_num == 4:
            self.dice4(a_point, b_point)
        elif die_num == 5:
            self.dice5(a_point, b_point)
        else:
            self.dice6(a_point, b_point)

    def dice1(self, a_val, b_val):
        mod = ((b_val.x - a_val.x) / 2)
        dice_dot1 = Circle(Point(a_val.x + mod, a_val.y + mod), self.rad)
        dice_dot1.setFill(self.dot_color)
        self.dice_dots.append(dice_dot1)

    def dice2(self, a_val, b_val):
        mod = ((b_val.x - a_val.x) * 0.25)
        dice_dot1 = Circle(Point(a_val.x + mod, a_val.y + mod), self.rad)
        dice_dot2 = Circle(Point(b_val.x - mod, b_val.y - mod), self.rad)
        dice_dot1.setFill(self.dot_color)
        dice_dot2.setFill(self.dot_color)
        self.dice_dots.append(dice_dot1)
        self.dice_dots.append(dice_dot2)

    def dice3(self, a_val, b_val):
        self.dice1(a_val, b_val)
        self.dice2(a_val, b_val)

    def dice4(self, a_val, b_val):
        mod = ((b_val.x - a_val.x) * 0.25)
        dice_dot1 = Circle(Point(a_val.x + mod, a_val.y + mod), self.rad)
        dice_dot2 = Circle(Point(b_val.x - mod, a_val.y + mod), self.rad)
        dice_dot3 = Circle(Point(a_val.x + mod, b_val.y - mod), self.rad)
        dice_dot4 = Circle(Point(b_val.x - mod, b_val.y - mod), self.rad)
        dice_dot1.setFill(self.dot_color)
        dice_dot2.setFill(self.dot_color)
        dice_dot3.setFill(self.dot_color)
        dice_dot4.setFill(self.dot_color)
        self.dice_dots.append(dice_dot1)
        self.dice_dots.append(dice_dot2)
        self.dice_dots.append(dice_dot3)
        self.dice_dots.append(dice_dot4)

    def dice5(self, a_val, b_val):
        self.dice1(a_val, b_val)
        self.dice4(a_val, b_val)

    def dice6(self, a_val, b_val):
        mod = ((b_val.x - a_val.x) * 0.25)
        dice_dot1 = Circle(Point(a_val.x + mod, a_val.y + mod), self.rad)
        dice_dot2 = Circle(Point(b_val.x - mod, a_val.y + mod), self.rad)
        dice_dot3 = Circle(Point(a_val.x + mod, b_val.y - mod), self.rad)
        dice_dot4 = Circle(Point(b_val.x - mod, b_val.y - mod), self.rad)
        dice_dot5 = Circle(Point(a_val.x + mod, a_val.y + (2 *mod)), self.rad)
        dice_dot6 = Circle(Point(a_val.x + (3 * mod), a_val.y + (2 * mod)), self.rad)
        dice_dot1.setFill(self.dot_color)
        dice_dot2.setFill(self.dot_color)
        dice_dot3.setFill(self.dot_color)
        dice_dot4.setFill(self.dot_color)
        dice_dot5.setFill(self.dot_color)
        dice_dot6.setFill(self.dot_color)
        self.dice_dots.append(dice_dot1)
        self.dice_dots.append(dice_dot2)
        self.dice_dots.append(dice_dot3)
        self.dice_dots.append(dice_dot4)
        self.dice_dots.append(dice_dot5)
        self.dice_dots.append(dice_dot6)
    
    def draw_dice(self, win, a_point, die_num):
        self.dice_dots = []
        b_point = Point((a_point.x + self.size), (a_point.y + self.size))
        dice = Rectangle(a_point, b_point)
        dice.setFill(self.die_color)
        dice.draw(win)
        self.place_dots(die_num, a_point, b_point)
        for i in range(die_num):
            self.dice_dots[i].draw(win)

    def resize(self, new_size):
        self.size = new_size
        self.rad = self.size * 0.1
    
    def change_die_color(self, new_color):
        self.die_color = new_color
    
    def change_dot_color(self, new_dot_color):
        self.dot_color = new_dot_color

def main():
    # Test the Graphical Window
    win = GraphWin("My Graphics Window", 1600, 1000)
    win.setBackground('red')
    # Test creation of six dice with size 100 per side
    die1 = Dice(100)
    die2 = Dice(100)
    die3 = Dice(100)
    die4 = Dice(100)
    die5 = Dice(100)
    die6 = Dice(100)
    # Test 6 dice with different locations and numbers
    die1.draw_dice(win, Point(200, 200), 1)
    die2.draw_dice(win, Point(320, 200), 2)
    die3.draw_dice(win, Point(440, 200), 3)
    die4.draw_dice(win, Point(560, 200), 4)
    die5.draw_dice(win, Point(680, 200), 5)
    die6.draw_dice(win, Point(800, 200), 6)
    # Test same die different location
    die1.draw_dice(win, Point(200, 400), 1)
    # Test same die with different location and number
    die1.resize(200)
    die1.change_die_color('yellow')
    die1.change_dot_color('blue')
    die1.draw_dice(win, Point(320, 400), 3)
    die2.draw_dice(win, Point(540, 400), 3)
    win.getMouse()
    win.close()

if __name__ == "__main__":
    main()
