import sys
 
input_file = open(sys.argv[1], 'r') 

groups = []
current_group = []
num_persons_in_a_group = 0

# i don't like it :/ 
for line in input_file.read().splitlines(): 
    if len(line) != 0: 
        num_persons_in_a_group += 1
        for c in line: 
            current_group.append(str(c))
    else: 
        groups.append((num_persons_in_a_group, current_group))
        current_group = []
        num_persons_in_a_group = 0
groups.append((num_persons_in_a_group, current_group))

groups_sorted_and_unique = [list(set(group[1])) for group in groups]
sum_answers = sum(len(group) for group in groups_sorted_and_unique)

def count_all_yes(group): 
    num_count = group[0] -1
    answers = group[1]
    answers.sort() 
    return sum([ answers[i] == answers[i+num_count] for i in range(len(answers) - num_count)])
    

# sum_everyone_answered_yes = sum(sum((group[1].count(chr(c)) == group[0]) for c in range(ord('a'), ord('z')+1)) for group in groups)
sum_everyone_answered_yes = sum(count_all_yes(group) for group in groups)

print("The sum of yes answers are: {}".format(sum_answers))
print("The sum of everyone answered yes are: {}".format(sum_everyone_answered_yes))
