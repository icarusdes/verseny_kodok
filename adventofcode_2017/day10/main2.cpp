
#include <iostream>
#include <sstream>
#include <algorithm>

static constexpr int LISTSIZE = 256;

void transformVector(std::vector<uint> & list, const std::vector<int> & lengths) {
    uint currentPos = 0; 
    uint skipSize = 0; 
    for (int i = 0; i < 64; i++) {
        for ( int currentLenght : lengths) {
            uint start = currentPos; 
            uint end = (currentPos + currentLenght) % LISTSIZE; 
            
            if (currentLenght != 0) 
                if (end <= start) {                 
                    std::vector<uint> toReverse; 
                    std::copy(list.begin() + start, list.end(), std::back_inserter(toReverse)); 
                    std::copy(list.begin(), list.begin() + end, std::back_inserter(toReverse)); 
                    std::reverse(toReverse.begin(), toReverse.end()); 

                    std::vector<uint> newList;

                    std::copy(toReverse.begin() + (LISTSIZE - start), toReverse.end(), std::back_inserter(newList)); 
                    std::copy(list.begin() + end, list.begin() + start, std::back_inserter(newList)); 
                    std::copy(toReverse.begin(), toReverse.begin() + (LISTSIZE - start), std::back_inserter(newList)); 
                    list = std::move(newList); 
                } else {
                    std::reverse(list.begin()+ start, list.begin() + end); 
                }

            currentPos = (currentPos + currentLenght + skipSize) % LISTSIZE;
            skipSize++; 
        }
    }
}

            
std::string createDenseHash(std::vector<uint> & list) {
    std::stringstream ss;
    for (int i = 0; i < 16; i++) {
        uint x = list[i * 16]; 
        for (int j = 1; j < 16; j++) {
            x = x ^ list[i * 16 + j]; 
        }
        ss << std::hex << ((x >> 4) & 0xF) << (x & 0xF);
    }
    return ss.str();
}

std::vector<int> lengthsFromString(const std::string & str ) {
    std::vector<int> temp; 
    for (int i = 0; i < str.size(); i++) {
        temp.push_back(str[i]); 
    }
    temp.push_back(17); 
    temp.push_back(31); 
    temp.push_back(73); 
    temp.push_back(47); 
    temp.push_back(23); 
    return temp; 
}

int main() {
    std::string hash = "31,2,85,1,80,109,35,63,98,255,0,13,105,254,128,33"; 
    /* static constexpr int LISTSIZE = 5;
    std::vector<int> lengths = {3, 4, 1, 5}; */ 
    // std::string hash = ""; 
    std::vector<uint> list(LISTSIZE); 
    std::iota(list.begin(), list.end(), 0); 
    
    std::vector<int> lengths = lengthsFromString(hash); 
    transformVector(list, lengths); 
    std::cout << createDenseHash(list) << std::endl; 

    std::cout << "Result: " <<  list[0] * list[1] << std::endl;
}