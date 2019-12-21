#include <iostream>
#include <ostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

bool gVerbose = false;

struct vector {
    int x; 
    int y;
    bool isMultiple( const vector & otherVec) {
        if (x == 0 && otherVec.x != 0) 
            return false;
        if (x != 0 && otherVec.x == 0)
            return false;        
        if (y == 0 && otherVec.y != 0)
            return false;
        if (y != 0 && otherVec.y == 0)
            return false;
        // nyilvánvalóan nem lehez azonos az irányuk de cserébe a nullával osztás miatt sem kell aggódni
        if (x == 0 && otherVec.x == 0)
            return (y * otherVec.y) > 0; 
        if (y == 0 && otherVec.y == 0)
            return (x * otherVec.x) > 0; 
        // ezek azok, ahol nyilvánvalóan azonos az irányuk 
        float x_mult = float{x} / otherVec.x; 
        float y_mult = float{y} / otherVec.y; 
        return x_mult == y_mult && x_mult >= 0 && y_mult >= 0; 
    }

    friend std::ostream& operator<<(std::ostream& os, const vector& dt);
};

std::ostream& operator<<(std::ostream& os, const vector& v)
{
    os << "{" << v.x << ',' << v.y << '}';
    return os;
}

struct asteroid {
    int x       = 0; 
    int y       = 0; 
    int seable  = 0; 
    vector directionVector ( const asteroid & otherAsteroid) {
        vector dVector; 
        dVector.x = otherAsteroid.x - x; 
        dVector.y = otherAsteroid.y - y; 

        return dVector; 
    }
    
    friend std::ostream& operator<<(std::ostream& os, const asteroid& dt);
};

std::ostream& operator<<(std::ostream& os, const asteroid& a)
{
    os << "{ x:" << a.x << ", y: " << a.y << ", detectable: " << a.seable << "}";
    return os;
}

int main(int argc, char ** argv) {    

    // UNIT test for vectors 

    vector v1 {1, 1};
    vector v2 {2, 2};
    vector v3 {1, 0}; 
    vector v4 {-1, 0}; 
    vector v5 {2, 0}; 
    vector v6 {2, 1}; 
    vector v7 {4, 2}; 
    vector v8 {-2, -2}; 
    vector v9 {-4, -4}; 

    std::cout << v1 << " " << v2 << " " << v1.isMultiple(v2) << std::endl; 
    std::cout << v2 << " " << v3 << " " << v2.isMultiple(v3) << std::endl;
    std::cout << v3 << " " << v4 << " " << v3.isMultiple(v4) << std::endl;
    std::cout << v3 << " " << v5 << " " << v3.isMultiple(v5) << std::endl;
    std::cout << v6 << " " << v7 << " " << v6.isMultiple(v7) << std::endl;
    std::cout << v8 << " " << v9 << " " << v8.isMultiple(v9) << std::endl;
    std::cout << v1 << " " << v9 << " " << v1.isMultiple(v9) << std::endl;

    std::cout << "-------------------------------------------------------" << std::endl;
    // 


    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
    if (argc == 3) 
        gVerbose = true; 

    std::vector<std::string> map; 
    std::vector<asteroid> asteroids; 

    for( std::string line; getline( input_file, line );) {
        map.push_back(line); 
    }
    if (gVerbose) 
        std::cout << "Dimensions: " << map.size() << "x" << map[0].size() << std::endl; 
    if (gVerbose) 
        std::cout << "-------------------------------------------------------" << std::endl;

    for (int i = 0; i < map.size(); i++) {
        if (gVerbose) 
            std::cout << map[i] << std::endl; 
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i].c_str()[j] == '#') 
                asteroids.push_back({j, i, 0});
        }
    }
    
    if (gVerbose) 
        std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "Number of asteroids: " << asteroids.size() << std::endl; 
    std::cout << "-------------------------------------------------------" << std::endl;

    for (int i = 0; i < asteroids.size(); i++) {
        bool trace = false; 
        // if asteroids[i].x == 
        std::vector<vector> directionVectors; 
        for (int j = 0; j < asteroids.size(); j++) {
            if (i == j) 
                continue; 
            bool isMultiple = false; 
            vector directionVector = asteroids[i].directionVector(asteroids[j]); 
            for (const auto & v : directionVectors) {
                if (directionVector.isMultiple(v)) {
                    isMultiple = true; 
                    break; 
                }
            }
            if (!isMultiple)
                directionVectors.push_back(directionVector); 
        }
        asteroids[i].seable = directionVectors.size();
        if (gVerbose) 
            std::cout << asteroids[i] << std::endl; 
    }

    int max_seable = -1;
    int asteroid_index = -1; 

    for (int i = 0; i < asteroids.size(); i++) {
        if (asteroids[i].seable > max_seable) {
            max_seable = asteroids[i].seable;
            asteroid_index = i; 
        }
    }   

    std::cout << asteroid_index << std::endl; 

    if (asteroid_index != -1) {
        auto & ba = asteroids[asteroid_index];
        std::cout << ba << std::endl; 
    } 

    return 0; 
}