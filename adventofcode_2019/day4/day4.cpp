#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

    int counter = 0;

    for (int i = 147981; i <= 691423; i++) {
    // for (int i = 111111; i <= 111111; i++) {
        std::string s = std::to_string(i);
        char const *buffer = s.c_str(); 
        // std::cout << buffer << std::endl; 

        std::vector<int> azonos_kezdok; 

        bool megfelel = true;
        bool van_azonos = false;
        for (int j = 0; j < 5; j++) {
            if (buffer[j] > buffer[j+1])
                megfelel = false; 
            if (buffer[j] == buffer[j+1])
                azonos_kezdok.push_back(j); 
        }
    //    std::cout << megfelel << " " << van_azonos << std::endl;
        if (megfelel && azonos_kezdok.size()) {
            counter++;
        }
    }

    std::cout << counter << std::endl; 

    return 0; 
}