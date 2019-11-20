#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>
#include <boost/algorithm/string.hpp>

int main() {

    constexpr int DANCEMAX = 16; 
    std::fstream input("input.txt"); 
    std::string line = "s1,x3/4,pe/b" ; 
    std::string delimiter(","); 
    std::getline(input, line); 
    std::vector<std::string> strs;
    boost::split(strs,line, boost::is_any_of(delimiter));
    std::deque<char> dance(DANCEMAX); 
    std::iota(dance.begin(), dance.end(), 'a'); 

    char action; 

    std::vector<std::deque<char> > dances; 
    dances.push_back(dance);
    int i = 0;   
    while (true) {
        for (const std::string & str : strs) {
            std::stringstream ss(str); 
            ss >> action; 
            /* std::for_each(dance.begin(), dance.end(), [] (char num) { std::cout << num << " ";}); 
            std::cout << std::endl; */ 
            
            if (action == 's') {
                int spinnum; 
                ss >> spinnum; 
                spinnum = spinnum % DANCEMAX; // csak hogy biztos ne legyen gond azzal, hogy túl sokat szeretnénk őket cserélgetni. 
                dance.insert(dance.begin(), dance.end() - spinnum, dance.end());
                /* std::for_each(dance.begin(), dance.end(), [] (char num) { std::cout << num << " ";}); 
                std::cout << std::endl; */ 
                dance.erase(dance.end() - spinnum, dance.end()); 
            } else if (action == 'x') {
                int num1, num2; 
                ss >> num1 >> action >> num2; 
                std::swap(dance[num1], dance[num2]);
            } else if (action == 'p') {
                int pos = str.find("/"); 
                std::string str1 = str.substr(1, pos-1); 
                std::string str2 = str.substr(pos+1); 
                auto it1 = std::find(dance.begin(), dance.end(), str1[0]); 
                auto it2 = std::find(dance.begin(), dance.end(), str2[0]); 
                char tmp = *it1; 
                *it1 = *it2;
                *it2 = tmp;
            }
        }
        if (std::find(dances.begin(), dances.end(), dance) == dances.end()) {
            dances.push_back(dance); 
            std::cout << "Inserting new value: " << i << " "; 
            std::for_each(dance.begin(), dance.end(), [] (char num) { std::cout << num << " ";}); 
            std::cout << std::endl; 
        } else { 
            std::cout << "Found again: " << i << " "; 
            std::for_each(dance.begin(), dance.end(), [] (char num) { std::cout << num << " ";}); 
            std::cout << std::endl; 
            break;
        }
        i++; 
    }
    dance = dances[1000000000 % dances.size()]; 
    std::for_each(dance.begin(), dance.end(), [] (char num) { std::cout << num;}); 
    std::cout << std::endl; 
}