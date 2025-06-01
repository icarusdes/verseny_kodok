import sys

num_safe_level = 0

def isSafe(numbers):
    isSafe = False
    for i in range(1, len(numbers)):
        if (numbers[i] > numbers[i-1]) and abs(numbers[i] - numbers[i-1]) < 4:
            isSafe = True
        else:
            isSafe = False
            break
    if isSafe:
        return True

    for i in range(1, len(numbers)):
        if (numbers[i] < numbers[i-1]) and abs(numbers[i] - numbers[i-1]) < 4:
            isSafe = True
        else :
            isSafe = False
            break
    return isSafe

with open(sys.argv[1]) as f:
    for line in f:
        
        numbers = line.split()
        numbers = [int(i) for i in numbers]

        if isSafe(numbers):
            print(numbers)
            num_safe_level += 1
            continue

        for i in range(0, len(numbers)):
            safe = isSafe(numbers[0:i] + numbers[i+1:])
            if safe:
                print(numbers)
                num_safe_level += 1
                break
        

print(num_safe_level)
        
