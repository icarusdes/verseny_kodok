#include <iostream>
#include <fstream> 
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

struct p_state {
    int first; 
    bool second;
    int ip; 
};

p_state compute(std::vector<int> & program, std::deque<int> & inputs, int last_output = -1, int current_opt = -1) {
    int currentopt = (current_opt != -1) ? current_opt : 0; 
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
            if (!inputs.size()) {
                std::cout << "Please provide an input than hit enter: "; 
                std::cin >> op1;
            } else {
                op1 = inputs.front();
                inputs.pop_front();  
            }
            numparams = 1; 
        } else if (opcode == 4) {
            return {op1, false, (currentopt + numparams + 1 ) % program.size() };
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
    return {last_output, true, currentopt}; 
}

void print_deque(std::deque<int> & deq) {
    for (auto d : deq) {
        std::cout << d << " ";
    }
    std::cout << std::endl; 
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

    std::vector<int> phases = {5,6,7,8,9};
    std::sort (phases.begin(),phases.end());
    do {
        std::vector<int> amp1_commands = commands;
        std::vector<int> amp2_commands = commands;
        std::vector<int> amp3_commands = commands;
        std::vector<int> amp4_commands = commands;
        std::vector<int> amp5_commands = commands;

        std::deque<int> amp1_inputs = {phases[0], 0};
        std::deque<int> amp2_inputs = {phases[1]};
        std::deque<int> amp3_inputs = {phases[2]};
        std::deque<int> amp4_inputs = {phases[3]};
        std::deque<int> amp5_inputs = {phases[4]};

        p_state result1 = {-1, false, 0};
        p_state result2 = {-1, false, 0};
        p_state result3 = {-1, false, 0};
        p_state result4 = {-1, false, 0};
        p_state result5 = {-1, false, 0};
        int it = 0;  
        while (result5.second != true) {  
            std::cout << "\t\t" << it++ << std::endl;
            print_deque(amp1_inputs);
            result1 = compute(amp1_commands, amp1_inputs, result1.first, result1.ip);
            amp2_inputs.push_back(result1.first);
            print_deque(amp2_inputs);
            result2 = compute(amp2_commands, amp2_inputs, result2.first, result2.ip);
            amp3_inputs.push_back(result2.first);
            print_deque(amp3_inputs);
            result3 = compute(amp3_commands, amp3_inputs, result3.first, result3.ip);
            amp4_inputs.push_back(result3.first);
            print_deque(amp4_inputs);
            result4 = compute(amp4_commands, amp4_inputs, result4.first, result4.ip);
            amp5_inputs.push_back(result4.first);
            print_deque(amp5_inputs);
            result5 = compute(amp5_commands, amp5_inputs, result5.first, result5.ip);
            amp1_inputs.push_back(result5.first);
        }
        if (result5.first > max_output) {
            max_output = result5.first;
            max_output_provider = phases;
        }
        std::cout << "Current output: " << result5.first << " current phases "; 
        for (auto i :  phases)
            std::cout << i << " "; 
        std::cout << std::endl;
    } while ( std::next_permutation(phases.begin(),phases.end()) );

    std::cout << "Highest output is: " << max_output << std::endl;

    return 0; 
}