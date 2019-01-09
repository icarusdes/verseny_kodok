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
    std::cout << std::endl; 

    input_file.open("input_day15.txt");

    // position=< 9,  1> velocity=< 0,  2> 
    boost::regex expr{"position=<\\s*(\\-?\\d+),\\s*(\\-?\\d+)> velocity=<\\s*(\\-?\\d+),\\s*(\\-?\\d+)>"}; 
    for( std::string line; getline( input_file, line ); ) {
        
    }
    return 0; 
}