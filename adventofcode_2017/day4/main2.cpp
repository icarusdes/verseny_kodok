#include <iostream> 
#include <fstream>
#include <sstream>
#include <algorithm>

using uint64 = long long unsigned int; 

int main() {
    std::ifstream infile("input.txt"); 
    std::string line; 
    std::vector<std::string> passwords;
    std::string currentWord;
    uint goodCatchPhrase = 0; 
    uint numberOfLines = 0;
    while(std::getline(infile, line)) {
        passwords.clear();
        std::istringstream iss(line);
        while (iss >> currentWord) {
            std::sort(currentWord.begin(), currentWord.end());
            passwords.push_back(currentWord); 
        }
        int size_before = passwords.size(); 
        std::sort(passwords.begin(), passwords.end()); 
        auto last = std::unique(passwords.begin(), passwords.end()); 
        passwords.erase(last, passwords.end()); 
        int size_after = passwords.size(); 
        if (size_before == size_after) {
            goodCatchPhrase++; 
        } else {
            std::cout << line << std::endl;
        }
        numberOfLines++;
    }
    std::cout << "Number of lines: " << numberOfLines << std::endl;
    std::cout << "Number of good catchphrases: " << goodCatchPhrase << std::endl; 
}