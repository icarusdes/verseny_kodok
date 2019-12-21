#include <ostream>
#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <utility>
#include <stdio.h>

struct point {
    int x = 0, y = 0, z = 0;
    int vx = 0, vy = 0, vz = 0; 

    friend std::ostream & operator<< (std::ostream & o, const point & p);

    inline int potential_energy() {
        return abs(x) + abs(y) + abs(z);    
    };

    inline int kinetic_energy() {
        return abs(vx) + abs(vy) + abs(vz);
    };

    inline int energy() {
        return potential_energy() * kinetic_energy(); 
    };

}; 

std::ostream & operator<< (std::ostream & o, const point & p) {
    o << "{ x=" << p.x << ", y=" << p.y << ", z=" << p.z << ", vx=" << p.vx << ", vy=" << p.vy << ", vz=" << p.vz << " }"; 
    return o;
}; 

void print_energy (const point &p ) {
    int pot = abs(p.x) + abs(p.y) + abs(p.z);
    int kin = abs(p.vx) + abs(p.vy) + abs(p.vz);
    std::cout << "pot: " << abs(p.x) << "\t + " << abs(p.y) << "\t + " << abs(p.z) << "\t  = " << pot << "; \t" << "Kin: " << 
                  abs(p.vx) << "\t  + " << abs(p.vy) << "\t  + " << abs(p.vz) << "\t  = " << kin << "\t Sum: " << kin*pot << std::endl;
}


int main(int argc, char ** argv) 
    {

    /* Test input 1 */ 
    /* 
    point p1  = {-1,   0,  2, 0, 0, 0};
    point p2  = {2 , -10, -7, 0, 0, 0};
    point p3  = {4 ,  -8,  8, 0, 0, 0};
    point p4  = {3 ,   5, -1, 0, 0, 0};
    int limit = 10;
    */ 

    /* Test input 2 */ 
    /* 
    point p1  = {-8, -10,  0, 0, 0, 0};
    point p2  = { 5,   5, 10, 0, 0, 0};
    point p3  = { 2,  -7,  3, 0, 0, 0};
    point p4  = { 9,  -8, -3, 0, 0, 0};
    int limit = 100;
    */ 

    /* Real input */ 
    point p1  = {3, 3,  0  , 0, 0, 0};
    point p2  = {4, -16, 2 , 0, 0, 0};
    point p3  = {-10, -6, 5, 0, 0, 0};
    point p4  = {-3, 0, -13, 0, 0, 0};
    int limit = 1000;    

    std::vector<point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    int steps = 0; 
    while (steps < limit) {

        if (steps % 10 == 0) {
            std::cout << "After " << steps << " steps: " << std::endl; 
            std::cout << points[0] << std::endl;
            std::cout << points[1] << std::endl;
            std::cout << points[2] << std::endl;
            std::cout << points[3] << std::endl;
            std::cout << std::endl;
        }


        for (int i = 0; i < points.size(); i++) {
            for (int j = i; j < points.size(); j++) {
                if (i == j)
                    continue;
                else {
                    point & p1 = points[i];
                    point & p2 = points[j];
                    if (p1.x < p2.x) {p1.vx += 1; p2.vx -= 1;} else if (p2.x < p1.x) {p1.vx -= 1; p2.vx += 1;};
                    if (p1.y < p2.y) {p1.vy += 1; p2.vy -= 1;} else if (p2.y < p1.y) {p1.vy -= 1; p2.vy += 1;};
                    if (p1.z < p2.z) {p1.vz += 1; p2.vz -= 1;} else if (p2.z < p1.z) {p1.vz -= 1; p2.vz += 1;};
                }
            }
        }

        for (int i = 0; i < points.size(); i++) {
            point & p1 = points[i];
            p1.x += p1.vx; 
            p1.y += p1.vy; 
            p1.z += p1.vz; 
        }
        steps++; 
    }

    std::cout << points[0] << std::endl;
    std::cout << points[1] << std::endl;
    std::cout << points[2] << std::endl;
    std::cout << points[3] << std::endl;
    print_energy(points[0]);
    print_energy(points[1]);
    print_energy(points[2]);
    print_energy(points[3]);

    std::cout << points[0].energy() + points[1].energy() + points[2].energy() + points[3].energy() << std::endl; 

    std::cout << "Thx" << std::endl; 
}
