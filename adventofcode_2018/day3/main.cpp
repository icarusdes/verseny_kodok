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
            numbers.push_back(a);
        }
        std::sort(numbers.begin(), numbers.end()); 
        uint diff = numbers[numbers.size() - 1] - numbers[0]; 
        sum += diff; 
    }
    std::cout << "The sum of all differences is: " << sum << std::endl;
    return 0; 
}