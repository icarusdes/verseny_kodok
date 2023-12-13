import sys 
import math

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()

# AAA = (BBB, CCC)


class NodeHistory:
    def __init__(self):
        self.previous_nodes = []
        self.possible_ends = []
    
    def add_previous_node(self, node):
        self.previous_nodes.append(node)

    def add_possible_end(self, node, step):
        if (node, step) not in self.possible_ends:
            self.possible_ends.append((node, step))
    
    def __repr__(self):
        return str(self.possible_ends)

directions = [c for c in lines[0].strip()]
directions_len = len(directions)

labirynth = {}
for line in lines[2:]:
    node = line[0:3]
    left_node = line[7:10]
    right_node = line[12:15]
    labirynth[node] = (left_node, right_node)
    print(node, left_node, right_node)

start_nodes = []
for node in labirynth:
    if node[2] == 'A':
        start_nodes.append(node)

node_history = [NodeHistory() for i in range(len(start_nodes))]

print(start_nodes)

for i in range(100000):
    for j in range(len(start_nodes)):
        node = start_nodes[j]
        left_node = labirynth[node][0]
        right_node = labirynth[node][1]
        if directions[i % directions_len] == 'L':
            start_nodes[j] = left_node
        else:
            start_nodes[j] = right_node
        node_history[j].add_previous_node(start_nodes[j])
        if start_nodes[j][2] == 'Z':
            node_history[j].add_possible_end(start_nodes[j], i+1)

lcm_list = []

for history in node_history:
    print(history)
    lcm_list.append(history.possible_ends[0][1])

print(lcm_list)
print(math.lcm(*lcm_list))
