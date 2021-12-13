import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()
folds = []
sheet = {}

for i in range(len(lines)): 
    if lines[i] == "": 
        folds = lines[i+1:]
        break
    x, y = lines[i].split(",")
    sheet[(int(x), int(y))] = 1

def draw_sheet(): 
    min_x = min([c[0] for c in list(sheet.keys())])
    max_x = max([c[0] for c in list(sheet.keys())])
    min_y = min([c[1] for c in list(sheet.keys())])
    max_y = max([c[1] for c in list(sheet.keys())])

    for y in range(min_y, max_y+1): 
        for x in range(min_x, max_x + 1): 
            if (x, y) in sheet: 
                print("#", end = "")
            else:
                print(".", end = "")
        print()

draw_sheet()

for fold in folds: 
    instruction, amount = fold.split("=")
    amount = int(amount)
    if instruction[-1] == "x": 
        print("folding horizontaly")
        for key in list(sheet.keys()):
            if (key[0] == amount):
                del sheet[key]
            elif (key[0] > amount):
                del sheet[key]
                sheet[( 2 * amount - key[0], key[1])] = 1
            else:
                pass 
                #nothing to do
    else: 
        for key in list(sheet.keys()):
            if (key[1] == amount):
                del sheet[key]
            elif (key[1] > amount):
                del sheet[key]
                sheet[(key[0],  2 * amount - key[1])] = 1
            else:
                pass 
                #nothing to do
        print("folding verticaly")

draw_sheet()

print(len(sheet))
