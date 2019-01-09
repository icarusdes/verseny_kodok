#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <stdio.h>
#include <ctype.h> 
#include <boost/regex.hpp>

int main(int argc, char ** argv) {

    // const int grid_serial_number = 57; 
    // const int grid_serial_number = 39; 
    // const int grid_serial_number = 71; 
    // const int grid_serial_number = 18;
    const int grid_serial_number = 5153; 
    int fuelcells[300][300]; 

    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {            
            const int x = i + 1; 
            const int y = j + 1; 
            const int rack_id = x + 10;
            int power_level = (((rack_id * y + grid_serial_number) * rack_id) % 1000) / 100 - 5; 

            fuelcells[i][j] = power_level;
        }
    }

    int max_value = -1000;
    int max_grid_size = 1; 
    int max_x = 1; 
    int max_y = 1; 

    for (int grid_size = 1; grid_size <= 300; grid_size++) {
        std::cout << "Tested grid_size: " << grid_size << "x" << grid_size << std::endl;
        for (int i = 0; i < 300 - grid_size + 1; i++) {
            for (int j = 0; j < 300 - grid_size + 1; j++) {
                int sum = 0; 
                for (int x = 0; x < grid_size; x++) 
                    for (int y = 0; y < grid_size; y++) {
                        sum += fuelcells[i + x][j+y]; 
                    }
                if (sum > max_value) {
                    max_value = sum; 
                    max_grid_size = grid_size; 
                    max_x = i + 1; 
                    max_y = j + 1; 
                }
            }
        }
    }

    std::cout << max_x << "," << max_y << "," << max_grid_size << " " << max_value; 
}