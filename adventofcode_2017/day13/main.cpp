#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Layer {
    uint depth;
    uint range; 
    bool down = true; 
    uint currentPos = 0; 
};

int main() {
    std::fstream input("input.txt"); 
    std::string line; 
    uint depth; 
    uint range; 
    int pos = -1; 
    int lastlayer = 0; 
    uint severity = 0; 
    uint delay = 0; 
    char temp;
    bool caught = true; 
    std::vector<Layer> layers;  

    while (std::getline(input, line)) {
        std::stringstream ss(line); 
        ss >> depth >> temp >> range; 
        std::cout << depth << " " << range << std::endl;
        Layer tempLayer; 
        tempLayer.depth = depth; 
        tempLayer.range = range;
        layers.push_back(tempLayer);
        if (depth > lastlayer)
            lastlayer = depth; 
    }

    while (caught) {
        caught = false;
        int tempDelay = delay; 
        int caughtAt = -1; 
        while (pos <= lastlayer && !caught) {
            for (Layer & currentLayer : layers) {

                if ((currentLayer.depth + delay) % (currentLayer.range * 2 - 2) == 0) {
                    caught = true; 
                    break; 
                }
                /* 
                if (currentLayer.depth == pos && currentLayer.currentPos == 0) {
                    severity += currentLayer.depth * currentLayer.range; 
                    caught = true; 
                    caughtAt = pos;
                    break; 
                    // for (j = 0; j < )
                }
                if (currentLayer.down) {
                    if (currentLayer.currentPos + 1 == currentLayer.range) {
                        currentLayer.down = false; 
                        currentLayer.currentPos--; 
                    } else {
                        currentLayer.currentPos++; 
                    }
                } else {
                    if (currentLayer.currentPos == 0 ) {
                        currentLayer.down = true; 
                        currentLayer.currentPos++; 
                    } else {
                        currentLayer.currentPos--; 
                    }
                } */ 
            }
            if (tempDelay)
                tempDelay--;  
            else
                pos++;
        }
        if (caught) {
            pos = -1; 
            delay++; 
            severity = 0; 
            // std::cout << "Caught at: " << caughtAt << std::endl; 
            std::cout << "Current delay is: " << delay << std::endl; 
            for (Layer & currentLayer: layers) {
                currentLayer.currentPos = 0; 
                currentLayer.down = true; 
            }
        }
    }
    std::cout << "Severity is " << severity << std::endl; 
    std::cout << "Number of steps is " << delay + 1<< std::endl; 
}