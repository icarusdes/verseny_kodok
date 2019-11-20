#include <iostream> 
#include <vector>
#include <algorithm>

int main() {
    uint currentPos = 0; 
    uint jump = 303; 
    uint numAfterZero = 0; 
    uint size = 1; 
    // uint jump = 3; 

    for (uint i = 1; i < 50000000; i++) {    

        if (currentPos == 0) {
            std::cout << "Value updated to: " << i << std::endl;
            numAfterZero == i;
        }
        size++; 
        
        if (i % 1000000 == 0) {
            std::cout << i << std::endl;
        }

        currentPos = (currentPos + 1 + jump) % size; 
    }
    std::cout << "The number after 0 is: " << numAfterZero << std::endl; 

    return 0; 
}