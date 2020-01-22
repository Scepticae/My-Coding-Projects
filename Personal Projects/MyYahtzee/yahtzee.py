import diceroller
import scorecard
import os

def dice_to_keep(numbers):
    check = True

    # Pick Dice until No Errors Exist
    while check == True:
        # Ask for Dice to Keep
        print('Select Dice to Keep:')
        selected_string = input()

        # Place Selected Dice in an Array
        selected = selected_string.split()

        # Check that the Die Chosen were Members of Rolled Dice
        for die in selected:
            if int(die) not in numbers:
                check = True
                break
            else:
                check = False

        if check == True:
            print('One or more dice incorrectly chosen.')

    # Return the Kept Dice
    return selected

def main():
    num_players = 0
    players = []
    turns = 0
    NUM_TURNS = 13
    NUM_DICE = 5

    # Welcome Message
    print('Welcome to Yahtzee.')

    # Determine Number of Players
    num_players = int(input('Enter Number of Players: '))
    os.system("cls")

    # Get Dice
    dice = diceroller.Dice(NUM_DICE)

    # Setup Player Scorecards
    for i in range(num_players):
        player_name = input('Enter Player Name: ')
        temp = scorecard.Scorecard(player_name)
        players.append(temp)
        os.system("cls")

    # Create Game Loop
    while turns < NUM_TURNS:
        for i in range(num_players):
            num_rolls = 0
            print(players[i].name, 'enter 1 to roll the dice or 0 to stop.')
            choice = int(input('Roll or Stop: '))
            while choice == 1 and num_rolls < 3:
                dice.roll_dice()
                chosen = dice_to_keep(dice.die)
                print(chosen)
                choice = int(input('Roll or Stop: '))
                os.system("cls")

if __name__ == "__main__":
    main()