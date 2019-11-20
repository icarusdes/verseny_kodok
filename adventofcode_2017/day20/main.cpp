
#include <string>
#include <boost/regex.hpp>
#include <fstream>
#include <iostream> 



int main() {
    std::fstream input("input.txt"); 
    std::string line; 
    boost::regex matchCoords("p=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>, v=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>, a=<([-+0-9]+),([-+0-9]+),([-+0-9]+)>.*"); 
    boost::smatch matches; 
    std::vector<std::array<int, 9>> particles; 
    int min_accel = INT_MAX; 
    int min_accel_index = 0; 
    int index = 0; 

    while (std::getline(input, line)) {
        if (boost::regex_match(line, matches, matchCoords) ) {
            int pos_x = stoi(matches[1]);
            int pos_y = stoi(matches[2]);
            int pos_z = stoi(matches[3]);
            int vel_x = stoi(matches[4]);
            int vel_y = stoi(matches[5]);
            int vel_z = stoi(matches[6]);
            int acc_x = stoi(matches[7]);
            int acc_y = stoi(matches[8]);
            int acc_z = stoi(matches[9]);
            std::cout << "pos(x, y, z) is " << "(" << pos_x << "," << pos_y << "," << pos_z << ") \t" \
                      << "vel(x, y, z) is " << "(" << vel_x << "," << vel_y << "," << vel_z << ") \t" << "acc(x, y, z) is " << "(" << acc_x << "," << acc_y << "," << acc_z << ")  " << std::endl;
            int m_accel = abs(acc_x) + abs(acc_y) + abs(acc_z); 
            if (min_accel == m_accel ) {
                std::cout << "Min accel found again " << min_accel << std::endl;
            }
            if (m_accel < min_accel) {
                min_accel = m_accel; 
                min_accel_index = index;
                std::cout << "Current min accel is " << min_accel << std::endl;
                std::cout << "Current min accel index is " << min_accel_index << std::endl;
            } 
        
            std::array<int, 9> temp = {pos_x, pos_y, pos_z, vel_x, vel_y, vel_z, acc_x, acc_y, acc_z}; 
            particles.push_back(temp);
            index++; 
        } else {
            std::cout << "Ezzel a sorral baj van: " << line << std::endl;
            exit(0); 
        }
    }

    return 0; 
}