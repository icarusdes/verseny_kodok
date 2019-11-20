#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

std::map<std::string, int> registers;

int getRegisterValue(const std::string & registerName) { 
    auto position = registers.find(registerName); 
    if (registers.end() == position) {
        return 0; 
    } else {
        return registers[registerName];
    }
}

int main() {
    boost::regex regexWithChilds("([a-zA-Z]+) (inc|dec) (-*[0-9]+) if ([a-zA-Z]+) ([!=<>]+) (-*[0-9]+).*");
    std::fstream input("input.txt"); 
    std::string line; 
    boost::smatch match;
    int largest_value_ever = INT_MIN; 

    while (std::getline(input, line)) {
        if (boost::regex_match(line, match, regexWithChilds))
        {        
            // std::cout << "Matched line: " << line << std::endl;
            std::string registerOneName = match[1]; 
            bool inc = (match[2] == "inc"); 
            int diff = stoi(match[3]); 
            std::string registerTwoName = match[4]; 
            std::string condition = match[5]; 
            int conditionValue = stoi(match[6]); 
            bool conditionTrue = false;

            if (condition == "==") {
                if (getRegisterValue(registerTwoName) == conditionValue) {
                    conditionTrue = true;
                }
            } else if (condition == "<") {
                if (getRegisterValue(registerTwoName) < conditionValue) {
                    conditionTrue = true;
                }
            } else if (condition == "!=") { 
                if (getRegisterValue(registerTwoName) != conditionValue) {
                    conditionTrue = true;
                }
            } else if (condition == ">") { 
                if (getRegisterValue(registerTwoName) > conditionValue) {
                    conditionTrue = true;
                }
            } else if (condition == "<=") { 
                if (getRegisterValue(registerTwoName) <= conditionValue) {
                    conditionTrue = true;
                }
            } else if (condition == ">=") { 
                if (getRegisterValue(registerTwoName) >= conditionValue) {
                    conditionTrue = true;
                }
            } else {
                std::cout << "Matched line: " << line << std::endl;
                std::cout << "Unhandled condition: " << condition << std::endl; 
            }

            if (conditionTrue) {
                if (inc) {
                    registers[registerOneName] = getRegisterValue(registerOneName) + diff; 
                } else {
                    registers[registerOneName] = getRegisterValue(registerOneName) - diff; 
                }
                for_each(registers.begin(), registers.end(), [&] (auto & value) { if (value.second > largest_value_ever) largest_value_ever = value.second; }); 
            }

        } else {
            std::cout << "This sucks: " << line <<  std::endl; 
        }
    }

    int largest_value = INT_MIN; 
    for_each(registers.begin(), registers.end(), [&] (auto & value) { if (value.second > largest_value) largest_value = value.second; }); 

    std::cout << "Largest value is: " << largest_value << std::endl;
    std::cout << "Largest value ever was: " << largest_value_ever << std::endl;
    return 0; 
}