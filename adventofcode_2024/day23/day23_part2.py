import sys

connections = {}

with open(sys.argv[1], 'r') as f:
    index = 0
    for line in f.readlines():
        print(line.strip())
        pc_a, pc_b = line.strip().split("-")

        if pc_a not in connections:
            connections[pc_a] = set()
        if pc_b not in connections:
            connections[pc_b] = set()

        connections[pc_b].add(pc_a)
        connections[pc_a].add(pc_b)
        index += 1

print('-'* 50)
print(len(connections))

largest_group_size = 2
cliques = []

for key, value in connections.items():
    for v in value:
        clique = set()
        clique.add(key)
        clique.add(v)
        if clique not in cliques:
            cliques.append(clique)

print(connections)
print(largest_group_size, len(cliques))


while True:
    new_cliques = []

    for clique in cliques: # process one clique at a time
        # print('-'* 30)
        # print(clique)
        # print(connections.keys())
        # print()
        for key in connections.keys(): # try to add every key to every clique
            connected_to_every = True
            for participant in clique:

                if participant not in connections[key]:
                    connected_to_every = False
                    break
            if connected_to_every:
                new_clique = set(clique)
                new_clique.add(key)
                if (new_clique not in new_cliques) and (len(new_clique) > largest_group_size):
                    new_cliques.append(new_clique)

    for new_clique in new_cliques:
        if len(new_clique) > largest_group_size:
            largest_group_size = len(new_clique)

    print('-'* 50)
    print(new_cliques)
    print(len(new_cliques))
    print(largest_group_size)
    if len(new_cliques) == 0:
        break
    cliques = new_cliques


print(largest_group_size)
names = list(cliques[0])
names.sort()
password = ",".join(names)
print(password)
