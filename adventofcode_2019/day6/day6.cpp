#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <boost/regex.hpp>

struct Node {
    std::string name;
    std::vector<Node*> childs;
    Node * parent; 
    int depth = 0;

    int sum() {
        int s = 0; 
        for ( auto & it : childs) {
            s += it->sum(); 
        }
        s += depth; 
        return s;
    } 
}; 

struct processed_line {
    std::string line;
    bool processed = false; 
}; 

int main(int argc, char ** argv) {
    Node root;
    root.name = "COM";

    Node * me; 
    Node * santa;

    std::vector<Node*> all_nodes;
    std::vector<processed_line> lines;  
    all_nodes.push_back(&root); 

    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }
    int processed_lines = 0;
    int current_line = 0; 

    for( std::string line; getline( input_file, line );) {
        lines.emplace_back(processed_line{line, 0}); 
    }
    
    boost::regex expr{"(\\w+)\\)(\\w+)"};
    while( processed_lines != lines.size() ) {
        if (lines[current_line].processed != true) {
            std::string line = lines[current_line].line;
            boost::smatch what;
            if (boost::regex_search(line, what, expr))
            {            
                std::string center = what[1]; 
                std::string orbiter = what[2]; 

                auto it = std::find_if(all_nodes.begin(), all_nodes.end(), [center](auto item)->bool { return item->name == center; });
                if (it != all_nodes.end()) {
                    // std::cout << "Parent " << *it << " " << (*it)->name << std::endl;
                    Node * newNode = new Node;
                    newNode->name = orbiter; 
                    newNode->depth = (*it)->depth + 1;
                    newNode->parent = *it;  
                    (*it)->childs.push_back(newNode);
                    all_nodes.push_back(newNode); 
                    processed_lines++; 
                    lines[current_line].processed = true;

                    if (orbiter == "YOU")
                        me = newNode;
                    if (orbiter == "SAN")
                        santa = newNode; 
                }  
            } else {
                std::cout << "No match for: " << line << std::endl;
            }
        }
        current_line = (current_line + 1) % lines.size();
    }
    std::cout << root.sum() << std::endl; 
    // delete root;

    int steps = 0; 

    int depth_distance = me->depth - santa->depth;
    while (depth_distance != 0) {
        if (depth_distance < 0) {
            santa = santa->parent;  
            depth_distance++; 
        } else { // depth_distance > 0
            me = me->parent; 
            depth_distance--; 
        }
        steps++; 
    }
    while (me != santa) {
        me = me->parent; 
        santa = santa->parent; 
        steps += 2; 
    }

    std::cout << "Number of steps: " << steps << std::endl; 

    return 0; 
}