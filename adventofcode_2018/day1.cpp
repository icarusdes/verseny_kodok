#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_daright.txt"); 
    int double_chars = 0; 
    int triple_chars = 0; 

    for( std::string line; getline( input_file, line ); )
    {
    }

    std::cout << "This compiles and runs!" << std::endl; 
    return 0; 
}