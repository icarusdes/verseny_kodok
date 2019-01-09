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

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day5.txt"); 
    std::string line; 
    getline( input_file, line ); 
    
    
    int shortest = line.size(); 
    int shortest_char = 'a';

    for (int i = 'a'; i <= 'w'; i++) {
        std::string line_copy = line;
        for (auto it = line_copy.end() - 1; it != line_copy.begin(); it--) {
            if (toupper(*it) == toupper(i))
                line_copy.erase(it);
        }
        bool reacted = true; 
        while (reacted) {
            reacted = false; 
            for (auto it = line_copy.begin(); it != (line_copy.end()-1); it++) {
                if (
                    ( 
                    (isupper(*it) && islower(*(it+1))) || 
                    (islower(*it) && isupper(*(it+1)))
                    ) 
                    && 
                    (
                    toupper(*it) == toupper(*(it+1))
                    )
                ) 
                {
                    line_copy.erase(it+1); 
                    line_copy.erase(it); 
                    reacted = true;
                    break; 
                }
            }
        }
        int size = line_copy.size(); 
        if (shortest > size) {
            shortest = size; 
            shortest_char = i; 
        }
        std::cout << "Char: " << (char) i << " length:  " << shortest << std::endl; 
    }
    return 0; 
}