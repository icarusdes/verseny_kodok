#include <iostream>
#include <map>

/* 

Begin in state A.
Perform a diagnostic checksum after 12586542 steps.

In state A:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state B.

In state B:
  If the current value is 0:
    - Write the value 0.
    - Move one slot to the right.
    - Continue with state C.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state B.

In state C:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state D.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state A.

In state D:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state E.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state F.

In state E:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state A.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state D.

In state F:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state A.
  If the current value is 1:
    - Write the value 1.
    - Move one slot to the left.
    - Continue with state E.

*/ 

enum States { 
A, 
B, 
C, 
D, 
E, 
F
}; 

using uint64 = long long unsigned int; 

int main() {
    // uint64 iterations = 10;
    uint64 iterations = 12586542;
    long long int pos_x = 0;
    States actualState = States::A; 
    std::map<int, int> memory;
    int max_x = 0, min_x = 0; 

    while (iterations--) {
        switch (actualState) {
            case States::A: 
                if (memory[pos_x] == 0) {
                    memory[pos_x] = 1;
                    pos_x++; 
                } else {
                    memory[pos_x] = 0;
                    pos_x--; 
                }
                actualState = States::B; 
                break; 
            case States::B: 
                if (memory[pos_x] == 0) {
                    pos_x++;
                    actualState = States::C; 
                } else {
                    pos_x--; 
                }
                break; 
            case States::C: 
                if (memory[pos_x] == 0) {
                    memory[pos_x] = 1; 
                    pos_x++;
                    actualState = States::D; 
                } else {
                    memory[pos_x] = 0;
                    pos_x--; 
                    actualState = States::A;
                }
                break;            
            case States::D: 
                if (memory[pos_x] == 0) {
                    memory[pos_x] = 1; 
                    pos_x--;
                    actualState = States::E; 
                } else {
                    pos_x--; 
                    actualState = States::F;
                }
                break;         
            case States::E: 
                if (memory[pos_x] == 0) {
                    memory[pos_x] = 1; 
                    pos_x--;
                    actualState = States::A; 
                } else {
                    memory[pos_x] = 0; 
                    pos_x--; 
                    actualState = States::D;
                }
                break;
            case States::F:
                if (memory[pos_x] == 0) {
                    memory[pos_x] = 1; 
                    pos_x++;
                    actualState = States::A; 
                } else {
                    pos_x--; 
                    actualState = States::E;
                }
                break;            
            default: 
                std::cout << "Valami furcsa hiba történt " << std::endl;
                exit(0);
        }
        if (pos_x > max_x)
            max_x = pos_x; 
        if (pos_x < min_x) 
            min_x = pos_x; 
    }

    std::cout << "Greatest x value is: " << max_x << std::endl;
    std::cout << "Lowest x value is: " << min_x << std::endl;
    int numberOfOnes = 0; 

    for (int i = min_x; i <= max_x; i++) {
        if (memory[i] == 1) 
            numberOfOnes++; 
    }

    std::cout << "Number of ones: " << numberOfOnes << std::endl; 
}