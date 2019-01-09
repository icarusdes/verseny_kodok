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
        bool dbl = false; 
        bool tpl = false; 
        std::vector<char> chars; 
        for (auto c : line) {
            std::cout << c << std::endl; 
            if (chars.end() == std::find(chars.begin(), chars.end(), c)) {
                int count = std::count(line.begin(), line.end(), c); 
                if (count == 2) {
                    chars.push_back(c); 
                    dbl = true; 
                } else if (count == 3 ) {
                    chars.push_back(c); 
                    tpl = true; 
                }
            }
        }
        if (dbl) double_chars++; 
        if (tpl) triple_chars++; 
    }
    std::cout << "Double " << double_chars << " tripple " << triple_chars << std::endl; 
    std::cout << double_chars * triple_chars << std::endl;
    std::cout << "This compiles and runs!" << std::endl; 
    return 0; 
}