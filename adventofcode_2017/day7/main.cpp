#include <fstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

struct Node {
    std::string name; 
    int weight; 
    std::vector<Node*> childs;

    Node(const std::string & _name, int _weight) : name(_name), weight(_weight) {}
    ~Node() {
        for_each(childs.begin(), childs.end(), [] (Node * p) { delete p; } ); 
    }
    int PrintSubTowerWeights() {
        std::vector<int> nums; 
        std::vector<std::string> names;
        int sum = weight; 
        int w = -1; 
        bool print = false;        
        // std::cout << "Number of childs: " << childs.size() << std::endl; 

        for_each(childs.begin(), childs.end(), [&] (Node* & p) { 
            int cw = p->PrintSubTowerWeights();  
            if (w == -1) {
                w = cw;
            } else if (w != cw) {
                print = true;
            }
            
            names.push_back(p->name); 
            nums.push_back(cw); 
            sum += cw; 
        }); 

        // std::cout << "Current node: " << name << " = " << weight << " " << sum << std::endl;

        if (print) {
            std::cout << "Current node: " << name << " = " << weight << std::endl;
            std::cout << "Number of names: " << names.size() << std::endl;
            std::cout << "Number of nums: " << nums.size() << std::endl;
            for (int i = 0; i < names.size(); i++) {
                std::cout << names[i] << " = " << nums[i] << std::endl; 
            }
            exit(0); 
        }
        return sum;
    }

};

int main() {
    boost::regex regexWithChilds("([a-zA-Z]+) \\(([0-9]+)\\) -> ([a-zA-Z ,]+).*");
    boost::regex regexWithoutChilds("([a-zA-Z]+) \\(([0-9]+)\\).*");
    std::string delimiters(", ");

    std::fstream input("input.txt"); 
    std::string line; 
    std::vector<Node*> rootCandidates; 
    std::map<std::string, Node*> mNodes; 
    boost::smatch match;

    while (std::getline(input, line)) {
        if (boost::regex_match(line, match, regexWithChilds))
        {        
            Node * currentNode = NULL; 
            bool newlyAdded = false; 

            if (mNodes.find(match[1]) != mNodes.end()) { 
                currentNode = mNodes[match[1]];
                currentNode->weight = stoi(match[2]); 
                // std::cout << "Updated " << match[1] << " with value of " << match[2] << std::endl;
            } else {
                newlyAdded = true;
                currentNode = new Node(match[1], stoi(match[2]) ); 
                // std::cout << "Created " << match[1] << " with value of " << currentNode->weight << std::endl;
                mNodes[currentNode->name] = currentNode;
            }

            if (newlyAdded) {
                rootCandidates.push_back(currentNode);
            } else {
                // std::cout << "Removing root candidate " << currentNode->name << std::endl; 
                auto position = std::find(rootCandidates.begin(), rootCandidates.end(), currentNode );
                if (position != rootCandidates.end())
                    rootCandidates.erase( position ); 
            }

            std::vector<std::string> branches; 
            std::string remainingParts(match[3]); 
            boost::split( branches, remainingParts, boost::is_any_of(delimiters));
            for_each(branches.begin(), branches.end(), [&] (const std::string & str) { 
                    if (str != "") {
                        Node * newNode = NULL; 
                        auto it = mNodes.find(str); 
                        if ( it == mNodes.end()) { 
                            newNode = new Node(str, -1); 
                            mNodes[str] = newNode;
                        } else {
                        //     std::cout << "Removing root candidate " << str << std::endl; 
                            auto position = std::find(rootCandidates.begin(), rootCandidates.end(), it->second );
                            if (position != rootCandidates.end())
                                rootCandidates.erase( position ); 
                            newNode = it->second;
                        }
                        currentNode->childs.push_back(newNode); 
                    }
                }
            ); 

        } else if (boost::regex_match(line, match, regexWithoutChilds)) {
            auto it = mNodes.find(match[1]); 
            if ( it == mNodes.end()) { 
                Node * newNode = new Node(match[1], stoi(match[2])); 
                mNodes[match[1]] = newNode;
            } else {
                mNodes[match[1]]->weight = stoi(match[2]); 
                // std::cout << "Updated " << match[1] << " with value of " << match[2] << std::endl;
            }
        } else {
            std::cout << "This sucks" << std::endl;
        }
    }
    std::cout << "Number of root candidates " << rootCandidates.size() << std::endl;
    std::cout << "Name of the root: " << rootCandidates[0]->name << std::endl;
    rootCandidates[0]->PrintSubTowerWeights();
    return 0; 
}