#include <iostream>

/* If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
{20,48,52}, {24,45,51}, {30,40,50}
For which value of p ≤ 1000, is the number of solutions maximised? */ 

using uint = unsigned int;

int main() {
    uint maxNumberOfSolutions = 0; 
    uint maxI = 0; 
    for (int i = 4; i <= 1000; i++) {
        uint numberOfSolutions = 0; 
        for (uint a = 1; a < i; a++)
            for (uint b = a; b < i - a; b++) {
                uint c = i - a - b; 
                if (c * c == a * a + b * b)
                    numberOfSolutions++; 
            }
        if (numberOfSolutions > maxNumberOfSolutions) {
            maxNumberOfSolutions = numberOfSolutions; 
            maxI = i;  
        }
    }

    std::cout << "Max number of solution is " << maxNumberOfSolutions << " for integer " << maxI << std::endl;
    return 0;
}