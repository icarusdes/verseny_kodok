#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input.txt"); 
    int sum = 0;
    std::vector<int> commands; 

    std::string line; 
    getline( input_file, line );
    
    std::stringstream ss(line);

    for (int i; ss >> i;) {
        commands.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    int currentopt = 0; 
    while (commands[currentopt] != 99) {
        int command = commands[currentopt]; 
        int op1 = commands[currentopt+1]; 
        int op2 = commands[currentopt+2]; 
        int out = commands[currentopt+3]; 
        if (command == 1) {
            commands[out] = commands[op1] + commands[op2]; 
        } else if (command == 2) {
            commands[out] = commands[op1] * commands[op2]; 
        }
        currentopt = (currentopt + 4) % commands.size(); 
    }

    std::cout << commands[0] << std::endl; 

    return 0; 
}