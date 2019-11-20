#include <iostream>
#include <fstream>
#include <string>
#include <map>

enum direction {
    UP, 
    RIGHT, 
    DOWN, 
    LEFT
}; 

void turn_left(int & dir) { 
    if (dir == 0) {
        dir = 3; 
        return; 
    }
    dir--; 
}

void turn_right(int & dir) { 
    dir = (dir + 1) % 4; 
}

void step(int dir, int & x, int & y) {
    switch (dir) {
        case UP: 
            y -= 1;
            break;
        case RIGHT:
            x += 1;
            break;  
        case DOWN:
            y += 1;
            break;  
        case LEFT: 
            x -= 1;
            break; 
        default: 
            std::cout << "Undefined dir " << dir  << std::endl; 
    }
}

using field = std::map<std::pair<int, int>, char>;
field ifield;

void drawField(field & ifield, int x, int y) {  
    for (int i=-5; i < 7; i++) {
        for (int j = -5; j < 7; j++) {
            char c = ifield[std::pair<int, int>(j, i)]; 
            if (c != '#')
                c = '.'; 
            if (x == j && y == i) 
                std::cout << "["; 
            else 
                std::cout << " "; 
            std::cout << c; 
            if (x == j && y == i) 
                std::cout << "]"; 
            else 
                std::cout << " ";
            std::cout << " "; 
        }
        std::cout << std::endl; 
    }

}

int main() {
    std::fstream input("input2.txt"); 
    std::string line; 
    uint line_x = 0; 
    uint line_y = 0; 
    uint burst_num = 10000; 

    while (std::getline(input, line)) {
        line_x = 0; 
        for (char & c : line) {
            if (c == '.' || c == '#') {
                ifield[std::make_pair<int, int>(line_x, line_y)] = c;
                std::cout << "Adding " << c << " to " << line_x << ", " << line_y << std::endl;
                line_x++; 
            }
        }
        line_y++; 
    }

    int dir = UP; 

    int start_y = line_y / 2; 
    int start_x = line_x / 2; 
    int infected = 0; 

    while(burst_num--) {
        // std::cout << "-------------------------------------------------------" << std::endl;
        // drawField(ifield, start_x, start_y); 
        char ref = ifield[std::pair<int, int>(start_x, start_y)]; 
        // std::cout << "Current x, y: " << start_x << ", " << start_y << " " << (int) ref << " " << ref << std::endl;

        if ('.' == ref || 0 == ref) {
            std::cout << "Current x, y: " << start_x << ", " << start_y << " " << (int) ref << " " << ref << std::endl;
            ifield[std::pair<int, int>(start_x, start_y)] = '#'; 
            turn_left(dir); 
            infected++;
        } else if ('#' == ref) {
            ifield[std::pair<int, int>(start_x, start_y)] = '.'; 
            turn_right(dir); 
        } else {
            std::cout << "Start x, start y " << start_x << ", " << start_y << std::endl;
            std::cout << (int) ref << std::endl;
            std::cout << "Itt baj van" << std::endl; 
            exit(0); 
        }
        step(dir, start_x, start_y); 
    }
    std::cout << "Number of infected nodes " << infected << std::endl; 

}