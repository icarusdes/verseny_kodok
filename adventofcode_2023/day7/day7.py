import sys
import functools
from enum import Enum

with open(sys.argv[1], "r") as input_file:
    lines = input_file.read().splitlines()


# A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. The relative strength of each card 
# follows this order, where A is the highest and 2 is the lowest.
value_order = ["J", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]


def compare_cards(card1, card2):
    return value_order.index(card2) - value_order.index(card1)

class types(Enum):
    FIVE_OF_A_KIND = 1
    FOUR_OF_A_KIND = 2
    FULL_HOUSE = 3
    THREE_OF_A_KIND = 4
    TWO_PAIRS = 5
    ONE_PAIR = 6
    HIGH_CARD = 7

class Hand():
    def __init__(self, line):
        cards, bid = line.split(" ")
        
        self.cards = [c for c in cards]
        
        self.bid = int(bid)

        # determine type
        self.type = types.HIGH_CARD

        temp_save = self.cards.copy()
        # to make sure jokers count to the highest card, we sort the cards
        temp_save.sort(key=functools.cmp_to_key(compare_cards))
        joker_count = temp_save.count("J")
        for i in range(0, joker_count):
            temp_save.remove("J")
        while temp_save:
            first = temp_save.pop(0)
            if temp_save.count(first) == 4:
                # nothing two do, we have a five of a kind, no remaining cards
                self.type = types.FIVE_OF_A_KIND
                break
            if temp_save.count(first) == 3:
                # we have one reaming card which can be nothing
                self.type = types.FOUR_OF_A_KIND
                break
            if temp_save.count(first) == 2:
                # we have two cards left, which can be pair or not pair
                if self.type == types.ONE_PAIR:
                    self.type = types.FULL_HOUSE
                    # we already processed those so we know we can end now 
                    break                 
                self.type = types.THREE_OF_A_KIND
                temp_save.remove(first)
                temp_save.remove(first)
                continue
            if temp_save.count(first) == 1:
                if self.type == types.THREE_OF_A_KIND:
                    self.type = types.FULL_HOUSE
                    # we already processed those so we know we can end now 
                    break
                if self.type == types.ONE_PAIR:
                    self.type = types.TWO_PAIRS
                    # we already processed those so we know we can end now 
                    break
                self.type = types.ONE_PAIR
                temp_save.remove(first)
                continue
            if temp_save.count(first) == 0:
                # we had exactly one card of this type
                continue
        if joker_count == 1:
            if self.type == types.FOUR_OF_A_KIND:
                self.type = types.FIVE_OF_A_KIND
            if self.type == types.THREE_OF_A_KIND:
                self.type = types.FOUR_OF_A_KIND
            if self.type == types.ONE_PAIR:
                self.type = types.THREE_OF_A_KIND
            if self.type == types.TWO_PAIRS:
                self.type = types.FULL_HOUSE
            if self.type == types.HIGH_CARD:
                self.type = types.ONE_PAIR
        if joker_count == 2:
            if self.type == types.THREE_OF_A_KIND:
                self.type = types.FIVE_OF_A_KIND
            if self.type == types.ONE_PAIR:
                self.type = types.FOUR_OF_A_KIND
            if self.type == types.HIGH_CARD:
                self.type = types.THREE_OF_A_KIND
        if joker_count == 3:
            if self.type == types.ONE_PAIR:
                self.type = types.FIVE_OF_A_KIND
            if self.type == types.HIGH_CARD:
                self.type = types.FOUR_OF_A_KIND
        if joker_count == 4:
            self.type = types.FIVE_OF_A_KIND
        if joker_count == 5:
            self.type = types.FIVE_OF_A_KIND

    def __str__(self):
        return str(self.cards) + " " + str(self.bid) + " " + str(self.type)
    
def compare_hands(hand1, hand2):
    if hand1.type.value != hand2.type.value:
        return hand1.type.value - hand2.type.value
    
    for i in range(0, len(hand1.cards)):
        if compare_cards(hand1.cards[i], hand2.cards[i]) != 0:
            return compare_cards(hand1.cards[i], hand2.cards[i])
hands = []
for line in lines:
    hand = Hand(line)
    hands.append(hand)
    print(hand)

new_hands = sorted(hands, key=functools.cmp_to_key(compare_hands), reverse=True)

print("-------------------")
for hand in new_hands:
    print(hand)

i = 1
sum_bids = 0
for hand in new_hands:
    sum_bids += hand.bid * i 
    i += 1

print(sum_bids)