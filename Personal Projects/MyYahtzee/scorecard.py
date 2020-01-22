#!/usr/bin/python3
class Scorecard:
    name = ''
    ones = None
    twos = None
    threes = None
    fours = None
    fives = None
    sixes = None
    three_of_kind = None
    four_of_kind = None
    full_house = None
    sm_straight = None
    lg_straight = None
    yahtzee = None
    bonus = None
    chance = None
    pre_upper_total = None
    upper_bonus = None
    upper_total = None
    lower_total = None
    total = None


    def __init__(self, new_name):
        self.name = new_name

    def display_scorecard(self):
        print('-----------------------------------------')
        print('Name:', self.name)
        print('-----------------------------------------')
        print('Ones:', self.ones)
        print('Twos:', self.twos)
        print('Threes:', self.threes)
        print('Fours:', self.fours)
        print('Fives:', self.fives)
        print('Sixes:', self.sixes)
        print('-----------------------------------------')
        print('Upper Pre-Total:', self.pre_upper_total)
        print('-----------------------------------------')
        print('Bonus for 63 or better:', self.upper_bonus)
        print('-----------------------------------------')
        print('Upper Total:', self.upper_total)
        print('-----------------------------------------')
        print()
        print()
        print('-----------------------------------------')
        print('3 of a Kind:', self.three_of_kind)
        print('4 of a Kind:', self.four_of_kind)
        print('Full House:', self.full_house)
        print('Small Straight:', self.sm_straight)
        print('Large Straight:', self.lg_straight)
        print('Yahtzee:', self.yahtzee)
        print('Bonus:', self.bonus)
        print('Chance:', self.chance)
        print('-----------------------------------------')
        print('Lower Total:', self.lower_total)
        print('Upper Total:', self.upper_total)
        print('-----------------------------------------')
        print('Grand Total:', self.total)
        print('-----------------------------------------')

def main():
    player = ''

    # Ask for Player Name
    player = input('Player Name: ')

    # Create New Player Scorecard
    card = Scorecard(player)

    # Test the Scorecard
    card.display_scorecard()

if __name__ == "__main__":
    main()