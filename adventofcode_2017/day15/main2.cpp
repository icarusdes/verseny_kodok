#include <iostream>

int main() {
    int counter = 0; 
    int lastcounter = -1;
    int goodCounter = 0; 

    // long long unsigned int A = 65;
    // long long unsigned int B = 8921;

    long long unsigned int A = 516; 
    long long unsigned int B = 190; 

    // while (counter < 6) {
    while (counter < 5000000) {
        // std::cout << "Counter is " << counter << std::endl; 
        A = (A * 16807) % 2147483647; 
        while ((A % 4) != 0 && (counter != lastcounter)) {
            A = (A * 16807) % 2147483647; 
            // std::cout << "Generated A " << A << std::endl; 
        }
        B = (B * 48271) % 2147483647; 
        while ((B % 8) != 0 && (counter != lastcounter)) {
            B = (B * 48271) % 2147483647; 
            // std::cout << "Generated B " << B << std::endl; 
        }
        if ((A & 0xFFFF) == (B & 0xFFFF)) {
            goodCounter++; 
        }
        lastcounter = counter; 
        counter++;
    }
    std::cout << "Number of equals " << goodCounter << std::endl; 
}