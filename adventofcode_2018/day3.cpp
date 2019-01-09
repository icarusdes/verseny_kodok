#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstdio>

struct box {
    int left = 0; 
    int top = 0; 
    int right = 0; 
    int bottom = 0; 
}; 

bool intersect(const box & r1, const box & r2) {
    return !(r2.left > r1.right
    || r2.right < r1.left
    || r2.top < r1.bottom
    || r2.bottom > r1.top);
}

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day3.txt"); 

    int * fabric = new int [1500 * 1500]; 
    for (int i = 0; i < 1500; i++) 
        for (int j = 0; j < 1500; j++)
            fabric[i * 1500 + j] = 0;

    std::vector<box> boxes; 

    for( std::string line; getline( input_file, line ); )
    {
        // pelda: #1318 @ 595,225: 25bottom8
        int id, left, top, height, width;
        
        if (5 == std::sscanf(line.c_str(), "#%d @ %d,%d: %dx%d ", &id, &left, &top, &width, &height )) {
            for (int i = left; i < left + width; i++)
                for (int j = top; j < top + height; j++)
                    fabric[i * 1500 + j]++; 
            box b; 
            b.top = top; 
            b.left = left; 
            b.bottom = top + height - 1; 
            b.right = left + width - 1; 
            boxes.push_back(b); 
        }
    }
    
    int sum = 0; 

    for (int i = 0; i <1500; i++) 
        for (int j = 0; j < 1500; j++)
            if (fabric[i * 1500 + j] > 1)
                sum++; 

    std::cout << sum << std::endl;
    std::cout << "This compiles and runs!" << std::endl; 
    return 0; 
}