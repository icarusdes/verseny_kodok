#include <iostream> 
#include <vector>

int main() {

    std::vector<uint> numbers = {0}; 
    uint currentPos = 0; 
    uint jump = 303; 
    // uint jump = 3; 

    for (uint i = 1; i < 2018; i++) {
        numbers.insert(numbers.begin() + currentPos + 1, i); 
        
        currentPos++; 

        for (uint j = 0; j < numbers.size(); j++) {
            if (j == currentPos) 
                std::cout << "("; 
            std::cout << numbers[j]; 
            if (j == currentPos) 
                std::cout << ")"; 
            std::cout << " "; 
        }
        std::cout << std::endl;

        currentPos = (currentPos + jump) % numbers.size(); 
    }

    return 0; 
}