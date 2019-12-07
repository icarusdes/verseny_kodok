#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

int compute(std::vector<int> program, std::vector<int> inputs) {
    int currentopt = 0; 
    int last_command_index = 0;
    int current_input = 0; 
    while ((program[currentopt] % 100) != 99) {   
        int command = program[currentopt];
        int numparams = 1;
        bool jumped = false; 
        int & op1 = ((command % 1000) / 100) ? program[currentopt+1] : program[program[currentopt+1]]; 
             
        int opcode = command % 100; 
        if (opcode == 1 || opcode == 2 || opcode == 7 || opcode == 8) {
            int & op2 = ((command % 10000) / 1000) ? program[currentopt+2] : program[program[currentopt+2]] ;                  
            int & out = (command / 10000) ? program[currentopt+3] : program[program[currentopt+3]];  
                
            numparams = 3; 
            if (opcode == 1)
                out = op1 + op2; 
            else if (opcode == 2)
                out = op1 * op2;
            else if (opcode == 7)
                out = (op1 < op2);
            else                   
                out = (op1 == op2);

        } else if (opcode == 3) {
            if (current_input > inputs.size()) {
                std::cout << "Please provide an input than hit enter: "; 
                std::cin >> op1;
            } else {
                op1 = inputs[current_input++]; 
            }
            numparams = 1; 
        } else if (opcode == 4) {
            return op1;
            numparams = 1;
        } else if (opcode == 5 || opcode == 6) {
            int & op2 = ((command % 10000) / 1000) ? program[currentopt+2] : program[program[currentopt+2]] ;
            if (opcode == 5) {
                if (op1) {                    
                    currentopt = op2;
                    jumped = true; 
                } 
            } else {
                if (!op1) {
                    currentopt = op2;
                    jumped = true; 
                } 
            }
            numparams = 2;
        }
        if (!jumped)
            currentopt = (currentopt + numparams + 1 ) % program.size(); 
    }
    return -1; 
}

int main(int argc, char ** argv) {
    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
    
    std::vector<int> commands; 
    std::string line; 
    getline( input_file, line );
    std::stringstream ss(line);

    for (int i; ss >> i;) {
        commands.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    std::vector<int> max_output_provider; 
    int max_output = INT_MIN; 

    std::vector<int> phases = {0,1,2,3,4};
    std::sort (phases.begin(),phases.end());
    do {
        int v1 = compute(commands, {phases[0], 0});
        int v2 = compute(commands, {phases[1], v1});
        int v3 = compute(commands, {phases[2], v2});
        int v4 = compute(commands, {phases[3], v3});
        int v5 = compute(commands, {phases[4], v4});
        if (v5 > max_output) {
            max_output = v5;
            max_output_provider = phases;
        }
        std::cout << "Current output: " << v5 << " current phases "; 
        for (auto i :  phases)
            std::cout << i << " "; 
        std::cout << std::endl;
    } while ( std::next_permutation(phases.begin(),phases.end()) );

    std::cout << "Highest output is: " << max_output << std::endl;

    return 0; 
}