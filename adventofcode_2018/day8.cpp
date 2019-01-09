#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>

#include <boost/algorithm/string.hpp>
 
/* 

Specifically, a node consists of:

A header, which is always exactly two numbers:
The quantity of child nodes.
The quantity of metadata entries.
Zero or more child nodes (as specified in the header).
One or more metadata entries (as specified in the header).
Each child node is itself a node that has its own header, child nodes, and metadata. For example:

2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2
A----------------------------------
    B----------- C-----------
                     D-----
*/ 


int * inputs; 
int current_inp = 0; 

struct node {
    std::vector<node*> nodes; 
    std::vector<int> data; 

    ~node() {
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            delete *it; 
        }
    }

    int sumData() {
        int sum = 0;    
        for (auto n : nodes) {
            sum += n->sumData(); 
        }
        for (auto v : data) {
            sum += v; 
        }
        return sum; 
    }

    int strangeSum() {
        int sum = 0; 
        if (nodes.size()) {
            // van gyerek, bonyi eset
            for (auto v : data) {
                if (((v - 1) >= nodes.size()) || v == 0) {
                    sum += 0; 
                } else {
                    sum += nodes[v - 1]->strangeSum(); 
                }
            }            
        } else {
            // nincs gyerek, egyszerűen csak a metadatak összege; 
            for (auto v : data) {
                sum += v; 
            }
        }
        return sum; 
    }

}; 

node * processInputs() {
    node * current_node = new node(); 
    int childnodes = inputs[current_inp++];
    int metadatas  = inputs[current_inp++];
    for (int i = 0; i < childnodes; i++) {
        current_node->nodes.push_back(processInputs()); 
    }
    for (int i = 0; i < metadatas; i++) {
        current_node->data.push_back(inputs[current_inp++]); 
    }
    return current_node; 
}

int main(int argc, char ** argv) {

    std::fstream input_file; 
    std::string line; 
    std::vector<std::string> results;

    input_file.open("input_day8.txt"); 
    getline( input_file, line );
    boost::split(results, line, [](char c){return c == ' ';});
    inputs = new int[results.size()]; 
    int i = 0; 

    for (auto it = results.begin(); it != results.end(); it++) { 
        inputs[i] = std::stoi(*it); 
        i++; 
    }

    node * root = processInputs(); 
    std::cout << "Sum of metadatas is: " << root->sumData() << std::endl; 
    std::cout << "Strangesum is: " << root->strangeSum() << std::endl; 
    delete root; 
    return 0; 
}