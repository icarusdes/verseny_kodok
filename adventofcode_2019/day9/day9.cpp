#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

bool logging = true; 

int main(int argc, char ** argv) {

    struct cpu_work_memory {
        long long int offset = 0; 
        std::vector<long long int> mem;

        long long int & operator()(const long long int & index, int mode = 0) {
            if (logging) std::cout << __FUNCTION__  << " index is " << index << " mode is " << mode << std::endl;             
            if (((long long int) mem.size()) <= index) {
                mem.resize(index + 1, 0); 
                if (logging) std::cout << __FUNCTION__ << " resized to: "  << mem.size() << std::endl;             
            }

            if (mode == 1) {
                return mem[index];
            } else if (mode == 2) {
                return mem[offset + mem[index]]; 
            }
            return mem[mem[index]];  // mode = 0
        }    
    } memory;

    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
    if (argc >= 3)
        logging = true; 
        
    
    std::string line; 
    getline( input_file, line );
    
    std::stringstream ss(line);

    for (long long int i; ss >> i;) {
        memory.mem.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    long long int currentopt = 0; 
    long long int command = memory(currentopt, 1);
    while ((command % 100) != 99) {   
        if (logging) std::cout << "Command: " << command << std::endl;
        int numparams = 1;
        bool jumped = false; 
        // (command / 20000 ) ? memory[memory.offset + memory[currentopt+3]] : ((command / 10000) ? memory[currentopt+3] : memory[memory[currentopt+3]]); 
        // ha nincs több operandus, akkor sincs belőle baj, mert null inicializáltak és a túl indexelést kezeljük 
        long long int & out = memory(currentopt+3, (command / 10000));       
        if (logging)  std::cout << "Out: " <<  out << std::endl;  
        //  ((command % 10000) / 2000 ) ? memory[memory.offset + memory[currentopt+2]] : (((command % 10000) / 1000) ? memory[currentopt+2] : memory[memory[currentopt+2]]); 
        //  ha nincs több operandus, akkor sincs belőle baj, mert null inicializáltak és a túl indexelést kezeljük 
        long long int & op2 = memory(currentopt+2, ((command % 10000) / 1000));
        if (logging)  std::cout << "Op2: " << op2 << std::endl;  
        // long long int & op1 = ((command % 1000) / 200 ) ? memory[memory.offset + memory[currentopt+1]] : (((command % 1000) / 100) ? memory[currentopt+1] : memory[memory[currentopt+1]]); 
        long long int & op1 = memory(currentopt+1, ((command % 1000) / 100));
        if (logging) std::cout << "Op1: " << memory(currentopt+1, ((command % 1000) / 100)) << std::endl;  
        if (logging) std::cout << "Op1: " << op1 << std::endl;
        
        int opcode = command % 100; 
        if (opcode == 1 || opcode == 2 || opcode == 7 || opcode == 8) {            
            if (opcode == 1)
                out = op1 + op2; 
            else if (opcode == 2)
                out = op1 * op2;
            else if (opcode == 7)
                out = (op1 < op2);
            else                   
                out = (op1 == op2);
            numparams = 3; 

        } else if (opcode == 3) {
            std::cin >> op1;
            numparams = 1; 
        } else if (opcode == 4) {
            std::cout << " " << op1;
            numparams = 1;
        } else if (opcode == 5 || opcode == 6) {
            if (opcode == 5) {
                if (op1) {                    
                    currentopt = op2;
                    jumped = true; 
                } 
            }
            else {
                if (!op1) {
                    currentopt = op2;
                    jumped = true; 
                } 
            }
            numparams = 2;
        } else if (opcode == 9) {
            memory.offset += op1;
            numparams = 1; 
        }

        if (!jumped)
            currentopt = (currentopt + numparams + 1 ) % memory.mem.size();

        command = memory(currentopt, 1);
    } 
    std::cout << std::endl;
    return 0; 
}