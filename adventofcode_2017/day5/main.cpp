#include <iostream>
#include <vector>
#include <fstream>  

int main() {
    int steps = 0; 
    int temp = 0; 
    int ip = 0; 
    int jump = 0; 

    std::fstream input("input.txt"); 
    std::vector<int> offsets; 

    while (input >> temp ) {
        offsets.push_back(temp); 
    }
    std::cout << "Size of the offset " << offsets.size() << std::endl;

    do {
        jump = offsets[ip];
        if (jump >= 3) {
            offsets[ip]--;
        } else {
            offsets[ip]++;
        }

        ip += jump; 
        // std::cout << ip << " " << offsets[ip] << std::endl; 
        
        steps++; 
    } while (ip >= 0 && ip < offsets.size()); 

    std::cout << "Number of steps " << steps << std::endl;
}