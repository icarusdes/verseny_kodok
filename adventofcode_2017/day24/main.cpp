#include <iostream>
#include <fstream> 
#include <sstream>
#include <bitset>
#include <vector>

std::vector<std::pair<uint, uint>> bridges;
uint totalBridges; 

std::pair<int, int> findMaxBridge(const std::bitset<64> & usedBridges, int lastPort) {
    int maxbridge = -1;
    int lenght = 0;
    bool lfound = false;
    for (int i = 0; i < totalBridges; i++) {
        if (usedBridges[i] == 0 && (bridges[i].first == lastPort || bridges[i].second == lastPort )) {
            std::bitset<64> temp = usedBridges;
            temp[i] = 1;
            int lp = bridges[i].first == lastPort ? bridges[i].second : bridges[i].first; 
            std::pair<int, int> data = findMaxBridge(temp, lp);
            if (data.second > lenght || lfound == false || (data.first > maxbridge && data.second >= lenght)) {
                maxbridge = data.first;
                lenght = data.second; 
            }
            lfound = true;
        } else {
            if (lfound)
                continue; 
            int sum = 0; 
            for (int j = 0; j < totalBridges; j++) {
                if (usedBridges[j] == 1) {
                    sum += bridges[j].first + bridges[j].second; 
                    // std::cout << bridges[j].first << " " << bridges[j].second << " "; 
                }
            }
            // std::cout << std::endl;
            if (sum > maxbridge) {
                maxbridge = sum;
            }
        }
    }
    return std::pair<int, int>(maxbridge, lenght + 1); 
}

int main() {
    std::string line; 
    std::fstream input("input2.txt"); 
    std::bitset<64> bset; 
    char temp; 
    int port1, port2; 
    totalBridges = 0; 

    while (std::getline(input, line)) {        
        std::stringstream ss(line); 
        ss >> port1 >> temp >> port2; 
        bridges.push_back(std::pair<uint, uint>(port1, port2)); 
        totalBridges++;
    }
    std::pair<int, int> maxbridge = findMaxBridge(bset, 0); 
    std::cout << "Max bridge found " << maxbridge.first << std::endl;
    std::cout << "Length is " << maxbridge.second << std::endl;
    return 0;
}