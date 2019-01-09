#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cstdio>
#include <utility> 

struct D {
    int id; 
    int sum; 
    int max_sleep; 
    int max_sleep_min; 
}; 

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day4.txt"); 

    std::vector<std::string> sorted_lines; 
    std::vector<D> datas; 

    for( std::string line; getline( input_file, line ); )
    {
        sorted_lines.push_back(line); 
    }
    std::sort(sorted_lines.begin(), sorted_lines.end()); 
    
    // [1518-11-01 00:00] Guard #10 begins shift
    // [1518-11-01 00:05] falls asleep
    // [1518-11-01 00:25] wakes up
    int falls = 0; 
    int wakes = 0; 
    int current_guard = 0; 
    std::vector<std::pair<int, std::vector<int> > > guards_sleeping; 
    auto it = guards_sleeping.end();

    for (int i = 0; i < sorted_lines.size(); i++) {
        int sleeping[60]; 
        auto current_line = sorted_lines[i]; 
        int year, month, day, hour, minute, id;
        if (6 == std::sscanf(current_line.c_str(), "[%d-%d-%d %d:%d] Guard #%d", &year, &month, &day, &hour, &minute, &id )) {
            current_guard = id; 
            it = guards_sleeping.end(); 
            for (auto i = guards_sleeping.begin(); i != guards_sleeping.end(); i++) {
                if (i->first == current_guard) {
                    it = i; 
                } 
            }
            if (it == guards_sleeping.end()) {
                std::vector<int> vec;
                vec.resize(60); 
                guards_sleeping.push_back(std::make_pair( current_guard, vec)); 
                for (auto i = guards_sleeping.begin(); i != guards_sleeping.end(); i++) {
                    if (i->first == current_guard) {
                        it = i; 
                    } 
                }
                for (int i = 0; i < 59; i++) {
                    it->second[i] = 0; 
                } 
            }
        } else if (5 == std::sscanf(current_line.c_str(), "[%d-%d-%d %d:%d]", &year, &month, &day, &hour, &minute)) {
            if (current_line.find("wakes") != std::string::npos) {
                wakes = minute; 
                for (int i = falls; i < wakes; i++) {
                    it->second[i]++; 
                }
            } else if (current_line.find("falls") != std::string::npos) {
                falls = minute; 
            } else {
                return 0; 
            }
        } else {
            std::cout << "Valami itt félrement" << std::endl; 
        }
    }
    
    for (auto it = guards_sleeping.begin(); it != guards_sleeping.end(); it++) {
        std::cout << "Pass for guard: " << it->first << std::endl; 
        D data; 
        data.id = it->first; 
        int max = 0; 
        int max_num = 0; 
        for (int i = 0; i < 60; i++) {
            if (it->second[i] > max) {
                max = it->second[i]; 
                max_num = i; 
            }
        }
        data.max_sleep = max_num; 
        data.max_sleep_min = max; 
        datas.push_back(data); 
        std::cout << "Id: " << data.id << " Sum: " << data.sum << " Max: " << data.max_sleep_min << " Max it: " << data.max_sleep << std::endl; 
    }

    int guard_id = 0; 
    int max_sleep = 0;
    int max_sleep_min = 0;
    for (auto it = datas.begin(); it != datas.end(); it++) {
        if (it->max_sleep_min > max_sleep) {
            max_sleep = it->max_sleep_min; 
            max_sleep_min = it->max_sleep; 
            guard_id = it->id; 
        }
    }

    std::cout << "Guard id is: " << guard_id << std::endl; 
    std::cout << "Min is: " << max_sleep << std::endl; 
    std::cout << "Num is: " << guard_id * max_sleep_min << std::endl; 
    return 0; 
}