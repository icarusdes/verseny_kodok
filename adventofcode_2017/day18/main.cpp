#include <iostream>
#include <boost/regex.hpp>
#include <fstream>
#include <string> 
#include <map>

int main() {
    boost::regex matchRegisters("([a-zA-Z]+) ([a-zA-Z0-9]+) ([a-zA-Z]+).*"); 
    boost::regex matchNumbers("([a-zA-Z]+) ([a-zA-Z0-9]+) ([-+0-9]+).*"); 
    boost::regex matchShorter("([a-zA-Z]+) ([a-zA-Z0-9]+).*"); 
    boost::smatch matches; 
    std::vector<std::string> commands;
    std::fstream input("input_2.txt"); 
    std::string line; 
    int currentCommand = 0; 
    int sFrequency = 0; 
    std::map<std::string, long long int> registers; 

    while (std::getline(input,line)) {
        commands.push_back(line); 
    }

    while (true && currentCommand < commands.size()) {  
        line = commands[currentCommand]; 
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

        std::cout << line << std::endl;

        if (cmd == "set") { 
            registers[registerOneName] = registerTwoValue; 
            std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "add") {
            registers[registerOneName] = registers[registerOneName] + registerTwoValue; 
            std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "mul") {
            registers[registerOneName] = registers[registerOneName] * registerTwoValue; 
            std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "mod") {
            registers[registerOneName] = registers[registerOneName] % registerTwoValue; 
            std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "snd") {
            sFrequency = registers[registerOneName]; 
            std::cout << "Value of sFrequency is " << registers[registerOneName] << std::endl;
        } else if (cmd == "rcv") {
            if (registers[registerOneName] != 0) {
                std::cout << sFrequency << std::endl; 
                exit(0); 
            }
        } else if (cmd == "jgz") {
            if (registers[registerOneName] > 0) {
                currentCommand += registerTwoValue - 1 ;
            }
        } else {
            std::cout << "Command not covered yet: " << cmd << std::endl; 
            exit(0); 
        }
        currentCommand++; 
    }
    
    std::cout << matches[1] << " " << matches[2] << " " << matches[3] << std::endl;

    return 0; 
}