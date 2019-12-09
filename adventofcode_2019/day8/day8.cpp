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
        layers[count/layer::pixel_count].pixels[count % layer::pixel_count] = i; 
        count++;  
    }
    
    int least_zero = INT_MAX; 
    int least_zero_layer = -1; 

    for (int i = 0; i < layernum; i++) {
        int zeros = std::count(layers[i].pixels, layers[i].pixels + layer::pixel_count, '0');
        if (zeros < least_zero) {
            least_zero = zeros;
            least_zero_layer = i;
        } 
    }

    std::cout << "Least zero layer number is: " << least_zero_layer << std::endl; 

    int ones = std::count(layers[least_zero_layer].pixels, layers[least_zero_layer].pixels + layer::pixel_count, '1');
    int twos = std::count(layers[least_zero_layer].pixels, layers[least_zero_layer].pixels + layer::pixel_count, '2');

    std::cout << "Product: " << ones*twos << std::endl;

    return 0; 
}