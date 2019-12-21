#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <deque>
#include <sstream>
#include <climits>
#include <assert.h>
#include <chrono>
#include <thread>

bool logging = false; 

struct field {
    int x = {0}; 
    int y = {0};
    int color = {0}; 
}; 

enum class cpu_state {
    halted, 
    waiting_for_input, 
    running, 
    Count
};

struct ball_type {
    int x = {-1}; 
    int y = {-1};
    int x_dir = {0}; 
    int y_dir = {0};  
}; 

struct paddle_type {
    int x = {0}; 
    int y = {0}; 
};

struct cpu {
    struct cpu_work_memory {
        long long int offset = 0; 
        std::vector<long long int> mem;

        long long int & operator()(const long long int & index, int mode = 0) {
            if (logging)
                std::cout << __FUNCTION__ << " " << index << " " << mem.size() << " " << mode << std::endl; 
            if ((offset + index) < 0 ) {
                std::cout << "Ilyen nem kellene legyen" << std::endl; 
                exit(0); 
            }            
            if ((long long int) mem.size() <= index)   
            {   
                if (logging) std::cout << "\t resize 1 " << index << std::endl;
                mem.resize(index+1, 0); 
            }

            int real_index = 0; 
            if (mode == 0) {
                real_index = mem[index]; 
            } else if (mode == 1) {
                real_index = index;
            } else if (mode == 2) {
                real_index = offset + mem[index]; 
            }
            if ((long long int) mem.size() <= real_index)   
            {   
                if (logging) std::cout << "\t resize 2 " << real_index << std::endl;
                mem.resize(real_index+1, 0); 
            }
            return mem[real_index];
        }    
    } memory;

    void loadProgram(const std::string & program ) {
        std::stringstream ss(program);
        for (long long int i; ss >> i;) {
            memory.mem.push_back(i);    
            if (ss.peek() == ',')
                ss.ignore();
        }
    }

    long long int currentopt = 0;
    long long int numreads = 0;
    long long int numwrites = 0;
    cpu_state state = cpu_state::running;

    size_t getOutPutQueueSize() const {
        return outputs.size();
    }

    long long int readOutPut() {
        auto & temp = outputs.front(); 
        outputs.pop_front(); 
        return temp; 
    }

    void writeInput(const long long int & v) {
        inputs.push_back(v); 
        if (state == cpu_state::waiting_for_input) 
            state = cpu_state::running; 
    }

    void iterate() {
        if (logging) std::cout << __FUNCTION__ << std::endl;
        if (state == cpu_state::running) {
            long long int command = memory(currentopt, 1);
            if ((command % 100) != 99) {               
                int numparams = 1;
                bool jumped = false; 

                if (logging)  std::cout << "Command: " << command << std::endl;  
                if (logging)  std::cout << "Op1: " <<  memory(currentopt+1, 1) << std::endl;
                if (logging)  std::cout << "Op2: " <<  memory(currentopt+2, 1) << std::endl;
                if (logging)  std::cout << "Out: " <<  memory(currentopt+3, 1) << std::endl;

                long long int & out = memory(currentopt+3, (command / 10000));       
                long long int & op2 = memory(currentopt+2, ((command % 10000) / 1000));       
                long long int & op1 = memory(currentopt+1, ((command % 1000) / 100));

                if (logging)  std::cout << "Command: " << command << std::endl;  
                if (logging)  std::cout << "Op1: " <<  op1 << std::endl;
                if (logging)  std::cout << "Op2: " <<  op2 << std::endl;
                if (logging)  std::cout << "Out: " <<  out << std::endl;
                
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
                    if (inputs.size()) {
                        op1 = inputs.front();
                        inputs.pop_front();
                        numparams = 1;
                        numreads++; 
                    } else {
                        state = cpu_state::waiting_for_input; 
                        return; 
                    }
                } else if (opcode == 4) {
                    numwrites++; 
                    outputs.push_back(op1); 
                    numparams = 1;
                } else if (opcode == 5 || opcode == 6) {
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
                } else if (opcode == 9) {
                    memory.offset += op1;
                    numparams = 1; 
                }
                if (command == 0) {
                    exit(0);
                }
                if (!jumped)
                    currentopt = (currentopt + numparams + 1 ) % memory.mem.size();
            } else {
                state = cpu_state::halted;
            }            
        }
    }

    void reset_cpu() {
        memory.mem.clear();
        memory.mem.shrink_to_fit(); 
        memory.offset = 0; 
        inputs.clear(); 
        outputs.clear(); 
        currentopt = 0; 
        numreads = 0; 
        numwrites = 0; 
        state = cpu_state::running; 
    }

    private: 
        std::deque<long long int> inputs; 
        std::deque<long long int> outputs; 
}; 

void test_cpu() {
    
    cpu t_cpu; 
    
    /* Day 2 test cases */ 
    {
        /* Basic TEST 1 */ 
        {
            t_cpu.loadProgram("1,0,0,0,99");
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Basic Test 1 ";
            if (t_cpu.memory.mem[0] == 2) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n"; 
        }

        /* Basic TEST 2 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("2,3,0,3,99"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Basic Test 2 ";
            if (t_cpu.memory.mem[3] == 6) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n"; 
        }

        /* Basic TEST 3 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("2,4,4,5,99,0"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Basic Test 3 ";
            if (t_cpu.memory.mem[5] == 9801) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n";     
        }
        /* Basic TEST 4 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1,1,1,4,99,5,6,0,99"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Basic Test 4 ";
            if (t_cpu.memory.mem[0] == 30 && t_cpu.memory.mem[4] == 2) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n";
        }
        /* Complex test 1*/ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1,9,10,3,2,3,11,0,99,30,40,50"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Complex Test 1 ";
            if (t_cpu.memory.mem[0] == 3500 && t_cpu.memory.mem[3] == 70) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n";
        }
        /* Complex test 2*/ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,6,1,19,1,5,19,23,2,9,23,27,1,6,27,31,1,31,9,35,2,35,10,39,1,5,39,43,2,43,9,47,1,5,47,51,1,51,5,55,1,55,9,59,2,59,13,63,1,63,9,67,1,9,67,71,2,71,10,75,1,75,6,79,2,10,79,83,1,5,83,87,2,87,10,91,1,91,5,95,1,6,95,99,2,99,13,103,1,103,6,107,1,107,5,111,2,6,111,115,1,115,13,119,1,119,2,123,1,5,123,0,99,2,0,14,0"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Complex Test 2 ";
            if (t_cpu.memory.mem[0] == 3101844) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n";
        }
        /* Complex test 3*/ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1,84,78,3,1,1,2,3,1,3,4,3,1,5,0,3,2,6,1,19,1,5,19,23,2,9,23,27,1,6,27,31,1,31,9,35,2,35,10,39,1,5,39,43,2,43,9,47,1,5,47,51,1,51,5,55,1,55,9,59,2,59,13,63,1,63,9,67,1,9,67,71,2,71,10,75,1,75,6,79,2,10,79,83,1,5,83,87,2,87,10,91,1,91,5,95,1,6,95,99,2,99,13,103,1,103,6,107,1,107,5,111,2,6,111,115,1,115,13,119,1,119,2,123,1,5,123,0,99,2,0,14,0"); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Complex Test 3 ";
            if (t_cpu.memory.mem[0] == 19690720) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n";
        }
    }

    /* Day 5 test cases */ 
    {
         /* Input test 1 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("3,0,4,0,99"); 
            t_cpu.writeInput(5); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Input test 1";
            if (t_cpu.readOutPut() == 5) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n"; 
        }

        /* Input test 1 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("3,0,4,0,99"); 
            t_cpu.writeInput(5); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Input test 1";
            if (t_cpu.readOutPut() == 5) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n"; 
        }

        /* Immediate mode test 1 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1002,4,3,4,33");  
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Immediate mode test 1";
            if (t_cpu.memory.mem[4] == 99) 
                std::cout << " PASSED\n"; 
            else 
                std::cout << " FAILED\n"; 
        }

        /* Negative numbers test 1 */ 
        {
            t_cpu.reset_cpu(); 
            t_cpu.loadProgram("1101,100,-1,4,0");  
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Negative numbers test 1";
            if (t_cpu.memory.mem[4] == 99) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n"; 
        }

        /* Day five unit test 1 */ 
        {
            std::fstream input_file; 
            input_file.open("../int_code_test_files/day5_input.txt");     
            std::string line; 
            getline( input_file, line );
            

            t_cpu.reset_cpu();
            t_cpu.loadProgram(line); 
            
            t_cpu.writeInput(1); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Day five unit test 1\n";
            while (t_cpu.getOutPutQueueSize() >= 2) {
                if (t_cpu.readOutPut() == 0)  
                    std::cout << "\tPASSED\n"; 
                else 
                    std::cout << "\tFAILED\n";
            }
            if (t_cpu.readOutPut()  == 9775037) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n"; 
        }

        /* Day five - part two unit tests 1*/ 
        {
            /* 
            3,9,8,9,10,9,4,9,99,-1,8 - Using position mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,9,8,9,10,9,4,9,99,-1,8"); 
            
            t_cpu.writeInput(8); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 1";
            if (t_cpu.readOutPut()  == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";            
        }

        /* Day five - part two unit tests 2*/ 
        {
            /* 
            3,9,8,9,10,9,4,9,99,-1,8 - Using position mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,9,8,9,10,9,4,9,99,-1,8"); 
            
            t_cpu.writeInput(7); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 2";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";            
        }

        /* Day five - part two unit tests 3 */ 
        {
            /* 
            3,9,7,9,10,9,4,9,99,-1,8 - Using position mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,9,7,9,10,9,4,9,99,-1,8"); 
            
            t_cpu.writeInput(7); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 3";
            if (t_cpu.readOutPut() == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 4 */ 
        {
            /* 
            3,9,7,9,10,9,4,9,99,-1,8 - Using position mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,9,7,9,10,9,4,9,99,-1,8"); 
            
            t_cpu.writeInput(8); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 4";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 5 */ 
        {
            /* 
            3,3,1108,-1,8,3,4,3,99 - Using immediate mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1108,-1,8,3,4,3,99"); 
            
            t_cpu.writeInput(8); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 5";
            if (t_cpu.readOutPut() == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 6 */ 
        {
            /* 
            3,3,1108,-1,8,3,4,3,99 - Using immediate mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1108,-1,8,3,4,3,99"); 
            
            t_cpu.writeInput(7); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 6";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 7 */ 
        {
            /* 
            3,3,1107,-1,8,3,4,3,99 - Using immediate mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1107,-1,8,3,4,3,99"); 
            
            t_cpu.writeInput(7); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 7";
            if (t_cpu.readOutPut() == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 8 */ 
        {
            /* 
            3,3,1107,-1,8,3,4,3,99 - Using immediate mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1107,-1,8,3,4,3,99"); 
            
            t_cpu.writeInput(9); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 8";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 9 */ 
        {
            /* 
            Here are some jump tests that take an input, then output 0 if the input was zero or 1 if the input was non-zero:
            3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 (using position mode)
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9"); 
            
            t_cpu.writeInput(0); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 9";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 10 */ 
        {
            /* 
            Here are some jump tests that take an input, then output 0 if the input was zero or 1 if the input was non-zero:
            3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 (using position mode)
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9"); 
            
            t_cpu.writeInput(2000); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 10";
            if (t_cpu.readOutPut() == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 11 */ 
        {
            /* 
            Here are some jump tests that take an input, then output 0 if the input was zero or 1 if the input was non-zero:
            3,3,1105,-1,9,1101,0,0,12,4,12,99,1 (using immediate mode)
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1105,-1,9,1101,0,0,12,4,12,99,1"); 
            
            t_cpu.writeInput(0); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 11";
            if (t_cpu.readOutPut() == 0) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 12 */ 
        {
            /* 
            Here are some jump tests that take an input, then output 0 if the input was zero or 1 if the input was non-zero:
            3,3,1105,-1,9,1101,0,0,12,4,12,99,1 (using immediate mode)
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,3,1105,-1,9,1101,0,0,12,4,12,99,1"); 
            
            t_cpu.writeInput(2000); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 12";
            if (t_cpu.readOutPut() == 1) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 13 */ 
        {
            /* 
            3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
            The above example program uses an input instruction to ask for a single number. The program will then output 999 if the input value is below 8, output 1000 if the input value is equal to 8, or output 1001 if the input value is greater than 8.
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"); 
            
            t_cpu.writeInput(7); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 13";
            if (t_cpu.readOutPut() == 999) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 14 */ 
        {
            /* 
            3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
            The above example program uses an input instruction to ask for a single number. The program will then output 999 if the input value is below 8, output 1000 if the input value is equal to 8, or output 1001 if the input value is greater than 8.
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"); 
            
            t_cpu.writeInput(8); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 14";
            if (t_cpu.readOutPut() == 1000) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five - part two unit tests 15 */ 
        {
            /* 
            3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
            The above example program uses an input instruction to ask for a single number. The program will then output 999 if the input value is below 8, output 1000 if the input value is equal to 8, or output 1001 if the input value is greater than 8.
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"); 
            
            
            t_cpu.writeInput(9); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Part two unit tests 15";
            if (t_cpu.readOutPut() == 1001) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }

        /* Day five unit test 2 */ 
        {
            std::fstream input_file; 
            input_file.open("../int_code_test_files/day5_input.txt");     
            std::string line; 
            getline( input_file, line );
            

            t_cpu.reset_cpu();
            t_cpu.loadProgram(line); 
            
            t_cpu.writeInput(5); 
            while (t_cpu.state != cpu_state::halted)
                t_cpu.iterate();

            std::cout << "Day five unit test 2\n";
            if (t_cpu.readOutPut()  == 15586959) 
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n"; 
        }

        /* Day nine test 1 */ 

        {
            /* 
            109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 takes no input and produces a copy of itself as output.
            */ 
            t_cpu.reset_cpu();
            t_cpu.loadProgram("109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99"); 

            // logging = true; 
            while (t_cpu.state != cpu_state::halted) {
                t_cpu.iterate();
            }
            logging = false;

            std::cout << "Day nine test 1";
            if ((t_cpu.readOutPut() == 109) &&
                (t_cpu.readOutPut() == 1) &&
                (t_cpu.readOutPut() == 204) &&
                (t_cpu.readOutPut() == -1) &&
                (t_cpu.readOutPut() == 1001) &&
                (t_cpu.readOutPut() == 100) &&
                (t_cpu.readOutPut() == 1) &&
                (t_cpu.readOutPut() == 100) &&                
                (t_cpu.readOutPut() == 1008) &&
                (t_cpu.readOutPut() == 100) &&
                (t_cpu.readOutPut() == 16) &&
                (t_cpu.readOutPut() == 101) &&
                (t_cpu.readOutPut() == 1006) &&
                (t_cpu.readOutPut() == 101) &&
                (t_cpu.readOutPut() == 0) &&
                (t_cpu.readOutPut() == 99))                                                                                                          
                std::cout << "\tPASSED\n"; 
            else 
                std::cout << "\tFAILED\n";
        }
    }
}

int main(int argc, char ** argv) {

    test_cpu();

    cpu robot_cpu; 
    std::fstream input_file; 
    std::vector<field> map;
    paddle_type paddle;
    ball_type ball;
    int max_x = 0; 
    int max_y = 0; 
    int score = 0; 
    int num_blocks = INT_MAX; 

    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }

    std::string line; 
    getline( input_file, line );
    robot_cpu.loadProgram(line);
    robot_cpu.memory.mem[0] = 2; 
    int iteration = 0;

    while (robot_cpu.state != cpu_state::halted && num_blocks != 0) {
        robot_cpu.iterate();
        iteration++; 

        if (robot_cpu.state == cpu_state::waiting_for_input) {
            while(robot_cpu.getOutPutQueueSize() > 0 && (robot_cpu.getOutPutQueueSize() % 3 == 0)) {
                field f {robot_cpu.readOutPut(),robot_cpu.readOutPut(), robot_cpu.readOutPut()}; 

                if (f.x == -1 && f.y == 0) 
                    score = f.color;
                else {
                    auto it = std::find_if(map.begin(), map.end(), [=](const field & cf) { return cf.x == f.x && cf.y == f.y;} );
                    if (it != map.end()) {
                        it->color = f.color;
                    } else {
                        map.push_back(f);
                    }
                    if (f.x > max_x) max_x = f.x;
                    if (f.y > max_y) max_y = f.y; 
                } 
            }

            for (int i = 0; i <= max_y; i++) {
                for (int j = 0; j <= max_x; j++) {
                    auto it = std::find_if(map.begin(), map.end(), [=](const field &f) {return f.x == j && f.y == i;} );
                    if (it != map.end()) {
                        switch (it->color) {
                            case 0: break; //  std::cout << " "; break; 
                            case 1: break; // std::cout << "#"; break; 
                            case 2: break; // std::cout << "+"; break; 
                            case 3: // std::cout << "-"; 
                                    paddle.x = it->x; 
                                    paddle.y = it->y;
                                    break; 
                            case 4: // std::cout << "o"; 
                                    if (ball.x != -1) {
                                        ball.x_dir = it->x - ball.x; 
                                        ball.y_dir = it->y - ball.y; 
                                    }
                                    ball.x = it->x; 
                                    ball.y = it->y;
                                    break; 
                            default: 
                                break;
                        }
                    } else {
                        // std::cout << " ";
                    }
                }
                // std::cout << std::endl;
            }
            num_blocks = std::count_if(map.begin(), map.end(), [=](const field &f) {return f.color == 2;});
            std::cout << "Number of blocks is: " << num_blocks << std::endl;
            std::cout << "The score is: " << score<<  std::endl; 

            /* We know where the ball is and where the paddle is */ 

            // if (ball.x_dir > 0 ) { // its going right

            const int minIterationsToHitThePaddle = paddle.y - ball.y;
            const int paddleBallDistance = abs(paddle.x - ball.x);  

            if (paddle.x < ball.x) { // it is right from us 
                robot_cpu.writeInput(1);
            } else if (paddle.x > ball.x) { // it is left from us
                robot_cpu.writeInput(-1); 
            } else { // its above us - we have to go the same direction the ball does
                robot_cpu.writeInput(0);
            }

            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            // } else { // its going left
            // }

            // int dir; 
            // std::cin >> dir;
            // std::cout << std::endl; 
            // robot_cpu.writeInput(dir);
        } 
    }

    while(robot_cpu.getOutPutQueueSize() > 0 && (robot_cpu.getOutPutQueueSize() % 3 == 0)) {
                field f {robot_cpu.readOutPut(),robot_cpu.readOutPut(), robot_cpu.readOutPut()}; 

                if (f.x == -1 && f.y == 0) 
                    score = f.color;
                else {
                    auto it = std::find_if(map.begin(), map.end(), [=](const field & cf) { return cf.x == f.x && cf.y == f.y;} );
                    if (it != map.end()) {
                        it->color = f.color;
                    } else {
                        map.push_back(f);
                    }
                    if (f.x > max_x) max_x = f.x;
                    if (f.y > max_y) max_y = f.y; 
                } 
    }

    std::cout << "The score is: " << score<<  std::endl; 
    std::cout << robot_cpu.getOutPutQueueSize() << std::endl;


    std::cout << max_x << " " << max_y << std::endl << std::endl << std::endl;

    return 0; 
}