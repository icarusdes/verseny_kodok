#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

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

    int currentopt = 0; 
    int last_command_index = 0;
    while ((commands[currentopt] % 100) != 99) {   
        int command = commands[currentopt];
        int numparams = 1;
        bool jumped = false; 
        int & op1 = ((command % 1000) / 100) ? commands[currentopt+1] : commands[commands[currentopt+1]]; 
             
        int opcode = command % 100; 
        if (opcode == 1 || opcode == 2 || opcode == 7 || opcode == 8) {
            int & op2 = ((command % 10000) / 1000) ? commands[currentopt+2] : commands[commands[currentopt+2]] ;                  
            int & out = (command / 10000) ? commands[currentopt+3] : commands[commands[currentopt+3]];  
                
            numparams = 3; 
            
            // std::cout << command << " " << commands[currentopt+1] << " " << commands[currentopt+2] << " " << commands[currentopt+3] << std::endl;
            // std::cout << " - "  << command << " " << op1 << " " << op2 << " " << out << std::endl;

            if (opcode == 1)
                out = op1 + op2; 
            else if (opcode == 2)
                out = op1 * op2;
            else if (opcode == 7)
                out = (op1 < op2);
            else                   
                out = (op1 == op2);

        } else if (opcode == 3) {
            // std::cout << command << " " << commands[currentopt+1] << std::endl;
            // std::cout << " - " << command << " " << op1 << std::endl;
            std::cin >> op1;
            numparams = 1; 
        } else if (opcode == 4) {
            std::cout << " ---------------------------" << command << " " << op1 << std::endl;
            numparams = 1;
        } else if (opcode == 5 || opcode == 6) {
            int & op2 = ((command % 10000) / 1000) ? commands[currentopt+2] : commands[commands[currentopt+2]] ;
            // std::cout << command << " " << commands[currentopt+1] << " " << commands[currentopt+2] << std::endl;
            // std::cout << command << " " << op1 << " " << op2 << std::endl;            
            if (opcode == 5) {
                // std::cout << "Jump if true" << std::endl; 
                if (op1) {                    
                    currentopt = op2;
                    jumped = true; 
                } 
            }
            else {
                // std::cout << "Jump if false" << std::endl; 
                if (!op1) {
                    currentopt = op2;
                    jumped = true; 
                } 
            }
            numparams = 2;
        }
        if (!jumped)
            currentopt = (currentopt + numparams + 1 ) % commands.size(); 
        // std::cout << "instruction pointer is " << currentopt << std::endl;
    }

    return 0; 
}