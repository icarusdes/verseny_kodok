#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <boost/algorithm/string.hpp>

// hint: https://www.redblobgames.com/grids/hexagons/

struct cube_coordinates {
    int x = 0;
    int y = 0; 
    int z = 0;

    void goDir(const std::string & dir) {
        if (dir == "n") {
            y += 1; 
            z -= 1; 
        } else if (dir == "nw") {
            x -= 1; 
            y += 1; 
        } else if (dir == "sw") {
            x -= 1; 
            z += 1; 
        } else if (dir == "s") {
            y -= 1; 
            z += 1; 
        } else if (dir == "se") {
            x += 1; 
            y -= 1; 
        } else { // ne
            x += 1;
            z -= 1; 
        }
    }
}; 

// function cube_distance(a, b):
//     return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2

int distance(const cube_coordinates & cc1, const cube_coordinates & cc2) {
    return ((int) (abs(cc1.x - cc2.x) + abs(cc1.y - cc2.y) + abs(cc1.z - cc2.z) )) / 2;
}

// ne,ne,ne is 3 steps away.
// ne,ne,sw,sw is 0 steps away (back where you started).
// ne,ne,s,s is 2 steps away (se,se).
// se,sw,se,sw,sw is 3 steps away (s,s,sw).

int main() {
    uint numberOfSteps = 0;
    uint maxdistance = 0; 
    cube_coordinates cc;
    cube_coordinates origo;
    std::fstream input("input.txt"); 
    std::string dirString; 
    // std::string dirString = "ne,ne,ne";
    // std::string dirString = "ne,ne,sw,sw";
    // std::string dirString = "ne,ne,s,s";
    // std::string dirString = "se,sw,se,sw,sw";
    std::string delimiters(",");
    std::getline(input, dirString); 
    std::vector<std::string> directions; 
    boost::split( directions, dirString, boost::is_any_of(delimiters));

    for (std::string & s : directions) {
        cc.goDir(s);
        uint d = distance(origo, cc);
        if (d > maxdistance)
            maxdistance = d; 
    }
    std::cout << std::endl;
    numberOfSteps = distance(origo, cc);
    std::cout << "Number of steps: " << numberOfSteps << std::endl; 
    std::cout << "Maximal distance: " << maxdistance << std::endl;
    return 0; 
}