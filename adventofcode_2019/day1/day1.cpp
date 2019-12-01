#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input.txt"); 
    int sum = 0;

    for( std::string line; getline( input_file, line ); )
    {
        int number = std::stoi(line) / 3 - 2;
        sum += number; 
        std::cout << number << std::endl; 
    }

    std::cout << "The sum is: " << sum << std::endl; 
    return 0; 
}