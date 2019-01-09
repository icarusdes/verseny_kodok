#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_daright.txt"); 
    std::vector<std::string> lines; 

    for( std::string line; getline( input_file, line ); )
    {
        lines.push_back(line); 
    }
    std::sort(lines.begin(), lines.end()); 
    for (int i = 0; i < lines.size() -1; i++) {
        auto line1 = lines[i]; 
        auto line2 = lines[i+1];
        auto it1 = line1.begin(); 
        auto it2 = line2.begin(); 
        int diff = 0; 
        while (it1 != line1.end()) {
            if (*it1 != *it2)
                diff++; 
            it1++; 
            it2++; 
        }
        if (diff == 1) {
            std::cout << line1 << std::endl;
            std::cout << line2 << std::endl;
        }
    }
    std::cout << "This compiles and runs!" << std::endl; 
    return 0; 
}