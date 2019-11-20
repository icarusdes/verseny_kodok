#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

enum DIR {
    DOWN, 
    LEFT, 
    UP, 
    RIGHT
}; 

int main() {
    std::vector<std::string> lines; 
    std::string line; 
    std::fstream input("input2.txt"); 
    std::vector<char> meetChars; 
    uint currentDir = DOWN;
    uint steps = 1; 

    while (std::getline(input, line)) {
        lines.push_back(line); 
        std::cout << line << std::endl; 
    }
    
    uint pos_x = 0; 
    uint pos_y = 0; 
    uint nextpos_x = 0; 
    uint nextpos_y = 0; 

    for (int i = 0; i < line.size(); i++) {
        if (lines[0][i] == '|') {
            pos_x = i; 
            break; 
        }
    }
    std::cout << "Starting positions (x,y) = (" << pos_x << "," << pos_y << ")" << std::endl;
    std::cout << "Max x = " << lines[0].size() << ", max y = " << lines.size() << std::endl;
    while (true) {
        switch (currentDir) {
            case UP: 
                nextpos_x = pos_x; 
                nextpos_y = pos_y - 1; 
                break; 
            case DOWN: 
                nextpos_x = pos_x; 
                nextpos_y = pos_y + 1;             
                break; 
            case LEFT: 
                nextpos_x = pos_x - 1; 
                nextpos_y = pos_y; 
                break; 
            case RIGHT:
                nextpos_x = pos_x + 1; 
                nextpos_y = pos_y; 
                break; 
            default: 
                std::cout << "Error in directions" << std::endl; 
                exit(0); 
        }

        std::cout << "Current X, Y:\t" << pos_x << ", " << pos_y << std::endl;
        std::cout << "Next X, Y:\t" << nextpos_x << ", " << nextpos_y << std::endl;

        char nextChar = lines[nextpos_y][nextpos_x]; 

        if ('+' == nextChar) {
            std::cout << "Found at " << nextpos_x << " " << nextpos_y << std::endl;
            if (currentDir == UP || currentDir == DOWN) {
                int x1 = nextpos_x - 1;  
                int x2 = nextpos_x + 1;
                if (x1 < 0 ) {
                    currentDir = RIGHT;
                } else if (lines[nextpos_y][x1] == '-') {
                    currentDir = LEFT;
                } else {
                    currentDir = RIGHT;
                }
            } else if (currentDir == LEFT || currentDir == RIGHT){
                int y1 = nextpos_y - 1;  
                int y2 = nextpos_y + 1;
                if (y1 < 0 ) {
                    currentDir = DOWN;
                } else if (lines[y1][nextpos_x] != ' ') {
                    currentDir = UP;
                } else {
                    currentDir = DOWN;
                }
            } else {
                std::cout << "Error in directions" << std::endl;
                exit(0); 
            }
        } else if ((nextChar != '-') && (nextChar != '|') && (nextChar != ' ')) {
            meetChars.push_back(nextChar); 
        } else if (nextChar == ' ') {
            std::cout << "It ends here " << std::endl;
            break; 
        }
        pos_x = nextpos_x; 
        pos_y = nextpos_y; 
        steps++; 
    }
    std::cout << "X, Y: " << nextpos_x << ", " << nextpos_y << std::endl;
    for_each(meetChars.begin(), meetChars.end(), [] (char num) { std::cout << num; });
    std::cout << std::endl; 
    std::cout << "Number of steps: " << steps << std::endl; 
}