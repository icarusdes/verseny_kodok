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
    std::fstream input_file; 
    input_file.open("input_day7.txt");

    std::vector<std::pair<std::string, std::string> > net; 
    std::vector<std::string> points;
    std::vector<std::string> printed;

    // Step D must be finished before step E can begin. 
    boost::regex expr{"Step (\\w+) must be finished before step (\\w+) can begin"}; 
    for( std::string line; getline( input_file, line ); ) {
        boost::smatch what;
        if (boost::regex_search(line, what, expr))
        {
            // std::cout << what[1] << " " << what[2] << std::endl; 
            net.push_back(make_pair((std::string) what[2], (std::string) what[1]) ); 
            points.push_back((std::string) what[1]); 
            points.push_back((std::string) what[2]);
        }
    }

    std::sort(net.begin(), net.end());

    for ( auto it = net.begin(); it != net.end(); it++)
        std::cout << it->first << " " << it->second << std::endl; 

    std::sort(points.begin(), points.end());
    auto last = std::unique(points.begin(), points.end());
    points.erase(last, points.end()); 

    int points_num = points.size(); 

    while (printed.size() != points_num) {
        for (auto it = points.begin(); it != points.end(); it++) {
            bool could_be_printed = true; 
            for (auto it2 = net.begin(); it2 != net.end(); it2++) {
                if (it2->first == *it) {
                    if (printed.end() == find(printed.begin(), printed.end(), it2->second)) {
                        could_be_printed = false; 
                        break; 
                    }
                }
            }

            if (could_be_printed) {
                std::cout << *it; 
                printed.push_back(*it); 
                points.erase(it); 
                break; 
            } else {
                continue; 
            }
        }
    }

    std::cout << std::endl; 
    return 0; 
}