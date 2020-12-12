import sys 

input_file = open(sys.argv[1], "r")

dirs = "ENWS"
dir_v = {
    "E": [1,0],
    "N": [0,1], 
    "W": [-1,0],
    "S": [0,-1],
}
heading = 0; 

rotate = [
    [[1, 0], [0, 1]], 
    [[0, 1], [-1, 0]], 
    [[-1, 0], [0, -1]],
    [[0, -1], [1, 0]],
]

pos_x, pos_y = 0,0
part = int(sys.argv[2])

waypont = [10, 1]

def rotate_waypoint(waypont, rotate_num): 
    rot_mat = rotate[rotate_num]
    waypoint_x = rot_mat[0][0] * waypont[0] + rot_mat[0][1] * waypont[1]
    waypoint_y = rot_mat[1][0] * waypont[0] + rot_mat[1][1] * waypont[1]
    return [waypoint_x, waypoint_y]

for line in input_file.read().splitlines(): 
    command = line[0]
    parameter = int(line[1:])

    if part == 1:     
        if command in "ENWS": 
            current_dir = dir_v[command]
            pos_x += current_dir[0] * parameter
            pos_y += current_dir[1] * parameter
        elif command == "R":
            heading = (heading - parameter // 90 ) % 4
        elif command == "L":
            heading = (heading + parameter // 90) % 4
        else: #forward
            current_dir = dir_v[dirs[heading]]
            pos_x += current_dir[0] * parameter
            pos_y += current_dir[1] * parameter    
    else: 
        if command in "ENWS":
            current_dir = dir_v[command]
            waypont[0] += current_dir[0] * parameter
            waypont[1] += current_dir[1] * parameter
        elif command == "R":
            rotate_number =  (parameter // 90 ) % 4
            waypont = rotate_waypoint(waypont, rotate_number)
        elif command == "L":
            rotate_number = ( -1 * (parameter // 90)) % 4    
            waypont = rotate_waypoint(waypont, rotate_number)        
        else: #forward
            current_dir = dir_v[dirs[heading]]
            pos_x += waypont[0] * parameter
            pos_y += waypont[1] * parameter    



print(pos_x, pos_y)
print(abs(pos_x) + abs(pos_y))