Android implementation: https://github.com/ashminbhandari/FiveCrowns-Android
Python implemenation: https://github.com/ashminbhandari/Five-Crowns-Python 

Five Crowns Manual

Improvements made:
1. The user with the least points wins the game compared to greater points winning the game.

Bug Report:
1. If the computer wins right off the bat, it doesn’t allow for the human to play it’s turn.
However, this doesn’t happen if the human wins right off the bat, if the human wins right off
the bat, it allows for the computer to have it’s turn before proceeding. This bug will be fixed
in the coming Python project.

Feature Report:
1. Missing features: None
2. Extra features: Allows for two help modes, regular and extended.
3. Player can enter their name so as to personalize the game.

Data structures/classes used:
1. fivecrowns:
This is the driver of the game. It calls upon the singleton instance of the round class and
starts up a round and goes until the round count hits 11. After all rounds are done, it tallies the
scores and prints out the winner.

2. gameRound
This is a singleton class which holds that one instance of round to be operated upon
throughout the game. It resets itself at the end of each round and starts itself up with updated
information.

3. newCardCollection
This is where all the strategizing takes place. The newCardCollection class will hold a
collection as a vector of cards and then operate on it to provide many functionalities such as
checking whether the user can go out or not, how many runs the user has currently, how many
books the user has, how many jokers or wildcards it used and so on. It uses a matrix representation
of the hand to do all this. The newCardCollection has three passes that it can make through the
matrix tackling various cases such as deciding which book or which run to prioritize (if one card
belongs to one or more books or runs) and where to use the jokers or wildcards best.

4. Brain
The brain class makes decisions on behalf of the computer and also helps the user out if
they ask for it. It makes decision with the help of the newCardCollection to choose which card to
pick, which to drop and so on.

5. Card
This is the card class that represents the card through strings. One for suit, one for rank.

6. Deck
This is the deck class that holds the deck as a vector of cards.

7. Player
This class holds all the information and functionalities belonging to a player in the game.
Two classes inherit from it and it also allows for function overriding in child classes.

8. Human
Human inherits from player class. A humans turn is different from a computer so function
overriding aka polymorphism is used here.

9. Computer
Computer inherits from player class. A computer turn is different from a computer so
function overriding aka polymorphism is used here.

10. Serialization
This class helps to serialize the game. Saving and loading is done with the help of this class.

