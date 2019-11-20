#include <iostream>

int main() {
    int counter = 0; 
    int goodCounter = 0; 

    long long unsigned int A = 516; 
    long long unsigned int B = 190; 

    // while (counter < 6) {
    while (counter < 40000000) {
        A = (A * 16807) % 2147483647; 
        B = (B * 48271) % 2147483647; 
        if ((A & 0xFFFF) == (B & 0xFFFF)) {
            goodCounter++; 
        }
        counter++;
    }
    std::cout << "Number of equals " << goodCounter << std::endl; 
}