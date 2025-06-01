import sys

def main():

    locks = []
    keys = []

    with open(sys.argv[1]) as f:
        blocks = f.read().split('\n\n')
        for block in blocks:
            lines = block.split('\n')
            heights = [[1 if c == "#" else 0 for c in line] for line in lines]
            sum = [0, 0, 0, 0, 0]
            for i in range(1, len(heights) -1):
                for j in range(5):
                    sum[j] += heights[i][j]

            if lines[0] == "#####":
                locks.append(sum)
            else:
                keys.append(sum)

    counter = 0
    for current_lock in locks:
        for current_key in keys:
            overlap = False
            for i in range(5):
                if current_lock[i] + current_key[i] > 5:
                    overlap = True
                    break
            if not overlap:
                counter += 1

    print(counter)

if __name__ == "__main__":
    main()
