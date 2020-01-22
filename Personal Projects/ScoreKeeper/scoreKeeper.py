import sys

player = []


# Set Number of Players
def num_players(p_names):
    global player
    for name in p_names:
        player.append([name, 0])


# Set Score Calculator
def score_calc():
    global player
    game_over = 0
    while game_over < 9:
        for i in player:
            i[1] += int(input(i[0] + " Score:"))
        print(player)
        game_over += 1


# Display Winner
def display_winner():
    global player
    player.sort(key=lambda x: x[1])
    print("\n\nGAME OVER\n\n")
    print("Winner is " + player[0][0])


# Main Function
def main():
    global player
    del sys.argv[0]
    num_players(sys.argv)
    score_calc()
    display_winner()


# Run Main
if __name__ == '__main__':
    main()
