import sys

sues = []
if __name__ == "__main__":

    looking_for = {}
    with open("measurements.txt") as f:
        for line in f.readlines():
            what, how_many = line.strip().split(": ", 1)
            looking_for[what] = int(how_many)

    print(looking_for)

    with open(sys.argv[1]) as f:
        for line in f.readlines():
            _, rest = line.strip().split(": ", 1)
            rest = rest.split(", ")
            sue = {}
            for what in rest:
                something, number = what.split(": ")
                sue[something] = int(number)

            sues.append(sue)

    for i, sue in enumerate(sues):
