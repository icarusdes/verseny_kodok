#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  

long unsigned int hash(std::vector<uint32_t> const& vec) {
  long unsigned int seed = vec.size();
  for(auto& i : vec) {
    seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

int main() {

    std::vector<uint32_t> memory =  {4,	1, 15, 12, 0, 9, 9, 5, 5, 8, 7, 3, 14, 5, 12, 3 };
    long unsigned int currenthash = hash(memory); 
    std::vector<long unsigned int> hashes; 

    uint numelements = memory.size(); 
    uint relocations = 0; 

    auto pos = hashes.begin(); 


    do {
        hashes.push_back(currenthash); 
        auto print = [] (const long unsigned int & v) { std::cout << v << " "; }; 
        // std::for_each(memory.begin(), memory.end(), print ); 
        // std::cout << std::endl; 
        // std::cout << relocations << std::endl;
        uint max = 0; 
        uint maxindex = 0; 

        for (uint i = 0; i < numelements; i++) {
        //     std::cout << i << std::endl;
            if (max < memory[i]) {
                max = memory[i]; 
                maxindex = i; 
            }
        }

        memory[maxindex] = 0; 
        maxindex = (maxindex + 1) % numelements;
        // std::cout << "Max found " << maxindex <<std::endl;

        while (max) {
        //     std::cout << maxindex << std::endl;
            memory[maxindex]++; 
            maxindex = (maxindex + 1) % numelements;
            max--; 
        }
        relocations++; 
        currenthash = hash(memory); 
    } while ((pos = std::find(hashes.begin(), hashes.end(), currenthash)) == hashes.end()); 

    std::cout << "Number of relocations: " << relocations << std::endl; 
    std::cout << "Length of cycle: " << hashes.end() - pos << std::endl;

    return 0; 
}