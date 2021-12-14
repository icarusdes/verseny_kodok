import sys

input_file = open(sys.argv[1], "r")
lines = input_file.read().splitlines()

cavemap = {}

for line in lines:
    _to, _from = line.split("-")
    if _to in cavemap:
        cavemap[_to].append(_from)
    else:
        cavemap[_to] = [_from]

    if _from in cavemap:
        cavemap[_from].append(_to)
    else:
        cavemap[_from] = [_to]

print(cavemap)

def find_recoursive_route(where_from, route_until_now):
    new_routes = []
    for next_node in cavemap[where_from]:
        if next_node.islower() and next_node in route_until_now:
            continue
            #this should be not visited twice
        elif next_node == "end":
            new_routes.append(route_until_now + [next_node])
        else:
            new_route = find_recoursive_route(next_node, route_until_now + [next_node])
            if new_route != []:
                #there was a route that way
                if len(new_route) == 1:
                    new_routes.extend(new_route)
                else:
                    new_routes.extend(new_route)
    return new_routes

def find_recoursive_route2(where_from, route_until_now, were_twice):
    new_routes = []
    for next_node in cavemap[where_from]:
        if next_node.islower() and route_until_now.count(next_node) == 2:
            continue #this should be not visited more than tree times
        elif next_node.islower() and were_twice and next_node in route_until_now:
            continue #there were already something twice
        elif next_node == "end":
            new_routes.append(route_until_now + [next_node])
            # we end here and don't follow the recursion
        elif next_node == "start":
            continue
            # we don't visit this twice
        else:
            if next_node.islower() and next_node in route_until_now:
                new_were_twice = True
            else:
                new_were_twice = were_twice
            new_route = find_recoursive_route2(next_node, route_until_now + [next_node], new_were_twice)
            if new_route != []:
                #there was a route that way
                if len(new_route) == 1:
                    new_routes.extend(new_route)
                else:
                    new_routes.extend(new_route)
    return new_routes


routes = find_recoursive_route("start", ["start"])
routes2 = find_recoursive_route2("start", ["start"], False)

#print (routes)
print (len(routes))

#print (routes2)
print (len(routes2))
routes2.sort()

# for r in routes2:
#     print(r)