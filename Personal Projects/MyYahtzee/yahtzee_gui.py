from tkinter import *

class Game_Gui:
    def __init__(self, master):
        self.scorecard = Frame(master, width=250, bg="#ffffaa")
        self.gameboard = Frame(master, height=800, width=900, bg="#00bbff")
        self.game_label = Label(self.gameboard, text="Yahtzee", font=("revue 150 bold"), bg="#00bbff", fg="white")
        self.dice_canvas = Canvas(self.gameboard, width=790, height=150, bg="#00bbff", relief="raised")
        self.keep_panel = Frame(master, width=250, bg="#ffffaa")
        self.scorecard.pack(side=LEFT, fill=Y)
        self.gameboard.pack(side=LEFT, fill=BOTH, expand=True)
        self.keep_panel.pack(side=LEFT, fill=Y)
        self.game_label.pack(side=TOP, pady=(150, 20))
        self.dice_canvas.pack()

        self.die = self.dice_canvas.create_rectangle((0,0,150,150), fill="darkred")
        self.die_dot = self.dice_canvas.create_oval((60,60,90,90), fill="white")

        self.die2 = self.dice_canvas.create_rectangle((160,0,310,150), fill="white")
        self.die_dot2a = self.dice_canvas.create_oval((180,20,210,50), fill="darkred")
        self.die_dot2b = self.dice_canvas.create_oval((260,100,290,130), fill="darkred")

        self.die3 = self.dice_canvas.create_rectangle((320,0,470,150), fill="darkred")
        self.die_dot3a = self.dice_canvas.create_oval((340,20,370,50), fill="white")
        self.die_dot3b = self.dice_canvas.create_oval((420,100,450,130), fill="white")
        self.die_dot3c = self.dice_canvas.create_oval((380,60,410,90), fill="white")

        self.die4 = self.dice_canvas.create_rectangle((480,0,630,150), fill="white")
        self.die_dot4a = self.dice_canvas.create_oval((500,20,530,50), fill="darkred")
        self.die_dot4b = self.dice_canvas.create_oval((580,20,610,50), fill="darkred")
        self.die_dot4c = self.dice_canvas.create_oval((500,100,530,130), fill="darkred")
        self.die_dot4d = self.dice_canvas.create_oval((580,100,610,130), fill="darkred")

        self.die5 = self.dice_canvas.create_rectangle((640,0,790,150), fill="darkred")

def main():
    root = Tk()
    root.title("Yahtzee")
    root.geometry("1400x800")

    game = Game_Gui(root)

    root.mainloop()

if __name__ == "__main__":
    main()