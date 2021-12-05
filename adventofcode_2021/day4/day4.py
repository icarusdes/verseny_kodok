import sys 

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines() 

drawn_numbers = list(map(int, lines[0].split(",")))
del lines[0:2]

bingo_boards = []
was_there_a_zero = []
current_board = []

for line in lines: 
    if line == '': 
        bingo_boards.append(current_board)
        current_board = []
        continue
    current_board += list(map(int, line.split()))
bingo_boards.append(current_board)

print(bingo_boards)
for board in bingo_boards: 
    print(board)

for board in bingo_boards: 
    try: 
        board.index(0)
        was_there_a_zero.append(1)
    except ValueError: 
        was_there_a_zero.append(0)

def is_there_a_bingo(table): 
    for i in range(5): 
        if table[i*5:(i+1)*5 ] == [-1, -1, -1, -1, -1]: 
            return True
        if table[i::5] == [-1, -1, -1, -1, -1]: 
            return True
    return False

def print_board(current_board): 
    for i in range(5):
        print(current_board[i*5:(i+1)*5 ])

for n in drawn_numbers: 
    boards_to_win = []
    print (f"Current drawn number:{n}")
    i = 0
    for board in bingo_boards: 
        try: 
            index = board.index(n)
            board[index] = -1
            if is_there_a_bingo(board):
                boards_to_win.append(i)
                if len(bingo_boards) == 1: 
                    print_board(board)
                    print(sum(board) + board.count(-1))
                    print((sum(board) + board.count(-1)) * n)
                    exit(0)
        except ValueError: 
            pass
        i+=1
    
    boards_to_win.reverse()
    if len(boards_to_win) > 0:
        print (boards_to_win) 
        for i in boards_to_win: 
            del bingo_boards[i]

print(bingo_boards)

