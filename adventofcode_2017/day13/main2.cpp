#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Layer {
    uint depth;
    uint range; 
};

int main() {
    std::fstream input("input.txt"); 
    std::string line; 
    uint depth; 
    uint range; 
    uint delay = 0; 
    int pos = -1; 
    int lastlayer = 0; 
    char temp;
    bool caught = true; 
    std::vector<Layer> layers;  

    while (std::getline(input, line)) {
        std::stringstream ss(line); 
        ss >> depth >> temp >> range; 
        Layer tempLayer; 
        tempLayer.depth = depth; 
        tempLayer.range = range;
        layers.push_back(tempLayer);
        if (depth > lastlayer)
            lastlayer = depth; 
    }

    while (caught) {
        caught = false;
        for (Layer & currentLayer : layers) {
            if ((currentLayer.depth + delay) % (currentLayer.range * 2 - 2) == 0) {
                caught = true; 
                break; 
            }
        }

        if (caught) {
            delay++; 
        }
    }
    std::cout << "Number of delays is " << delay<< std::endl; 
}