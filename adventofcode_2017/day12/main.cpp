#include <iostream> 
#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

int main() {
    uint size = 0; 
    uint size2 = 0; 
    std::string line; 
    std::fstream input("input.txt"); 
    std::string delimiters(", "); 
    boost::regex regex("(\\d+) <-> ([0-9 ,]+).*");
    boost::smatch match; 
    std::set<uint> * sets[2000]; 
    for (uint i = 0; i < 2000; i++) {
        std::set<uint> * pset = new std::set<uint>(); 
        pset->insert(i); 
        sets[i] = pset;
    }


    while (std::getline(input, line)) {
        std::cout << line << std::endl;
        if (boost::regex_match(line, match, regex)) {
            uint currentid = std::stoi(match[1]);
            std::string idListString = match[2]; 
            std::vector<std::string> vec; 
            boost::split( vec, idListString, boost::is_any_of(delimiters));

            for (const std::string & str : vec) {

                if (str == "")
                    continue;
                uint otherid = std::stoi(str); 
                if (otherid == currentid)
                    continue;                
                if (sets[currentid] == sets[otherid]) 
                    continue;

                sets[currentid]->insert(sets[otherid]->begin(), sets[otherid]->end()); 
                void * tp = sets[otherid]; 
                delete  sets[otherid]; 
                for (int i = 0; i < 2000; i++) {
                    if (sets[i] == tp)
                        sets[i] = sets[currentid];
                }
            }
        } 
    }

    std::set<std::set<uint>* > pointerSet; 

    for (int i = 0; i < 2000; i++) {
        pointerSet.insert(sets[i]); 
    }
    
    std::cout << "Number of elements in the group containing number 0: " << sets[0]->size() << std::endl; 
    std::cout << "Number of groups: " << pointerSet.size() << std::endl;
    return 0; 
}