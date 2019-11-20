
#include <iostream>
#include <algorithm>

int main() {

    static constexpr int LISTSIZE = 256;
    std::vector<int> lengths = {31,2,85,1,80,109,35,63,98,255,0,13,105,254,128,33 }; 
    /* static constexpr int LISTSIZE = 5;
    std::vector<int> lengths = {3, 4, 1, 5}; */ 
    std::vector<int> list(LISTSIZE); 
    std::iota(list.begin(), list.end(), 0); 
    uint currentPos = 0; 
    uint skipSize = 0; 
    
    for ( int currentLenght : lengths) {

        // std::cout << "Current lenght: " << currentLenght <<  std::endl; 
        uint start = currentPos; 
        uint end = (currentPos + currentLenght) % LISTSIZE; 

        /*         
        for (int i = 0; i < LISTSIZE; i++) {
            if (start == i && currentLenght != 0)
                std::cout << "("; 
            if (currentPos == i) 
                std::cout << "["; 
            std::cout << list[i]; 
            if (currentPos == i) 
                std::cout << "]";
            if (end -1 == i && currentLenght != 0) 
                std::cout << ")";
            std::cout << " "; 
        }
        std::cout << std::endl; 
        */ 
        
        if (currentLenght != 0) 
            if (end <= start) {                 
                std::vector<int> toReverse; 
                std::copy(list.begin() + start, list.end(), std::back_inserter(toReverse)); 
                std::copy(list.begin(), list.begin() + end, std::back_inserter(toReverse)); 
                std::reverse(toReverse.begin(), toReverse.end()); 

                std::vector<int> newList;

                std::copy(toReverse.begin() + (LISTSIZE - start), toReverse.end(), std::back_inserter(newList)); 
                std::copy(list.begin() + end, list.begin() + start, std::back_inserter(newList)); 
                std::copy(toReverse.begin(), toReverse.begin() + (LISTSIZE - start), std::back_inserter(newList)); 
                list = std::move(newList); 
            } else {
                std::reverse(list.begin()+ start, list.begin() + end); 
            }

        /* for (int i = 0; i < LISTSIZE; i++) {
            if (start == i && currentLenght != 0)
                std::cout << "("; 
            if (currentPos == i) 
                std::cout << "["; 
            std::cout << list[i]; 
            if (currentPos == i) 
                std::cout << "]";
            if (end -1 == i && currentLenght != 0) 
                std::cout << ")";
            std::cout << " "; 
        } 
        std::cout << std::endl; 
        */ 

        currentPos = (currentPos + currentLenght + skipSize) % LISTSIZE;
        skipSize++; 
        // std::cout << "Current position " << currentPos << ". Skip size: " << skipSize << std::endl; 
    }    
    /* 
    for (int i = 0; i < LISTSIZE; i++) {
        if (currentPos == i) 
            std::cout << "["; 
        std::cout << list[i]; 
        if (currentPos == i) 
            std::cout << "]";
        std::cout << " "; 
    }
    std::cout << std::endl; 
    std::cout << std::endl << std::endl; */ 
    std::cout << "Result: " <<  list[0] * list[1] << std::endl;
}