#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <deque>
#include <sstream>

bool logging = false; 

struct field {
    int x = {0}; 
    int y = {0};
    int color = {0}; 
}; 

struct cpu {
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

    long long int currentopt = 0;
    std::deque<long long int> inputs; 
    std::deque<long long int> outputs; 

    bool iterate() {
        long long int command = memory(currentopt, 1);
        if ((command % 100) != 99) {               
            int numparams = 1;
            bool jumped = false; 
            long long int & out = memory(currentopt+3, (command / 10000));       
            long long int & op2 = memory(currentopt+2, ((command % 10000) / 1000));            
            long long int & op1 = memory(currentopt+1, ((command % 1000) / 100));
            if (logging) {
                std::cout << "Command: " << command << std::endl;
                std::cout << "Out: " <<  out << std::endl;  
                std::cout << "Op2: " << op2 << std::endl;              
                std::cout << "Op1: " << op1 << std::endl;
            }
            
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
                op1 = inputs.front();
                inputs.pop_front(); 
                numparams = 1; 
            } else if (opcode == 4) {
                outputs.push_back(op1); 
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

            return false; 
        }
        return true;
    }

}; 

enum class direction {
    UP, 
    RIGHT, 
    DOWN, 
    LEFT,
    Count
};


int main(int argc, char ** argv) {

    cpu robot_cpu; 

    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
    if (argc >= 3)
        logging = true; 
        
    /* parancsok beolvasása a CPU-ba */ 
    
    std::string line; 
    getline( input_file, line );    
    std::stringstream ss(line);

    for (long long int i; ss >> i;) {
        robot_cpu.memory.mem.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }

    std::vector<field> map; 

    bool ended = false; 
    bool step_generated = false; 
    bool output_generated = false;
    int cur_x = 0; 
    int cur_y = 0;     
    direction cur_dir = direction::UP; 
    
    while (!ended) {
        if(!step_generated) {
            auto it = std::find_if(map.begin(), map.end(), [=](const field & f) { return f.x == cur_x && f.y == cur_y; });
            if (it != map.end())
                robot_cpu.inputs.push_back(it->color);
            else 
                robot_cpu.inputs.push_back(0); // mert ahol nem jartunk, az tuti fekete
            step_generated = true; 
        }
        ended = robot_cpu.iterate(); 
        if (robot_cpu.outputs.size() == 2) {

            // szinezés
            auto it = std::find_if(map.begin(), map.end(), [=](const field & f) { return f.x == cur_x && f.y == cur_y; });
            if (it != map.end()) {
                it->color = robot_cpu.outputs.front();                
            } else {
                field f {cur_x, cur_y, robot_cpu.outputs.front()}; 
                map.push_back(f); 
            }
            robot_cpu.outputs.pop_front(); 
            
            // léptetés
            bool turn_right = robot_cpu.outputs.front(); 
            robot_cpu.outputs.pop_front(); 

            if (turn_right) {
                cur_dir = static_cast<direction>((static_cast<int>(cur_dir) + 1) % static_cast<int>(direction::Count));
            } else {
                cur_dir = static_cast<direction>((static_cast<int>(cur_dir) -1 + static_cast<int>(direction::Count)) % static_cast<int>(direction::Count));
            }

            switch (cur_dir)
            {
            case direction::UP:
                cur_y++; 
                break;
            case direction::RIGHT:
                cur_x++; 
                break;
            case direction::DOWN:
                cur_y--; 
                break;
            case direction::LEFT:
                cur_x--; 
                break;
            default:
                std::cout << "Itt valami nagy gebasz van" << std::endl; 
                break;
            }

            std::cout << cur_x << " " << cur_y << std::endl; 
            step_generated = false; 
        }
    }

    std::cout << map.size() << std::endl;

    auto numfeher = std::count_if(map.begin(), map.end(), [](const field & f) { return f.color == 1; } );
    // 0 ballra fordulás, 1 jobbra fordulás

    std::cout << numfeher << std::endl;
    return 0; 
}