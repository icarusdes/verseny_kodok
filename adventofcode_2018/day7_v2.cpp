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
    std::pair<std::string, int> workers[5]; 

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

    std::cout << "Remaining: "; 
    for (auto v : points) {
        std::cout << v << " "; 
    }
    std::cout << std::endl; 
    std::sort(points.begin(), points.end());
    auto last = std::unique(points.begin(), points.end());
    points.erase(last, points.end()); 
    std::cout << "Remaining: "; 
    for (auto v : points) {
        std::cout << v << " "; 
    }
    std::cout << std::endl; 

    int points_num = points.size(); 
    int tick = 0; 

    while (printed.size() != points_num) {
        int free_workers = 0; 
        for (int i = 0; i < 5; i++) {
            if (workers[i].first == "") {
                free_workers++; 
            } else {
                if (workers[i].second == tick) {
                    printed.push_back(workers[i].first);  
                    free_workers++;
                    workers[i] = make_pair(std::string(), 0); 
                }                
            }
        }


            for (auto it = points.begin(); (it != points.end()) && free_workers && points.size(); it++) {
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
                    for (int i = 0; i < 5; i++) {
                        if (workers[i].first == "") {
                            workers[i] = std::make_pair(*it, it->c_str()[0] - 'A' + 61 + tick );  
                            // std::cout << workers[i].first << " " << workers[i].second << std::endl; 
                            free_workers--; 
                            points.erase(it);                             
                            break; 
                        }   
                    }
                    it = points.begin(); 
                    continue; 
                }
            }   
        std::cout << tick << "\t" << workers[0].first << "\t" << workers[1].first << "\t" << workers[2].first << "\t" << workers[3].first << "\t" << workers[4].first << "\t"; 
        for (auto v : printed) {
            std::cout << v; 
        }
        std::cout << std::endl;
        tick++;
    }

    std::cout << std::endl; 
    return 0; 
}