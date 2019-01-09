#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stdio.h>
#include <ctype.h> 
#include <boost/regex.hpp>

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day12.txt");


    std::cout << "Rules: " << std::endl; 
    for( std::string line; getline( input_file, line ); ) {
        std::cout << line << std::endl;     
    }

    std::cout << "This is it\n"; 
}