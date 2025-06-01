import sys

numeric_keyboard = ["7", "8", "9", "4", "5", "6", "1", "2", "3", "#", "0", "A"]

def numeric_keyboard_moves(from_button, to_button):
    # 7 8 9
    # 4 5 6
    # 1 2 3
    #   0 A

    current_index = numeric_keyboard.index(from_button)
    desired_index = numeric_keyboard.index(to_button)

    from_row = current_index // 3
    from_col = current_index % 3
    to_row = desired_index // 3
    to_col = desired_index % 3

    direction_accumulator = ""

    if from_row == to_row:
        # same row
        if from_col < to_col:
            # we are moving right
            direction_accumulator += ">" * (to_col - from_col)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "<" * (from_col - to_col)
    elif from_row < to_row:
        # we are mowing always left and right first, than down
        if from_col == to_col:
            # same column
            direction_accumulator += "v" * (to_row - from_row)
        elif from_col < to_col:
            # we are moving right
            direction_accumulator += ">" * (to_col - from_col)
            direction_accumulator += "v" * (to_row - from_row)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "<" * (from_col - to_col)
            direction_accumulator += "v" * (to_row - from_row)
    elif from_row > to_row:
        # we are moving always up first and than left and right
        if from_col == to_col:
            # same column
            direction_accumulator += "^" * (from_row - to_row)
        elif from_col < to_col:
            # we are moving right
            direction_accumulator += "^" * (from_row - to_row)
            direction_accumulator += ">" * (to_col - from_col)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "^" * (from_row - to_row)
            direction_accumulator += "<" * (from_col - to_col)

    return direction_accumulator + "A"

def simulate_moves_numeric(start_button, moves):
    current_index = numeric_keyboard.index(start_button)
    from_row = current_index // 3
    from_col = current_index % 3
    text = ""
    for move in moves:
        if move == "v":
            from_row += 1
        elif move == "^":
            from_row -= 1
        elif move == ">":
            from_col += 1
        elif move == "<":
            from_col -= 1
        elif move == "A":
            text += numeric_keyboard[from_row * 3 + from_col]
        else:
            raise ValueError(f"Invalid move {move}")
    return text


directional_keyboard = ['#', '^', 'A', '<', 'v', '>' ]

def directional_keyboard_moves(from_button, to_button):
    current_index = directional_keyboard.index(from_button)
    desired_index = directional_keyboard.index(to_button)

    from_row = current_index // 3
    from_col = current_index % 3
    to_row = desired_index // 3
    to_col = desired_index % 3

    direction_accumulator = ""
    if from_row == to_row:
        # same row
        if from_col < to_col:
            # we are moving right
            direction_accumulator += ">" * (to_col - from_col)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "<" * (from_col - to_col)
    elif from_row < to_row:
        # we use that the row difference could be at most 1 and we are moving down
        direction_accumulator += "v"
        if from_col < to_col:
            # we are moving right
            direction_accumulator += ">" * (to_col - from_col)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "<" * (from_col - to_col)
    else: # from_row > to_row
        # from_row > to_row
        if from_col < to_col:
            # we are moving right
            direction_accumulator += ">" * (to_col - from_col)
        elif from_col > to_col:
            # we are moving left
            direction_accumulator += "<" * (from_col - to_col)
        direction_accumulator += "^"
    #   ^ A
    # < v >
    return direction_accumulator + "A"

def simulate_moves_directional(start_button, moves):
    current_index = directional_keyboard.index(start_button)
    from_row = current_index // 3
    from_col = current_index % 3
    text = ""
    for move in moves:
        if move == "v":
            from_row += 1
        elif move == "^":
            from_row -= 1
        elif move == ">":
            from_col += 1
        elif move == "<":
            from_col -= 1
        elif move == "A":
            text += directional_keyboard[from_row * 3 + from_col]
        else:
            raise ValueError(f"Invalid move {move}")
    return text

def simulate_moves(start_button, moves):
    current_button = start_button
    directional_moves_layer_2 = ""
    for move in moves:
        print(current_button, move)
        current_button = simulate_moves_directional(current_button, move)
        directional_moves_layer_2 += current_button

    print(directional_moves_layer_2)

    directional_moves_layer_1 = ""
    for move in directional_moves_layer_2:
        current_button = simulate_moves_directional(current_button, move)
        directional_moves_layer_1 += current_button

    print(directional_moves_layer_1)

    numeric_layer = ""
    for move in directional_moves_layer_1:
        current_button = simulate_moves_directional(current_button, move)
        numeric_layer += current_button

    print(numeric_layer)

if __name__ == '__main__':

    codes = []

    if __name__ == "__main__":
        with open(sys.argv[1]) as f:
            for line in f.readlines():
                codes.append(line.strip())

    print (codes)

    complexity_sum = 0

    for code in codes:

        numeric_layer = ""
        numeric_start_button = "A"
        for c in code:
            numeric_layer += numeric_keyboard_moves(numeric_start_button, c)
            numeric_start_button = c


        print(code,)
        print(numeric_layer)

        directional_moves_layer_1 = ""
        directional_start_button = "A"
        for move in numeric_layer:
            directional_moves_layer_1 += directional_keyboard_moves(directional_start_button, move)
            directional_start_button = move
        print(directional_moves_layer_1)

        directional_moves_layer_2 = ""
        directional_start_button = "A"
        for move in directional_moves_layer_1:
            directional_moves_layer_2 += directional_keyboard_moves(directional_start_button, move)
            directional_start_button = move
        print(directional_moves_layer_2)

        sequence_length = len(directional_moves_layer_2)
        numeric_part = int(code[:-1])
        print(sequence_length)
        print(numeric_part)
        complexity = sequence_length * numeric_part
        print(complexity)
        complexity_sum += complexity

        print("-"*80)

    print(complexity_sum)
