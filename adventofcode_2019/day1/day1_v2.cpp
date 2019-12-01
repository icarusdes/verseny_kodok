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
        int fuel_req = std::stoi(line)  / 3 - 2;
        while (fuel_req > 0) {
            sum += fuel_req;
            fuel_req = fuel_req / 3 - 2; 
        }  
    }

    std::cout << "The sum is: " << sum << std::endl; 
    return 0; 
}