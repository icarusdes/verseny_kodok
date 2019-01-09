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
    int recipe_nums_from = 880751;
    int cround = 0;  
    while (recipes.size() < (recipe_nums_from + 10)) {
        int sum = recipes[elf1] + recipes[elf2]; 
        int r1 = sum / 10; 
        int r2 = sum % 10; 

        if (r1) 
            recipes.push_back(r1); 
        recipes.push_back(r2); 

        /* std::cout << cround << "\t"; 
        for (int i = 0; i < recipes.size(); i++) {
            if (elf1 == i) { 
                std::cout << "("; 
            }
            if (elf2 == i) { 
                std::cout << "["; 
            }
            std::cout << recipes[i]; 
            if (elf1 == i) { 
                std::cout << ")"; 
            }
            if (elf2 == i) { 
                std::cout << "]"; 
            }
            std::cout << " "; 
        }
        std::cout << std::endl; */ 
        elf1 = (elf1 + recipes[elf1] + 1) % recipes.size();
        elf2 = (elf2 + recipes[elf2] + 1) % recipes.size();
        cround++; 
        if (recipes.size() % 1000 == ) {
            std::cout << recipe.size() << std::endl; 
        }
    }

    for (int i = 0; i < 10; i++) {
        std::cout << recipes[recipe_nums_from + i]; 
    }
    std::cout << std::endl; 

    return 0; 
}