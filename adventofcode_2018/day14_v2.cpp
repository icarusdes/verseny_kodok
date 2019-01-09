#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stdio.h>
#include <ctype.h> 
#include <boost/regex.hpp>

int main(int argc, char ** argv) {
    std::vector<int> recipes = {3, 7}; 
    int elf1 = 0; 
    int elf2 = 1; 
    int stop_for = 880751;
    while (true) {
        int sum = recipes[elf1] + recipes[elf2]; 
        int r1 = sum / 10; 
        int r2 = sum % 10; 

        if (r1) 
            recipes.push_back(r1); 
        recipes.push_back(r2); 
        int rsize = recipes.size(); 
        elf1 = (elf1 + recipes[elf1] + 1) % rsize;
        elf2 = (elf2 + recipes[elf2] + 1) % rsize;

        if (rsize > 7) {
            int num1 = recipes[rsize - 7] * 100000 + recipes[rsize - 6] * 10000 + recipes[rsize - 5] * 1000 + recipes[rsize - 4] * 100 + recipes[rsize - 3] * 10 + recipes[rsize - 2] * 1; 
            int num2 = recipes[rsize - 6] * 100000 + recipes[rsize - 5] * 10000 + recipes[rsize - 4] * 1000 + recipes[rsize - 3] * 100 + recipes[rsize - 2] * 10 + recipes[rsize - 1] * 1; 
            if (num1 == stop_for || num2 == stop_for)
                break; 
        }
    }

    std::cout << recipes.size() - 6 << std::endl; 

    return 0; 
}