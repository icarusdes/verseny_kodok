#include <iostream>
#include <map>
#include <vector>

enum DIRECTION {
    UP, 
    LEFT, 
    DOWN, 
    RIGHT
};

int coord = 0; 
uint circle = 0; 
std::map<std::pair<int, int>, uint> iField; 
std::vector<std::pair<int, int> > nextCorners; 
std::pair<int, int> currentCoords;
int direction = UP; 


void generateNewCorners() {
    circle++; 
    nextCorners.clear(); 
    nextCorners.push_back(std::pair<int, int>(circle, circle));
    nextCorners.push_back(std::pair<int, int>(-circle, circle));
    nextCorners.push_back(std::pair<int, int>(-circle, -circle));
    nextCorners.push_back(std::pair<int, int>(circle + 1, -circle));
}

void getNextCoord() {
    std::pair<int, int> temp = currentCoords; 
    switch(direction) {
        case UP: 
            temp.second += 1; 
            if (temp == nextCorners[0]) 
                direction = LEFT;
            break; 
        case LEFT: 
            temp.first -= 1; 
            if (temp == nextCorners[1])
                direction = DOWN; 
            break; 
        case DOWN: 
            temp.second -= 1; 
            if (temp == nextCorners[2])
                direction = RIGHT; 
            break;
        case RIGHT: 
            temp.first += 1; 
            if (temp == nextCorners[3]) {
                direction = UP; 
                generateNewCorners();
            }
            break; 
    }
    currentCoords = temp; 
}

std::vector<std::pair<int, int> > getNeighboors(const std::pair<int, int> & center ) {
    std::vector<std::pair<int, int> > temp(8);
    temp[0] = center; temp[0].first += 1; 
    temp[1] = center; temp[1].first += 1; temp[1].second += 1; 
    temp[2] = center; temp[2].second += 1; 
    temp[3] = center; temp[3].first -= 1; temp[3].second += 1; 
    temp[4] = center; temp[4].first -= 1;
    temp[5] = center; temp[5].first -= 1; temp[5].second -= 1; 
    temp[6] = center; temp[6].second -= 1; 
    temp[7] = center; temp[7].first += 1; temp[7].second -= 1; 
    return temp; 
}

int main() {
    iField[std::pair<int, int>(0, 0)] = 1;
    iField[std::pair<int, int>(1, 0)] = 1;  

    currentCoords = std::pair<int, int>(1, 0); 
    generateNewCorners(); 

    uint input = 312051; 
    uint lastnum = 1; 
    while (lastnum < input) {
        auto neighboors = getNeighboors(currentCoords); 
        uint sum = 0; 
        for (const auto & coord : neighboors) {
            sum += iField[coord]; 
        }
        iField[currentCoords] = sum; 
        lastnum = sum; 
        std::cout << "Current sum is " << sum << std::endl; 
        getNextCoord(); 
    }
    /* while( true ) {
        circle++; 
        line_lenght = circle * 2 - 1 ; 
        if (input < line_lenght * 4 + 4)
            break; 
        input -= line_lenght * 4 + 4; 
        std::cout << "Circlenumber: " << circle << "\t" << line_lenght *  4 + 4 << "\t remaning " << input << std::endl; 
    } */ 

    return 0; 
}