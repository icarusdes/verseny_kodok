#include <iostream>
#include <fstream>
#include <sstream>  

int main(int argc, char ** argv) {
    std::fstream input_file; 

    if (argc > 1) {
        input_file.open(argv[2]); 
    } else {
        input_file.open("input.txt"); 
    }

    std::string line;
    getline( input_file, line );
    std::stringstream ss(line);

    int level = 0; 
    int entering_basement_count = 1; 

    for (char c; ss >> c; ) {
        if (c == '(')
            level++;
        if (c == ')')
            level--;
        if (level == -1)
            std::cout << "At basement level -1 at step: " << entering_basement_count << std::endl;
        entering_basement_count++;  
    }

    std::cout << "Current level is: " << level << std::endl;

    return 0;
}