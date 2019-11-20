#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using uint64 = long long unsigned int;

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    std::vector<int> numbers; 
    uint64 sum = 0; 
    while (std::getline(infile, line))
    {
        std::cout << line << std::endl; 
        numbers.clear(); 
        std::istringstream iss(line);
        uint a;
        while (iss >> a) {
            bool toBreak = false; 
            for (int i = 0; i < numbers.size(); i++ ) {
                if (numbers[i] % a == 0) {
                    sum += numbers[i] / a; 
                    std::cout << numbers[i] << " " << a << std::endl;
                    toBreak = true; 
                    break; 
                }
                if (a % numbers[i] == 0) {
                    sum += a / numbers[i]; 
                    std::cout << numbers[i] << " " << a << std::endl;
                    toBreak = true; 
                    break; 
                }
            }
            if (toBreak)
                break;
            numbers.push_back(a);
        }
    }
    std::cout << "The sum of all differences is: " << sum << std::endl;
    return 0; 
}