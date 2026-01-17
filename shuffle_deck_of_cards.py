from enum import Enum
from attr import dataclass
import random

class Category(Enum):

    SPADE = "SPADE"
    CLUB = "CLUB"
    DIAMOND = "DIAMOND"
    HEART = "HEART"

# @dataclass
class Card:

    def __init__(self, value: str, category: Category):
        self.value = value
        self.category = category

class Deck:

    def __init__(self):
        self.cards = [[Card(value, cat) for value in range(13)] 
                      for cat in [Category.CLUB, Category.DIAMOND, Category.HEART, Category.SPADE]
                      ]
        self.deck = []
        for card in self.cards:
            self.deck.extend(card)
    
    def reset(self):
        self.deck = []
        for card in self.cards:
            self.deck.extend(card)
        
    def shuffle(self):
        for i in range(1, 53):
            numb = random.randint(i, 52)
            self.deck[i-1], self.deck[numb-1] = self.deck[numb-1], self.deck[i-1]


deck = Deck()
# for i in range(52):
#     print(deck.deck[i].value, deck.deck[i].category)

deck.shuffle()
for i in range(52):
    print(deck.deck[i].value, deck.deck[i].category)
