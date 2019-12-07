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
    // for (int i = 112233; i <= 112233; i++) {

        std::string s = std::to_string(i);
        char const *buffer = s.c_str(); 

        std::vector<int> azonos_kezdok; 

        bool megfelel = true;
        bool van_azonos = false;
        for (int j = 0; j < 5; j++) {
            if (buffer[j] > buffer[j+1])
                megfelel = false; 
            if (buffer[j] == buffer[j+1])
                azonos_kezdok.push_back(j);         
        }

        for (int j = 0; j < 4; j++) {
            if ((buffer[j] == buffer[j+1]) && (buffer[j+1] == buffer[j+2]))
                for (auto it = azonos_kezdok.begin(); it != azonos_kezdok.end(); it++) {
                    if ((*it == j)) {                        
                        azonos_kezdok.erase(it + 1);
                        azonos_kezdok.erase(it);
                        break; 
                    }
                    if ((*it == j+1)) {         
                        azonos_kezdok.erase(it);
                        break; 
                    }    
                }
        }

        if (megfelel && azonos_kezdok.size()) {
            counter++;
        }
    }

    std::cout << counter << std::endl; 

    return 0; 
}