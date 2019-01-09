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
    // if (RectA.Left < RectB.Right && RectA.Right > RectB.Left && RectA.Top > RectB.Bottom && RectA.Bottom < RectB.Top ) 
    return (r1.top > r2.bottom) && (r1.bottom < r2.top) && (r1.left < r2.right) && (r1.right > r2.left); 
}

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day4.txt"); 
    std::vector<box> boxes; 
    std::vector<int> overlaped; 

    for( std::string line; getline( input_file, line ); )
    {
        // pelda: #1318 @ 595,225: 25bottom8
        int id, left, top, height, width;
        
        if (5 == std::sscanf(line.c_str(), "#%d @ %d,%d: %dx%d ", &id, &left, &top, &width, &height )) {
            box b; 
            b.top = top + height; 
            b.left = left; 
            b.bottom = top; 
            b.right = left + width; 
            boxes.push_back(b); 
        }
    }
    
    bool * intersected = new bool[boxes.size()]; 

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            if (intersect(boxes[i], boxes[j])) {
                std::cout << i << " " << j << std::endl; 
                intersected[i] = true; 
                intersected[j] = true; 
            }
        }
    }

    for (int i = 0; i < boxes.size(); i++)
        if (intersected[i] == false)
            std::cout << i << std::endl; 
    
    return 0; 
}