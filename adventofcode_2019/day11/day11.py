ex = 0
d = 0
base = 0
inp = open('input11.txt').read().split(',')
lst = list(map(int, inp))
[lst.append(0) for rin in range(10000)]

pos = [0,0]
painted = set(())
painter = {}
angle = 0
dx = {0: 0, 90: 1, 180: 0, 270: -1}
dy = {0: 1, 90: 0, 180: -1, 270: 0}

def turn(color, ang):
    global pos,painted,painter,angle,dx,dy
    painted.add((pos[0],pos[1]))
    painter[(pos[0],pos[1])] = color
    if ang == 1:
        angle += 90
        angle = angle % 360
    else:
        angle -= 90
        if angle < 0:
            angle += 360
    print(pos)
    pos[0] += dx[angle]
    pos[1] += dy[angle]
    if (pos[0],pos[1]) not in painter.keys():
        painter[(pos[0],pos[1])] = 0
    return  painter[(pos[0],pos[1])]

def intcode(color):
    global d,base,lst,inp,ex
    out = 0
    save = 0
    def one(second, third, fourth):
        lst[fourth] = lst[second] + lst[third]

    def two(second, third, fourth):
        lst[fourth] = lst[second] * lst[third]

    def three(second, third, fourth):
        lst[second] = int(color)

    def four(second, third, fourth):
        nonlocal out, save,color
        out+=1
        if out == 2:
            color = turn(save,lst[second])
            out = 0
        save = lst[second]

    def five(second, third, fourth):
        global d
        if lst[second] != 0:
            d = lst[third] - 4
        else:
            d -= 1

    def six(second, third, fourth):
        global d
        if lst[second] == 0:
            d = lst[third] - 4
        else:
            d -= 1

    def seven(second, third, fourth):
        if lst[second] < lst[third]:
            lst[fourth] = 1
        else:
            lst[fourth] = 0

    def eight(second, third, fourth):
        if lst[second] == lst[third]:
            lst[fourth] = 1
        else:
            lst[fourth] = 0

    def nine(second, third, fourth):
        global base
        base += lst[second]

    def ninetynine(second, third, fourth):
        global painted,ex
        print(len(painted))
        ex = 1
        return

    command = {1: one, 2: two, 3: three, 4: four, 5: five, 6: six, 7: seven, 8: eight, 9: nine, 99: ninetynine}

    while 1:
        if ex == 1:
            return
        beg = str(lst[d])
        opcode = int(beg[-2:])

        try:
            second = int(beg[-3])
        except:
            second = 0
        try:
            third = int(beg[-4])
        except:
            third = 0
        try:
            fourth = int(beg[-5])
        except:
            fourth = 0

        e = (d+1)
        f = (d+2)
        g = (d+3)
        if second != 1:
            e = lst[e]
            if second == 2:
                e = e+base
        if third !=1:
            f = lst[f]
            if third == 2:
                f = f+base
        if fourth != 1:
            g = lst[g]
            if fourth == 2:
                g = g+base
        command[opcode](e,f,g)
        if opcode == 4 or opcode == 3 or opcode == 9:
            d += 2
        else:
            d += 4

intcode(1)
lst = list(painter.values())
print(lst.count(1))
grid = {}
for j in range(-50,50):
    for i in range(-10,10):
        grid[(j,i)] = 0
for (x,y) in painter.keys():
    try:grid[(x,y)] = painter[(x,y)]
    except:grid[(x,y)] = 0

print(grid)
for i in range(-50,50):
    str = ''
    for j in range(-10,10):
        if grid[(i,j)] == 0:
            str = str + ' '
        else:
            str = str + '#'
    print(str)