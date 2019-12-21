#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <filesystem>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

struct compound {
    int amount;
    std::string name;
    bool produced_from_ore = false; 

    friend std::ostream & operator<<(std::ostream & os, const compound & c);
};

std::ostream & operator<<(std::ostream & os, const compound & c) {
    os << c.amount << " x " << c.name; 
    if (c.produced_from_ore) 
        os << " (from ORE) ";
    return os;
}

struct recipe {
    int level = -1;
    compound current;
    std::vector<compound> compounds; 

    friend std::ostream & operator<<(std::ostream & os, const recipe & r);
}; 

std::ostream & operator<<(std::ostream & os, const recipe & r) {
    os << "Current compound: " << r.current << std::endl; 
    for (auto & c : r.compounds) {
        os << "\t" << c << std::endl; 
    }
    os << "Level: " << r.level << std::endl;
    return os; 
}

recipe parse(const std::string line) {
    recipe current_recipe;
    boost::regex expr{"(.*) => (.*)"};
    boost::smatch what;
    if (boost::regex_search(line, what, expr))
    {
        int number; 
        std::string compound_name;
        std::stringstream ss(what[2]); // what we are making part
        ss >> number >> compound_name; 
        current_recipe.current.amount = number;
        current_recipe.current.name = compound_name; 
        std::cout << "Current compound: " << number << "x" << compound_name << std::endl; 

        std::vector<std::string> results;
        boost::split(results, what[1], [](char c){return c == ',';});

        if (results.size() == 1) {
            std::stringstream ss(results[0]); // what we are making part
            ss >> number >> compound_name;
            current_recipe.compounds.push_back({number, compound_name});
            std::cout << "\tMade from: " << number << "x" << compound_name <<  std::endl; 
            if (compound_name == "ORE") {
                current_recipe.current.produced_from_ore = true;
                current_recipe.level = 1;
            } 
        } else {
            for (auto v : results) {
                std::stringstream ss(v); // what we are making part
                ss >> number >> compound_name;
                std::cout << "\tMade from: " << number << "x" << compound_name <<  std::endl; 
                current_recipe.compounds.push_back({number, compound_name});
            }            
        }
    }
    return current_recipe;  
}

std::vector<recipe> recipes; 

recipe & findRecipeByName(const std::string & name) {
    auto it = std::find_if(recipes.begin(), recipes.end(), [=](const recipe & r) { return r.current.name == name; });
    return *it;  
}

void generateLevels(const std::string & name) {
    recipe & current_r = findRecipeByName(name); 
    int max_level = -1;
    for (compound & c : current_r.compounds) {
        recipe & r = findRecipeByName(c.name); 
        if (r.level == -1) 
            generateLevels(r.current.name);
        if (r.level > max_level) 
            max_level = r.level; 
    }
    current_r.level = max_level + 1; 
}

void generateDotFile(const std::string & input_file_name) {
    std::ofstream outfile;
    std::cout << input_file_name << std::endl; 
    outfile.open(input_file_name + ".dot");
    outfile << "digraph day_14 {" << std::endl;
    outfile << "\tnode [shape=box style=filled]" << std::endl; 
    for ( auto & r : recipes) {
        for ( auto & c : r.compounds) {
            outfile << "\t" << c.name << " -> " << r.current.name << ";" << std::endl;
        }
    }

    auto & fuel_recipe = findRecipeByName("FUEL"); 

    std::cout << "Max level: " << fuel_recipe.level << std::endl;

    for (int i = 1; i < fuel_recipe.level; i++) {
        outfile << "\t{rank=same; "; 
        for ( auto & r : recipes) {
            if (r.level == i) {
                outfile << r.current.name << " "; 
            }
        }
        outfile << "}" << std::endl;
    }

    // {rank=same;ITManager Teacher1 Teacher2}  // Put them on the same level 

    outfile << "}" << std::endl;
}

int main(int argc, char ** argv) {
    std::fstream input_file; 
    std::string input_file_name; 

    if (argc == 1) {
        input_file_name = "input.txt";     
    } else {
        input_file_name = argv[1];
    }

    input_file.open(input_file_name);

    for (std::string line; getline(input_file, line);) {
        recipes.push_back(parse(line));
    }

    
    for (recipe & current_recipe : recipes) {
        // mindegyik recepten vegigmegyunk 
        if (! current_recipe.current.produced_from_ore)
            for (compound & c : current_recipe.compounds) {
                // es azoknak minden osszetevoje
                auto r = findRecipeByName(c.name); 
                c.produced_from_ore = r.current.produced_from_ore;
            }
    }

    generateLevels("FUEL");
    generateDotFile(argv[1]); 

    auto fuel_it = std::find_if(recipes.begin(), recipes.end(), [](const recipe & r) { return r.current.name == "FUEL";});
    if (fuel_it != recipes.end()) {
        recipe fuel_recipe = *fuel_it; 
        recipes.erase(fuel_it); 

        while (std::count_if(fuel_recipe.compounds.begin(), fuel_recipe.compounds.end(), [=] (const compound & c) { return c.produced_from_ore == false; })) {                        
            auto max_level_comp = std::max_element(fuel_recipe.compounds.begin(), fuel_recipe.compounds.end(), [=](const compound & c1, const compound & c2) { 
                    const auto rec1 = findRecipeByName(c1.name);
                    const auto rec2 = findRecipeByName(c2.name); 
                    return rec1.level < rec2.level; } );
            int highest_level = findRecipeByName(max_level_comp->name).level;
            // van még olyan anyag, ami nem triviálisan előállítható ércből
            // keresünk tehát egy ilyent, elmentjuk, toroljuk
            {
                auto it = std::find_if(fuel_recipe.compounds.begin(), fuel_recipe.compounds.end(), [=] (const compound & c) { const auto rec = findRecipeByName(c.name);  return c.produced_from_ore == false && rec.level == highest_level;}); 
                compound backup = *it; 
                auto recipe = findRecipeByName(backup.name);

                if (backup.amount % recipe.current.amount == 0) { 
                    // szerencsénk van, mert a recept amit találtunk egész 
                    // számúszor van meg a számunkra szükséges mennyiségben 
                    fuel_recipe.compounds.erase(it); 
                    int multiplier = backup.amount / recipe.current.amount; 
                    for (auto c : recipe.compounds) {
                        auto comp_it = find_if(fuel_recipe.compounds.begin(), fuel_recipe.compounds.end(), [=] (const compound & comp) { return comp.name == c.name;} );
                        if (comp_it == fuel_recipe.compounds.end()) {
                            fuel_recipe.compounds.push_back({c.amount * multiplier, c.name, c.produced_from_ore }); 
                        } else {
                            comp_it->amount += c.amount * multiplier;
                        }
                    }
                } else {
                    fuel_recipe.compounds.erase(it); 
                    int multiplier = backup.amount / recipe.current.amount + 1;
                    std::cout << "Megmarad " <<  recipe.current.amount * multiplier - backup.amount << " ebből: " << recipe.current.name << std::endl; 

                    for (auto c : recipe.compounds) {
                        auto comp_it = find_if(fuel_recipe.compounds.begin(), fuel_recipe.compounds.end(), [=] (const compound & comp) { return comp.name == c.name;} );
                        if (comp_it == fuel_recipe.compounds.end()) {
                            fuel_recipe.compounds.push_back({c.amount * multiplier, c.name, c.produced_from_ore }); 
                        } else {
                            comp_it->amount += c.amount * multiplier;
                        }
                    }
                }

                // std::cout << fuel_recipe << "------------------------" << std::endl;
            }
            // megvan, így megkeressük, hogy milyen receptektől áll össze 
        } 
        // és a vegen az egészet átváltjuk ORE-ra 
        int sum_ore = 0;
        for ( auto & c: fuel_recipe.compounds) {
            auto r = findRecipeByName(c.name); 
            int mult = 0;
            if (c.amount % r.current.amount == 0) {
                mult = c.amount / r.current.amount; 
            } else {
                mult = c.amount / r.current.amount + 1; 
            }
            int temp = mult * r.compounds.front().amount;
            std::cout << "sum: " <<sum_ore << " + " << temp << " for " << c.name << std::endl;
            sum_ore += temp;
        }

        std::cout << "A szükséges ORE mennyiség: " << sum_ore << std::endl;
        std::cout << "With one trilion ore: " << 1000000000000l / sum_ore << std::endl;
    } else {
        std::cout << "Nagy gebasz van. Nincs recept az üzemanyagra" << std::endl;
    }

    return 0; 
}