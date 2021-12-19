import sys
import math

input_file = open(sys.argv[1])
lines = input_file.read().splitlines()

def split(sublist): 
    for i in range(len(sublist)): 
        element = sublist[i]
        if type(element) == int and element > 9:
            new_list = [math.floor(element / 2.0), math.ceil(element / 2)]
            sublist[i] = new_list
            return True
        if type(element) == list: 
            if split(element): 
                return True

def explode(sublist, current_level = 1, left_to_add = None, right_to_add = None):

    if left_to_add == None and right_to_add == None:
        # there was no explosion 
        if (current_level > 4) and len(sublist) == 2 and type(sublist[0]) == int and type(sublist[1]) == int: 
            #mi robbantunk
            return True, sublist[0], sublist[1]

        exploded_index = -1
        for i in range(len(sublist)):
            if type(sublist[i]) == list and exploded_index == -1: 
                exploded, la, ra = explode(sublist[i], current_level = current_level+1)
                # közvetlen gyerek robbant vagy annak egy gyereke
                if exploded: 
                    left_to_add = la
                    right_to_add = ra
                    exploded_index = i
                    if left_to_add != None and right_to_add != None: 
                        sublist[i] = 0
                    break 
        
        if exploded_index != -1:
            if right_to_add != None: 
                #gyerek vagy gyerek gyereke robbant / ha utobbi, akkor nem biztos hogy van right to add
                for i in range(exploded_index+1, len(sublist)):
                    # elore kell haladni 
                    if type(sublist[i]) == int: 
                        sublist[i] += right_to_add 
                    else: 
                        e, la, ra = explode(sublist[i], current_level+1, None, right_to_add)
                    #csak akkor futunk ide bele, ha bármi volt tőlünk jobbra 
                    # de ha barmi is volt tolunk jobbra, akkor tuti hogy sikerult hozzá adni a 
                    # right_to_add-et, szóval már nincs rá szükségünk 
                    right_to_add = None
            if left_to_add != None: 
                #gyerek vagy gyerek gyereke robbant / ha utobbi, nem biztos hogy maradt left_to_add
                for i in range(exploded_index - 1, -1, -1):
                    # visszafele kell haladni, hiszen a legbaloldalibb elemhez kell addoljuk
                    if type(sublist[i]) == int: 
                        sublist[i] += left_to_add
                        left_to_add = None
                    else: #this is a list
                        e, la, ra = explode(sublist[i], current_level+1, left_to_add, None)
                    #csak akkor futunk bele ide, ha akarmi is volt balra tőlünk
                    #de akarmi is volt balra, hozzá lehetett adni a left_to_add-ot
                    #szóval arra már nincs szükség
                    left_to_add = None 
            #we have to find the first proper number to the left and to the right

        # akár volt robbanás, akár nem, elvileg ezek értéke a megfelelő kellene itt legyen
        # ezzel elvileg lekezeltuk azt, ha mi magunk robbantunk és azt is, ha a gyerek gyereke
        return exploded_index != -1, left_to_add, right_to_add

    # szülőtől kaptunk egy left to_add-ot és mivel szülőtől kapuk, ezért tuti hogy le kellene tudjuk kezelni
    if left_to_add != None: 
        if type(sublist[-1]) == int: 
                sublist[-1] += left_to_add
        if type(sublist[-1]) == list: 
                e, la, ra = explode(sublist[-1], current_level+1, left_to_add, None)
        left_to_add = None

    # szülőtől kaptunk egy left to_add-ot és mivel szülőtől kapuk, ezért tuti hogy le kellene tudjuk kezelni vagy mi, vagy a gyerekünk
    if right_to_add != None: 
        if type(sublist[0]) == int: 
                sublist[0] += right_to_add
        if type(sublist[0]) == list: 
                e, la, ra = explode(sublist[0], current_level+1, None, right_to_add)
        right_to_add = None
    
    #akármelyik szülőtől is kaptuk, tuti lekezeltük sikeresen, de attól még megőrízzük a robbanás tényét
    return True, None, None

def addlist(first_list, second_list):
    new_list = [first_list, second_list]
    #  print (new_list)
    transformed = True
    while transformed: 
        transformed, la, ra = explode(new_list)
        if not transformed: 
            transformed = split(new_list)
        # if transformed: 
        #     print (new_list)
    return new_list

def magnitude(sublist):
    if type(sublist) == int: 
        return sublist
    else: 
        return 3 * magnitude(sublist[0]) + 2 * magnitude(sublist[1])
        
part1 = False

if part1: 
    result_so_far = eval(lines[0])
    for i in range(1, len(lines)):
        result_so_far = addlist(result_so_far, eval(lines[i]))

    print(f"Magnitued of result is {magnitude(result_so_far)}")
else: 
    max_magnitude = 0
    for i in range(len(lines)): 
        for j in range(len(lines)): 
            if i == j: 
                continue
            res = addlist(eval(lines[i]), eval(lines[j]) )
            mag = magnitude(res)
            if max_magnitude < mag: 
                max_magnitude = mag
    print(f"Maximum magnitude is: {max_magnitude}")