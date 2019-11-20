#include <iostream> 
#include <fstream>
#include <sstream>

int main() {
    std::fstream input("input.txt"); 
    std::string line; 
    std::getline(input, line);
    // std::stringstream ss(line) ; 

    /* 
    <>, 0 characters.
    <random characters>, 17 characters.
    <<<<>, 3 characters.
    <{!>}>, 2 characters.
    <!!>, 0 characters.
    <!!!>>, 0 characters.
    <{o"i!a,<{i<a>, 10 characters. 
    */ 

    // std::string line("<random characters>") ; 
    // std::string line("<<<<>") ; 
    // std::string line("<{!>}>"); 
    // std::string line("<!!>"); 
    // std::string line("<!!!>>");
    // std::string line("<{o\"i!a,<{i<a>"); 
    char currentChar; 
    bool cancelNext = false; 
    bool garbage = false;
    uint groupCounter = 0; 
    uint score = 0; 
    uint garbageCounter = 0; 

    for (int i = 0; i < line.size(); i++) {
        currentChar = line[i];
        std::cout << currentChar; 

        if (!cancelNext) {
            switch (currentChar) {
                case '<': 
                    if (garbage)
                        garbageCounter++; 
                    else 
                        garbage = true;
                    break; 
                case '>': 
                    garbage = false;
                    break;
                case '!': 
                    cancelNext = !cancelNext; 
                    break;
                case '{': 
                    if (!garbage) {
                        groupCounter++;
                    } else {
                        garbageCounter++;
                    }
                    break;
                case '}':
                    if (!garbage) {
                        score += groupCounter; 
                        groupCounter--; 
                    } else {
                        garbageCounter++; 
                    }
                    break;                
                default: 
                    if (garbage) 
                        garbageCounter++; 
                    break; 
            }
        } else {
            cancelNext = false;
        }
        std::cout << "Char '" << currentChar << "' gc= " << garbageCounter << std::endl; 
    }
    std::cout << std::endl;
    std::cout << "Score is " << score << std::endl;
    std::cout << "Number of garbage: " << garbageCounter << std::endl;
    return 0;
}