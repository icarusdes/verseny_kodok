import re 
import sys

leds = [[0 for j in range(1000)] for i in range(1000)]

input_file = open(sys.argv[1], "r")

# turn on 0,0 through 999,999 would turn on (or leave on) every light.
# toggle 0,0 through 999,0 would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
# turn off 499,499 through 500,500 would turn off (or leave off) the middle four lights.

for line in input_file.read().splitlines():
    m = re.match("(turn on|toggle|turn off) (\d+),(\d+) through (\d+),(\d+)", line)
    x1 = int(m.group(2))
    y1 = int(m.group(3))
    x2 = int(m.group(4))
    y2 = int(m.group(5))
    for i in range(x1, x2+1): 
        for j in range(y1, y2+1): 
            if m.group(1) == "turn on": 
                leds[i][j] += 1
            elif m.group(1) == "toggle": 
                leds[i][j] += 2
            elif leds[i][j] > 0: 
                leds[i][j] -= 1


print(sum(sum(leds[i]) for i in range(0, 1000)))

# print(leds)