import sys

def input_to_list(line: str) -> list:
    harddrive = []
    id = 0
    x = 0
    for c in line:
        number = int(c)
        if x % 2 == 0:
            harddrive.extend([id for _ in range(number)])
        else:
            if number == 0:
                pass
            else:
                harddrive.extend(['.' for _ in range(number)])
            id += 1
        x += 1

    print("Max id is", id)
    return harddrive

def deflate(harddrive: list) -> list:
    first_x = harddrive.index('.')
    last_x = len(harddrive) - 1
    while harddrive[last_x] == '.':
        last_x -= 1
    while first_x != last_x and first_x < last_x:
        harddrive[first_x], harddrive[last_x] = harddrive[last_x], harddrive[first_x]
        first_x += 1
        last_x -= 1
        while harddrive[first_x] != '.' and first_x < last_x and first_x < len(harddrive):
            first_x += 1
        while harddrive[last_x] == '.' and first_x < last_x and last_x > 0:
            last_x -= 1
    return harddrive

def deflate3(harddrive: list) -> list:
    files = []
    empty_spaces = []

    prev_start = 0
    prev_id = 0
    for i in range(len(harddrive)):
        current_id = harddrive[i]
        if current_id == prev_id:
            # we are happy
            pass
        else:
            if prev_id == '.':
                empty_spaces.append((prev_start, i - prev_start))
            else:
                files.append((prev_start, i - prev_start, prev_id))
            prev_start = i
            prev_id = current_id
    if prev_id == '.':
        empty_spaces.append((prev_start, i - prev_start + 1))
    else:
        files.append((prev_start, i - prev_start + 1, prev_id))
    print(files)
    print(empty_spaces)

    for i in range(len(files), 0, -1):
        # we start from the end
        file = files[i-1]
        for j in range(len(empty_spaces)):
            # we start from the first empty space
            empty_space = empty_spaces[j]
            
            # if the empty space is to the right of the file
            if empty_space[0] >= file[0]:
                break
            # if the empty space is big enough
            if empty_space[1] >= file[1]:
                # if the empty space is exactly the same size as the file
                if empty_space[1] == file[1]:
                    empty_spaces.pop(j)
                # if the empty space is bigger than the file
                else:
                    empty_spaces[j] = (empty_space[0] + file[1], empty_space[1] - file[1])
                
                old_start = file[0]
                files[i-1] = (empty_space[0], file[1], file[2])
                break
            else: 
                # nothing to do, the next iteration can continue
                pass

                # # update the empty spaces list with files old position
                # found_index = None
                # for k in range(len(empty_spaces)):
                #     if empty_spaces[k][0] + empty_spaces[k][1] == old_start:
                #         found_index = k
                #         break
                # if found_index is not None:
                #     empty_spaces[found_index] = (empty_spaces[found_index][0], empty_spaces[found_index][1] + file[1])
                # else:
                #     empty_spaces.append((file[0], file[1]))
    print(files)
    print(empty_spaces)

    sum = 0
    for files in files:
        for i in range(files[0], files[0] + files[1]):
            sum += i * files[2]
    print(sum)

def deflate2(harddrive: list) -> list:
    processed = set()
    last_x = len(harddrive) - 1
    while harddrive[last_x] == '.':
        last_x -= 1

    while last_x >= 0:

        # determine the length of the continuous segment of not '.'
        # starting from the end which what we havent processed yet
        length = 0
        id = harddrive[last_x]
        while harddrive[last_x] == id:
            length += 1
            last_x -= 1

        # find first continuous segment of '.' which is at least as long as the
        # segment of not '.'

        first_x = 0
        while first_x < len(harddrive) and first_x < last_x and (id not in processed):
            len_empty = 0
            while harddrive[first_x] != '.':
                first_x += 1
            beginning = first_x
            while first_x < len(harddrive) and harddrive[first_x] == '.':
                len_empty += 1
                first_x += 1
            if len_empty >= length:
                if length > 1:
                    harddrive[beginning: beginning+length] = harddrive[last_x+1:length+last_x+1]
                    harddrive[last_x + 1:last_x + 1 + length] = ['.' for _ in range(length)]
                else:
                    harddrive[beginning] = harddrive[last_x+1]
                    harddrive[last_x+1] = '.'
                break
            else:
                continue 
        processed.add(id)

        while harddrive[last_x] == '.':
            last_x -= 1

def checksum(harddrive: list) -> int:
    sum = 0
    x = 0
    for c in harddrive:
        if c != '.':
            sum += x*c
        x += 1
    return sum

harddrive = []
with open(sys.argv[1]) as f:
    line = f.readline().strip()
    harddrive = input_to_list(line)
    print(''.join([str(i) for i in harddrive]))
    copyd_data = harddrive[:] 
    deflate(harddrive)    
    deflate3(copyd_data)
    # print(''.join([str(i) for i in harddrive]))
    # print(''.join([str(i) for i in copyd_data]))
    print(checksum(harddrive))
    # print(checksum(copyd_data))