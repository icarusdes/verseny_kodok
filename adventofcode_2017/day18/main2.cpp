#include <iostream>
#include <boost/regex.hpp>
#include <fstream>
#include <string> 
#include <map>
#include <locale>  

// #define DEBUG 1

struct Machine {
    int instructioPointer = 0; 
    std::map<std::string, long long int> registerMap; 
    std::deque<long long int> outChannel; 
    std::deque<long long int> * inChannel; 
    bool isBlocked = false;
}; 

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int main() {
    boost::regex matchRegisters("([a-zA-Z]+) ([a-zA-Z0-9]+) ([a-zA-Z]+).*"); 
    boost::regex matchNumbers("([a-zA-Z]+) ([a-zA-Z0-9]+) ([-+0-9]+).*"); 
    boost::regex matchShorter("([a-zA-Z]+) ([a-zA-Z0-9]+).*"); 
    boost::smatch matches; 
    std::vector<std::string> commands;
    std::fstream input("input_2.txt"); 
    std::string line; 
    Machine machines[2]; 
    machines[0].inChannel = & machines[1].outChannel; 
    machines[1].inChannel = & machines[0].outChannel; 
    machines[0].registerMap["p"] = 0;
    machines[1].registerMap["p"] = 1;
    uint currentMachine = 0;
    uint sentByFirst = 0; 

    std::vector<long long int> sValues[2];
    
    while (std::getline(input,line)) {
        commands.push_back(line); 
    }

    int * currentCommand = & machines[currentMachine].instructioPointer;

    while ( *currentCommand < commands.size()) { 

        
        auto & registers = machines[currentMachine].registerMap; 
        auto & inChannel = machines[currentMachine].inChannel; 
        auto & outChannel = machines[currentMachine].outChannel;


        line = commands[*currentCommand]; 
        std::string cmd; 
        std::string registerOneName; 
        int registerTwoValue; 
        if (boost::regex_match(line, matches, matchRegisters) ) {
            cmd = matches[1]; 
            registerOneName = matches[2]; 
            registerTwoValue = registers[std::string(matches[3])]; 
        } else if (boost::regex_match(line, matches, matchNumbers) ) { 
            cmd = matches[1];
            registerOneName = matches[2]; 
            registerTwoValue = stoi(matches[3]); 
        } else if (boost::regex_match(line, matches, matchShorter) ) { 
            cmd = matches[1];
            registerOneName = matches[2]; 
        }

#ifdef DEBUG
        std::cout << line << std::endl;
#endif

        if (cmd == "set") { 
            registers[registerOneName] = registerTwoValue; 
            std::cout << "Thread " << currentMachine << "\t" << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "add") {
            registers[registerOneName] = registers[registerOneName] + registerTwoValue; 
            std::cout << "Thread " << currentMachine << "\t" << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "mul") {
            registers[registerOneName] = registers[registerOneName] * registerTwoValue; 
            std::cout << "Thread " << currentMachine << "\t" << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "mod") {
            registers[registerOneName] = registers[registerOneName] % registerTwoValue; 
            std::cout << "Thread " << currentMachine << "\t" << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "snd") {
            
            if (is_digits(registerOneName)) {
                outChannel.push_back(stoi(registerOneName));
#ifdef DEBUG
                std::cout << "Thread " << currentMachine << "\t" << " Writen to channel:" << stoi(registerOneName) << std::endl;
#endif
            } else {
                outChannel.push_back(registers[registerOneName] ); 
#ifdef DEBUG
                std::cout << "Thread " << currentMachine << "\t" << " Writen to channel:" << registers[registerOneName] << std::endl;
#endif 
            }
#ifdef DEBUG
            std::cout << "Thread " << currentMachine << "New channel backlog size: " << outChannel.size() << std::endl;
#endif
            if (currentMachine) 
                sentByFirst++; 
            if (sentByFirst > 10000000)
                break;

        } else if (cmd == "rcv") {
            if (inChannel->size()) {
                registers[registerOneName] = inChannel->front(); 
#ifdef DEBUG
                std::cout << "Thread " << currentMachine << "\t" << "Read from channel: " << inChannel->front() << std::endl; 
#endif 
                inChannel->pop_front(); 
#ifdef DEBUG
                std::cout << "Thread " << currentMachine << "New channel backlog size: " << inChannel->size() << std::endl;
#endif
            } else {
                machines[currentMachine].isBlocked = true;
                std::cout << "Changing machine " << currentMachine << "->";
                if (currentMachine == 0)
                    currentMachine = 1; 
                else 
                    currentMachine = 0; 
                std::cout << currentMachine << std::endl; 

                (*currentCommand)--;
                if (machines[currentMachine].inChannel->size() == 0)
                    break; 
            }            
        } else if (cmd == "jgz") {
            bool jump = false;
            if (is_digits(registerOneName)) { 
                jump = stoi(registerOneName) > 0; 
            } else {
                jump = registers[registerOneName] > 0;  
            }
            if (jump) {
                (*currentCommand) += registerTwoValue - 1 ;
            }
        } else {
            std::cout << "Thread " << currentMachine << "\t" << "Command not covered yet: " << cmd << std::endl; 
            break;
        }        
        (*currentCommand)++; 
        currentCommand = &machines[currentMachine].instructioPointer;
    }
    
    std::cout << "Sent by the first machine " <<  sentByFirst << std::endl;

    return 0; 
}