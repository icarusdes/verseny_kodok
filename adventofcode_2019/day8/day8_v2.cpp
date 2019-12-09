#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>

struct layer {
    static constexpr auto columns = 25;
    static constexpr auto rows = 6;
    static constexpr auto pixel_count = columns * rows;
    char pixels[pixel_count]; 
}; 

int main(int argc, char ** argv) {
    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
     
    std::string line; 
    getline( input_file, line );
    std::stringstream ss(line);

    auto layernum = line.size() / layer::pixel_count; 
    std::cout << "Number of layers: " << layernum << std::endl;

    layer * layers = new layer[layernum]; 
    int count = 0; 
    for (char i; ss >> i;) {
        layers[count/layer::pixel_count].pixels[count % layer::pixel_count] = i - '0'; 
        count++;  
    }

    layer result = layers[layernum - 1]; 

    for (int i = layernum -2; i >= 0; i--) {
        const layer & current_layer = layers[i]; 
        for (int j = 0; j < layer::pixel_count; j++) {
            if (current_layer.pixels[j] != 2) {
                result.pixels[j] = current_layer.pixels[j]; 
            }
        }
    }

    for (int i = 0; i < layer::rows; i++) {
        for (int j = 0; j < layer::columns; j++) {
            char current_char; 
            if (result.pixels[i * layer::columns + j] == 2 || result.pixels[i * layer::columns + j] == 0)
                current_char = ' '; 
            else 
                current_char = result.pixels[i * layer::columns + j] + '0'; 
            std::cout << current_char; 
        }
        std::cout << std::endl;
    }

    return 0; 
}