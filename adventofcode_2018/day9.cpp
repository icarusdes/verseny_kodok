#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <algorithm>

#include <boost/algorithm/string.hpp>

int main(int argc, char ** argv) {

    // 438 players; last marble is worth 71626 points

    int player_num = 438; 
    int last_marble_worth = 71626*100; 
    int current_player = 1; 
    int current_marble_index = 1;
    int current_marble = 2;  
    int vec_size = 2; 

    std::vector<uint64_t> player_scores; 
    player_scores.reserve(player_num); 
    std::vector<int> marbles = {0, 1}; 
    marbles.reserve(last_marble_worth);

    std::cout << "[" << current_player + 1 << "]\t"; 
    for (int i = 0; i < marbles.size(); i++) {
        if (current_marble_index == i) std::cout << "("; 
        std::cout << marbles[i]; 
        if (current_marble_index == i) std::cout << ")";  
        std::cout << " ";
    }
    std::cout << std::endl;

    while (current_marble <= last_marble_worth) {
        
        if ((current_marble % 10000) == 0 )
            std::cout << current_marble << std::endl; 
        if (current_marble % 23 == 0) {
            int to_be_removed_marble = ((current_marble_index - 7 + marbles.size()) % marbles.size()); 
            player_scores[current_player] += current_marble; 
            player_scores[current_player] += *(marbles.begin() + to_be_removed_marble); 
            current_marble_index = to_be_removed_marble;  
            marbles.erase(marbles.begin() + to_be_removed_marble); 
            current_marble++; 
            vec_size--; 
            current_player = current_player + 1;
            if (current_player >= player_num)
                current_player -= player_num;
        } else { 
            int next_marble_index = current_marble_index + 2; 
            if  (next_marble_index >= vec_size) {
                next_marble_index -= vec_size; 
            }
            auto it = marbles.begin() + next_marble_index; 
            marbles.insert(it, current_marble); 
            
            current_marble_index = next_marble_index;
            current_marble++; 
            vec_size++; 
            current_player = (current_player + 1) % player_num; 
        }
        /* 
        std::cout << "[" << current_player + 1 << "]\t"; 
        for (int i = 0; i < marbles.size(); i++) {
            if (current_marble_index == i) std::cout << "("; 
            std::cout << marbles[i]; 
            if (current_marble_index == i) std::cout << ")";  
            std::cout << " ";
        }
        std::cout << std::endl; */
    }
    std::cout << "--------------------------- Scores --------------" << std::endl; 
    std::sort(player_scores.begin(), player_scores.end()); 
    uint64_t highest = 0; 
    for (int i = 0; i < player_num; i++ ) {
        std::cout << "Player " << i + 1 << " score: " << player_scores[i] << std::endl; 
        highest = std::max(highest, player_scores[i]); 
    }

    std::cout << "Highest value is: " << highest << std::endl; 
    return 0; 
}