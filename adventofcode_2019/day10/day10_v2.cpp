#include <iostream>
#include <ostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <climits>

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>

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

    // a függőlegeshez képest
    float angle() const {
        float res = atan2 (x , y) * 180 / M_PI;
        return (res <= 0) ? res + 360.0 : res ;
            
    }

    friend std::ostream& operator<<(std::ostream& os, const vector& dt);

    bool operator<(const vector & v) {
        return angle() > v.angle(); 
    }
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

    float distance( const asteroid & otherAsteroid) { 
        return sqrt(pow(x - otherAsteroid.x, 2) + pow(y - otherAsteroid.y, 2)); 
    }
    
    friend std::ostream& operator<<(std::ostream& os, const asteroid& dt);
};

std::ostream& operator<<(std::ostream& os, const asteroid& a)
{
    os << "{ x:" << a.x << ", y: " << a.y << ", detectable: " << a.seable << "}";
    return os;
}

int main(int argc, char ** argv) {    

    bool unit_test = true; 
    if (unit_test) {
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
        vector v10 {4, -4}; 
        vector v11 {0, -4}; 
        vector v12 {0, 4}; 
        vector v13 {-4, 4}; 


        std::cout << v1 << " " << v2 << " " << v1.isMultiple(v2) << std::endl; 
        std::cout << v2 << " " << v3 << " " << v2.isMultiple(v3) << std::endl;
        std::cout << v3 << " " << v4 << " " << v3.isMultiple(v4) << std::endl;
        std::cout << v3 << " " << v5 << " " << v3.isMultiple(v5) << std::endl;
        std::cout << v6 << " " << v7 << " " << v6.isMultiple(v7) << std::endl;
        std::cout << v8 << " " << v9 << " " << v8.isMultiple(v9) << std::endl;
        std::cout << v1 << " " << v9 << " " << v1.isMultiple(v9) << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;


        std::cout << std::fixed << std::setprecision(5) << v3 << " \t" << v3.angle() << std::endl;
        std::cout << v1 << "\t" << v1.angle() << std::endl;
        std::cout << v2 << "\t" << v2.angle() << std::endl;
        std::cout << v4 << "\t" << v4.angle() << std::endl;
        std::cout << v10 << "\t" << v10.angle() << std::endl;
        std::cout << v11 << "\t" << v11.angle() << std::endl;
        std::cout << v12 << "\t" << v12.angle() << std::endl;
        std::cout << v9 << "\t" << v9.angle() << std::endl;
        std::cout << v13 << "\t" << v13.angle() << std::endl;
        std::cout << v6 << "\t" << v6.angle() << std::endl;

        std::cout << "-------------------------------------------------------" << std::endl;
    }
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
    if (gVerbose) 
        std::cout << "-------------------------------------------------------" << std::endl;

    int max_seable = -1;
    int asteroid_index = -1; 

    for (int i = 0; i < asteroids.size(); i++) {
        if (asteroids[i].seable > max_seable) {
            max_seable = asteroids[i].seable;
            asteroid_index = i; 
        }
    }   

    asteroid best_asteroid = asteroids[asteroid_index];
    asteroids.erase(asteroids.begin() + asteroid_index); 

    std::cout << "The best asteroid for radar is: " << best_asteroid << std::endl; 
    std::cout << "Let the destruction begin" << std::endl;
    
    std::vector<vector> directionVectors; 
    for (int j = 0; j < asteroids.size(); j++) {
        bool isMultiple = false; 
        vector directionVector = asteroids[j].directionVector(best_asteroid); 
        for (const auto & v : directionVectors) {
            if (directionVector.isMultiple(v)) {
                isMultiple = true; 
                break; 
            }
        }
        if (!isMultiple) {
            directionVectors.push_back(directionVector);
            std::cout << directionVector << std::endl;
        }
    }

    std::cout << "-------------------------------------------------------" << std::endl;

    std::sort(directionVectors.begin(), directionVectors.end());

    for (auto & v : directionVectors) {
        std::cout << v << std::endl;
    }

    int destroy_index = 1; 
    
    while (asteroids.size()) { // addig megyünk, ameddig csak van elpusztítani való aszteroida
        for (int i = 0; i < directionVectors.size(); i++) { // minden egyes vektorra megkeressük a legközelebb lévő aszteroidát
            auto & currentVector = directionVectors[i];
            std::vector<int> inLineAsteroidsIndex;
            for (int j = 0; j < asteroids.size(); j++) {   
                auto directionVector = asteroids[j].directionVector(best_asteroid); 
                if (directionVector.isMultiple(currentVector)) {
                    // std::cout << directionVector << " " << asteroids[j] << std::endl;
                    inLineAsteroidsIndex.push_back(j);
                }
            }
            if (inLineAsteroidsIndex.size() > 0) {
                float closest_distance = INFINITY; 
                int closest_index = INT_MAX; 
                // megkeressük a legközelebbit
                for (int j = 0; j < inLineAsteroidsIndex.size(); j++) {
                    // std::cout << asteroids[inLineAsteroidsIndex[j]] << std::endl; 
                    if (asteroids[inLineAsteroidsIndex[j]].distance(best_asteroid) < closest_distance) {
                        closest_distance = asteroids[inLineAsteroidsIndex[j]].distance(best_asteroid); 
                        closest_index = inLineAsteroidsIndex[j];
                    }
                }

                std::cout << destroy_index++ << ". asteroid destroyed is " << asteroids[closest_index] << std::endl;
                asteroids.erase(asteroids.begin() + closest_index); 
            }
        }
    }


    return 0; 
}