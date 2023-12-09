import sys

input_file = open(sys.argv[1], 'r')
lines = input_file.read().splitlines()

sum_score = 0

num_cards = {i: 1 for i in range(len(lines))}
current_card = 0

for line in lines:
    winning, ours = line.split(" | ")
    winning_numbers = winning.split()[1:]
    our_numbers = ours.split()
    score = None
    sum_wins = 0
    for i in range(0, len(winning_numbers)):
        if winning_numbers[i] in our_numbers:
            sum_wins += 1
            if score:
                score *= 2
            else:
                score = 1
    if score:
        sum_score += score
        score = None
        for i in range(sum_wins):
            next_card = current_card + i + 1
            if next_card in num_cards:
                num_cards[next_card] += num_cards[current_card]
            else:
                break
        sum_wins = 0
    current_card += 1

print(sum_score)

sum_cards = 0
for k,v in num_cards.items():
    print(k, v)
    sum_cards += v
print(sum_cards)