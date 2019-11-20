#include <iostream>
#include <boost/regex.hpp>
#include <fstream>
#include <string> 
#include <map>

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int main() {
    boost::regex matchRegisters("([a-zA-Z]+) ([a-zA-Z0-9]+) ([a-zA-Z]+).*"); 
    boost::regex matchNumbers("([a-zA-Z]+) ([a-zA-Z0-9]+) ([-+0-9]+).*"); 
    boost::smatch matches; 
    std::vector<std::string> commands;
    std::fstream input("input1.txt"); 
    std::string line; 
    int currentCommand = 0; 
    int sFrequency = 0; 
    int mulNum = 0; 
    std::map<std::string, long long int> registers; 
    // registers["a"] = 1;

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
        }

        std::cout << line << std::endl;

        if (cmd == "set") { 
            registers[registerOneName] = registerTwoValue; 
            std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
            if (registerOneName == "f") {
                std::cout << registers["b"] << std::endl; 
            }
        } else if (cmd == "sub") {
            registers[registerOneName] = registers[registerOneName] - registerTwoValue; 
            // std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
        } else if (cmd == "mul") {
            registers[registerOneName] = registers[registerOneName] * registerTwoValue; 
            // std::cout << "Value of " << registerOneName << " is " << registers[registerOneName] << std::endl;
            mulNum++; 
        } else if (cmd == "jnz") {
            if (is_digits(registerOneName)) {
                if (stoi(registerOneName) != 0) {
                    currentCommand += registerTwoValue - 1 ;
                }
            } else if (registers[registerOneName] != 0) {
                currentCommand += registerTwoValue - 1 ;
            }
        } else {
            std::cout << "Command not covered yet: " << cmd << std::endl; 
            exit(0); 
        }
        currentCommand++; 
    }
    std::cout << "Number of multiplications: " << mulNum << std::endl; 
    std::cout << "Value of register h is " << registers["h"] << std::endl;

    return 0; 
}