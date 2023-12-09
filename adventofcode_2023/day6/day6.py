test_race = {7: 9, 15: 40, 30: 200}
real_input = {46: 347, 82:1522, 84:1406, 79:1471}
test_race = {71530: 940200}
real_input = {46828479: 347152214061471}
win_product = 1

for time, distance in real_input.items():
    wins = 0
    for i in range(time):
        speed = i
        achieved_distance = (time - i) * speed
        if achieved_distance > distance:
            wins += 1
    win_product *= wins

print(f"Number of wins: {win_product}")