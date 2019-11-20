
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <deque>

static constexpr int LISTSIZE = 256;

void transformVector(std::vector<uint> & list, const std::vector<int> & lengths) {
    uint currentPos = 0; 
    uint skipSize = 0; 
    for (int i = 0; i < 64; i++) {
        for ( int currentLenght : lengths) {
            uint start = currentPos; 
            uint end = (currentPos + currentLenght) % LISTSIZE; 
            
            if (currentLenght != 0) 
                if (end <= start) {                 
                    std::vector<uint> toReverse; 
                    std::copy(list.begin() + start, list.end(), std::back_inserter(toReverse)); 
                    std::copy(list.begin(), list.begin() + end, std::back_inserter(toReverse)); 
                    std::reverse(toReverse.begin(), toReverse.end()); 

                    std::vector<uint> newList;

                    std::copy(toReverse.begin() + (LISTSIZE - start), toReverse.end(), std::back_inserter(newList)); 
                    std::copy(list.begin() + end, list.begin() + start, std::back_inserter(newList)); 
                    std::copy(toReverse.begin(), toReverse.begin() + (LISTSIZE - start), std::back_inserter(newList)); 
                    list = std::move(newList); 
                } else {
                    std::reverse(list.begin()+ start, list.begin() + end); 
                }

            currentPos = (currentPos + currentLenght + skipSize) % LISTSIZE;
            skipSize++; 
        }
    }
}
            
std::bitset<128> createDenseHash(std::vector<uint> & list) {
    // std::stringstream ss;
    std::bitset<128> bs; 
    int counter = 0; 
    for (int i = 0; i < 16; i++) {
        uint x = list[i * 16]; 
        for (int j = 1; j < 16; j++) {
            x = x ^ list[i * 16 + j]; 
        }
        // ss << std::hex << ((x >> 4) & 0xF) << (x & 0xF);
        for (int j = 0; j < 8; j++) {
            bs[counter++] = (x >> (7 - j)) & 0x1; 
        }
    }
    return bs;
}

std::vector<int> lengthsFromString(const std::string & str ) {
    std::vector<int> temp; 
    for (int i = 0; i < str.size(); i++) {
        temp.push_back(str[i]); 
    }
    temp.push_back(17); 
    temp.push_back(31); 
    temp.push_back(73); 
    temp.push_back(47); 
    temp.push_back(23); 
    return temp; 
}

int main() {
    // std::string hash = "31,2,85,1,80,109,35,63,98,255,0,13,105,254,128,33"; 
    std::stringstream ss; 
    std::vector<std::bitset<128> > hashes; 
    std::deque<std::pair<uint, uint> > openList;
    int matrix[128][128]; 
    uint numOfOnes = 0; 

    for (uint i = 0; i < 128; i++) {
        ss.str(std::string());
        ss << "ugkiagan-" << i; 
        std::string hash = ss.str();
        // creating string for knot hash

        std::vector<uint> list(LISTSIZE); 
        std::vector<int> lengths = lengthsFromString(hash); 
        std::iota(list.begin(), list.end(), 0); 
        // initiated vector

        transformVector(list, lengths); 
        std::bitset<128> denseHash = createDenseHash(list);
        for (uint j = 0; j < 128; j++) {
            if (denseHash[j]) 
                matrix[i][j] = -1;
            else 
                matrix[i][j] = 0; 
        }
        std::cout << denseHash.to_string() << std::endl; 
        numOfOnes += denseHash.count(); 
        // hashes.push_back(denseHash); 
    }

    uint currentGroup = 0; 
    std::cout << "Number of squares " << numOfOnes << std::endl;

    for (uint i = 0; i < 128; i++){ 
        for (uint j = 0; j < 128; j++) {
            std::cout << matrix[i][j] << "\t"; 
        }
        std::cout << std::endl; 
    }

    for (uint i = 0; i < 128; i++){ 
        for (uint j = 0; j < 128; j++) {
            // std::cout << "Current i and j is " << i << "\t" << j << std::endl;
            if (matrix[i][j] == 0) 
                continue; 
            if (matrix[i][j] == -1) {
                currentGroup++;
                openList.push_back(std::make_pair(i, j)); 
            }

            while(openList.size() > 0) {
                std::pair<uint, uint> p = openList.front(); 
                openList.pop_front(); 
                int t1, t2; 
                
                // std::cout << "\t Current i and j is " << p.first << "\t" << p.second << std::endl;
                matrix[p.first][p.second] = currentGroup; 

                // std::cout << "T1 " << std::endl;
                t1 = p.first -1; 
                t2 = p.second; 
                if (t1 >= 0 && matrix[t1][t2] == -1)
                    openList.push_back(std::make_pair(t1,t2)); 

                // std::cout << "T2 " << std::endl;
                t1 = p.first +1; 
                t2 = p.second; 
                if (t1 < 128 && matrix[t1][t2] == -1)
                    openList.push_back(std::make_pair(t1,t2)); 

                // std::cout << "T3 " << std::endl;
                t1 = p.first; 
                t2 = p.second - 1; 
                if (t2 >= 0 && matrix[t1][t2] == -1)
                    openList.push_back(std::make_pair(t1,t2)); 

                // std::cout << "T4 " << std::endl;
                t1 = p.first; 
                t2 = p.second + 1; 
                if (t2 < 128 && matrix[t1][t2] == -1)
                    openList.push_back(std::make_pair(t1,t2)); 
            }

        }
    }

    std::cout << "Number of groups " << currentGroup << std::endl;

    for (uint i = 0; i < 128; i++){ 
        for (uint j = 0; j < 128; j++) {
            std::cout << matrix[i][j] << "\t"; 
        }
        std::cout << std::endl; 
    }
}