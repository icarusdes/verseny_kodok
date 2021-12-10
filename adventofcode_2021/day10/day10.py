import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

starter = ["(", "[", "{" ,"<"]
pairs = {
    "(" : ")",
    "[" : "]", 
    "<" : ">", 
    "{" : "}", 
    # ")" : "(", 
    # "]" : "[", 
    # ">" : "<", 
    # "}" : "{"
}

points = {
    None : 0, 
    ")"  : 3, 
    "]"  : 57, 
    "}"  : 1197, 
    ">"  : 25137,
    "("  : 1,
    "["  : 2, 
    "{"  : 3, 
    "<"  : 4,
}

def process_line(line): 
    stack = []
    for char in line: 
        if char in starter: 
            stack.append(char)
        else:
            if len(stack) == 0 or pairs[stack[-1]] != char: 
                return False, True, char
                # this is a corrupted line
            else: 
                stack.pop()
    if len(stack) != 0: 
        return False, False, stack
        # this is an incomplete line
    return True, None, None, 
            
corrupted_chars = []
second_part_scores = []

for line in lines: 
    isValid, isCorrupted, data = process_line(line)
    
    if not isValid: 
        if isCorrupted: 
            corrupted_chars.append(data)
        else: 
            #not corrupted, so just incomplete
            score = 0
            data = list(data)
            data.reverse()
            for c in data: 
                score = score * 5 + points[c]
            second_part_scores.append(score)
    else: 
        #valid lines
        pass 


fisrt_part_score = sum( [points[c] for c in corrupted_chars])
second_part_scores.sort()

print(f"Part one score is {fisrt_part_score}.")
print(f"Part second score is {second_part_scores[len(second_part_scores)  // 2]}.")