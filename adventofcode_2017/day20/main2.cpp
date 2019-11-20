
#include <string>
#include <boost/regex.hpp>
#include <fstream>
#include <iostream> 
#include <algorithm>

struct particle {
    int pos_x;
    int pos_y;
    int pos_z;
    int vel_x;
    int vel_y;
    int vel_z;
    int acc_x;
    int acc_y;
    int acc_z;
    int _id; 

    particle(int v1 = 0,int v2 = 0, int v3 = 0, int v4 = 0, int v5 = 0, int v6 = 0, int v7 = 0, int v8 = 0, int v9 = 0) : pos_x(v1), 
        pos_y(v2), pos_z(v3), vel_x(v4), vel_y(v5), vel_z(v6), acc_x(v7), acc_y(v8), acc_z(v9) {
    }

    void step() {
        vel_x += acc_x; 
        vel_y += acc_y; 
        vel_z += acc_z; 
        pos_x += vel_x; 
        pos_y += vel_y; 
        pos_z += vel_z; 
    }

    int collisionTimeWith(const particle & other) {
        
    }

    bool operator==(const particle & other) const { 
        return pos_x == other.pos_x && pos_y == other.pos_y && pos_z == other.pos_z; 
    }
    
    bool operator<(const particle & other) const {
        if (pos_x != other.pos_x) 
            return pos_x < other.pos_x; 
        if (pos_y != other.pos_y) 
            return pos_y < other.pos_y; 
        if (pos_z != other.pos_z) 
            return pos_z < other.pos_z;
        if (vel_x != other.vel_x) 
            return vel_x < other.vel_x;
        if (vel_y != other.vel_y) 
            return vel_y < other.vel_y; 
        if (vel_z != other.vel_z) 
            return vel_z < other.vel_z;
        if (acc_x != other.acc_x) 
            return acc_x < other.acc_x;
        if (acc_y != other.acc_y) 
            return acc_y < other.acc_y;
        if (acc_z != other.acc_z) 
            return acc_z < other.acc_z;
        return _id < other._id; 
    }
}; 

int main() {
    std::fstream input("input.txt"); 
    std::string line; 
    boost::regex matchCoords("p=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>, v=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>, a=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>.*"); 
    boost::smatch matches; 
    std::vector<particle> particles; 
    int min_accel = INT_MAX; 
    int min_accel_index = 0; 
    int index = 0; 

    while (std::getline(input, line)) {
        if (boost::regex_match(line, matches, matchCoords) ) {
            int pos_x = stoi(matches[1]);
            int pos_y = stoi(matches[2]);
            int pos_z = stoi(matches[3]);
            int vel_x = stoi(matches[4]);
            int vel_y = stoi(matches[5]);
            int vel_z = stoi(matches[6]);
            int acc_x = stoi(matches[7]);
            int acc_y = stoi(matches[8]);
            int acc_z = stoi(matches[9]);
// #ifdef DEBUG
            std::cout << index << " pos(x, y, z) is " << "(" << pos_x << "," << pos_y << "," << pos_z << ") \t" \
                      << "vel(x, y, z) is " << "(" << vel_x << "," << vel_y << "," << vel_z << ") \t" << "acc(x, y, z) is " << "(" << acc_x << "," << acc_y << "," << acc_z << ")  " << std::endl; 
// #endif  
            particle p(pos_x, pos_y, pos_z, vel_x, vel_y, vel_z, acc_x, acc_y, acc_z); 
            p._id = index;
            particles.push_back(p);
            index++; 
        }
    }

    std::cout << "Data loaded" << std::endl; 

    for (int i = 0; i < 1000; i++) {

        int before = particles.size(); 
        std::sort(particles.begin(), particles.end());
        std::vector<particle> toRemove; 

        for (int j = 0; j < particles.size()-1 ; j++) {
            if (particles[j] == particles[j+1]) 
                toRemove.push_back(particles[j]); 
        }
        for (int j = 0; j < toRemove.size(); j++) {
            particles.erase(std::remove(particles.begin(), particles.end(), toRemove[j]), particles.end()); 
        }

        for (int j = 0; j < particles.size() ; j++) {
            particles[j].step();
        }
        int after = particles.size(); 

        std:: cout << i << " number of removed elements " << before - after << std::endl; 
        std:: cout << i << " remaining elements " << after << std::endl; 
    }
    std::cout << std::endl;


    return 0; 
}