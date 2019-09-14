from tkinter import *
import tkinter.messagebox as mb

def doNothing():
    print("Click Worked")

# Creates the main window
root = Tk()
root.geometry("500x500")

menu = Menu(root)
root.config(menu=menu, bg="lightgray")

submenu = Menu(menu)
menu.add_cascade(label="File", menu=submenu)

submenu.add_command(label="New Project", command=doNothing)
submenu.add_command(label="New", command=doNothing)
submenu.add_separator()
submenu.add_command(label="Exit", command=root.quit)

editMenu = Menu(menu)
menu.add_cascade(label="Edit", menu=editMenu)

editMenu.add_command(label="Redo", command=doNothing)

# Create the Toolbar
toolbar = Frame(root, bg="blue")
insertButton = Button(toolbar, text="Insert Image", command=doNothing)
insertButton.pack(side=LEFT, padx=2, pady=2)

printButton = Button(toolbar, text="Print", command=doNothing)
printButton.pack(side=LEFT, padx=2, pady=2)

toolbar.pack(side=TOP, fill=X)

canvas = Canvas(root, width=200, height=100)
canvas.pack()

blackline = canvas.create_line(0, 0, 200, 50)
circle = canvas.create_oval(20, 20, 60, 60, fill="red")
greenbox = canvas.create_rectangle(80, 80, 100, 100, fill="green")

# Create a Status Bar
status = Label(root, text="Preparing to do nothing", bd=1, relief=SUNKEN, anchor=W)
status.pack(side=BOTTOM, fill=X)

# Runs Window until closed
root.mainloop()