#include <iostream>
#include <fstream> 
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>

struct pont {
    int x; 
    int y; 
};

struct vonal {
    pont start, stop; 
    bool fekvo = false; 
};

struct metszespont {
    int x; 
    int y; 
    int wire1_dist; 
    int wire2_dist; 
}; 

int main(int argc, char ** argv) {
    std::fstream input_file; 
    if (argc == 1) {
        input_file.open("input.txt");     
    } else {
        input_file.open(argv[1]);
    }

    std::vector<vonal> lines; 
    std::vector<metszespont> metszespontok; 

    std::string line1; 
    std::string line2;
    getline( input_file, line1 );
    std::stringstream ss(line1);
    int x = 0; 
    int y = 0; 
    bool fekvo = false; 

    for (char direction; ss >> direction;) {
        int distance; ss >> distance; 
        int next_x = x;
        int next_y = y;
        if (direction == 'L') {
            next_x -= distance; 
            fekvo = true;
        } else if (direction == 'R') {
            next_x += distance; 
            fekvo = true;
        } else if (direction == 'U') {
            next_y += distance; 
            fekvo = false; 
        } else { // D 
            next_y -= distance;
            fekvo = false; 
        }
        pont start {std::min(x, next_x), std::min(y, next_y)}; 
        pont stop {std::max(x, next_x), std::max(y, next_y)}; 

        lines.push_back(vonal{start, stop, fekvo}); 

        if (ss.peek() == ',')
            ss.ignore();
        x = next_x; 
        y = next_y;
    }

    getline( input_file, line2 );
    ss = std::stringstream(line2);
    x = 0; 
    y = 0; 

    for (char direction; ss >> direction;) {
        int distance; ss >> distance;
        int next_x = x;
        int next_y = y;
        if (direction == 'L') {
            next_x -= distance; 
            fekvo = true;
        } else if (direction == 'R') {
            next_x += distance; 
            fekvo = true;
        } else if (direction == 'U') {
            next_y += distance; 
            fekvo = false; 
        } else { // D 
            next_y -= distance;
            fekvo = false; 
        }
        pont start {std::min(x, next_x), std::min(y, next_y)}; 
        pont stop {std::max(x, next_x), std::max(y, next_y)}; 

        x = next_x; 
        y = next_y;

        for ( auto v : lines) {
            if (v.fekvo == fekvo) {
                continue;
                if (fekvo && v.start.y == y) {
                    // az y allando 
                    int metszet_x1 = std::max(v.start.x, start.x);
                    int metszet_x2 = std::min(v.stop.x, stop.x);
                    if (metszet_x2 >= metszet_x1) {
                        for (int i = metszet_x1; i <= metszet_x2; i++)
                            if (i != 0 || y != 0) 
                                metszespontok.push_back({i, y, -1, -1});
                    }
                } else if (v.start.x == x) {
                    // az x allando
                }
                // ezzel még nem foglalkozunk - jelenleg feltételezzük, hogy a párhuzamosok nem metszik egymást 
            } else {
                if (fekvo) { 
                    // mi fekvők (nálunk csak az x változik, y nem) vagyunk, ő nem (ott az x állandó és az y nem) 
                    int temp_x = v.start.x;
                    int temp_y = y;
                    if ((start.x <= temp_x) && (temp_x <= stop.x) && (v.start.y <= temp_y) && (temp_y <= v.stop.y)) 
                    {
                            if (temp_x != 0 || temp_y != 0) {
                                metszespontok.push_back({temp_x, temp_y, -1, -1});
                            }
                    }
                } else {
                    // mi állok (nálunk csak az y változik, x nem) vagyunk, ő nem (ott az y állandó és az x nem) 
                    int temp_x = x;
                    int temp_y = v.start.y;
                    if ((v.start.x <= temp_x) && (temp_x <= v.stop.x) && (start.y <= temp_y) && (temp_y <= stop.y)) 
                    {
                        if (temp_x != 0 || temp_y != 0) {
                            metszespontok.push_back({temp_x, temp_y, -1, -1});
                        }
                    }
                    // azt jelenti, hogy az x meg fog egyezni a mi koordinátáinkban, de az övében nem
                }
            }
        }

        if (ss.peek() == ',')
            ss.ignore();
    }

    ss = std::stringstream(line1);
    std::cout << line1 << std::endl;

    x = 0; 
    y = 0;
    int the_way_soo_far = 0; 

    for (char direction; ss >> direction;) {
        int distance; ss >> distance;
        int next_x = x;
        int next_y = y;
        if (direction == 'L') {
            next_x -= distance; 
            fekvo = true;
        } else if (direction == 'R') {
            next_x += distance; 
            fekvo = true;
        } else if (direction == 'U') {
            next_y += distance; 
            fekvo = false; 
        } else { // D 
            next_y -= distance;
            fekvo = false; 
        }

        pont start {std::min(x, next_x), std::min(y, next_y)}; 
        pont stop {std::max(x, next_x), std::max(y, next_y)}; 

        std::cout <<  direction << distance << std::endl;
        std::cout << start.x << " " << start.y << std::endl;
        
        for (metszespont & m: metszespontok) {
            if (m.wire1_dist == -1) // már bejártuk egyszer korábban
                if (fekvo) { // y allando
                    if (m.y == y && start.x <= m.x && m.x <= stop.x) // intervallumon belül vagyunk - örülünk vincent 
                    {
                        m.wire1_dist = the_way_soo_far + abs(m.x - x);
                    }  
                } else { // x allando
                    if (m.x == x && start.y <= m.y && m.y <= stop.y) // intervallumon belül vagyunk - örülünk vincent 
                    {
                        m.wire1_dist = the_way_soo_far + abs(m.y - y);
                    } 
                }
        }

        
        x = next_x; 
        y = next_y;
        the_way_soo_far += distance;
        if (ss.peek() == ',')
            ss.ignore();
    }

    ss = std::stringstream(line2);

    x = 0; 
    y = 0;
    the_way_soo_far = 0; 

    for (char direction; ss >> direction;) {
        int distance; ss >> distance;
        int next_x = x;
        int next_y = y;
        if (direction == 'L') {
            next_x -= distance; 
            fekvo = true;
        } else if (direction == 'R') {
            next_x += distance; 
            fekvo = true;
        } else if (direction == 'U') {
            next_y += distance; 
            fekvo = false; 
        } else { // D 
            next_y -= distance;
            fekvo = false; 
        }

        pont start {std::min(x, next_x), std::min(y, next_y)}; 
        pont stop {std::max(x, next_x), std::max(y, next_y)}; 

        for (metszespont & m: metszespontok) {
            if (m.wire2_dist != -1) // már bejártuk egyszer korábban
                continue; 
            if (fekvo) { // y allando
                if (m.y == y && start.x <= m.x && m.x <= stop.x) // intervallumon belül vagyunk - örülünk vincent 
                {
                    m.wire2_dist = the_way_soo_far + abs(m.x - x);
                }  
            } else { // x allando
                if (m.x == x && start.y <= m.y && m.y <= stop.y) // intervallumon belül vagyunk - örülünk vincent 
                {
                    m.wire2_dist = the_way_soo_far + abs(m.y - y);
                } 
            }
        }
        
        x = next_x; 
        y = next_y;
        
        the_way_soo_far += distance;
        if (ss.peek() == ',')
            ss.ignore();
    }

    int closest_manh = -1;

    for (auto p : metszespontok) {
        if (closest_manh == -1 || ((abs(p.x) + abs(p.y)) < closest_manh )) {
            closest_manh = abs(p.x) + abs(p.y); 
        }
    }

    std::cout << closest_manh << std::endl;

    int closest_wire_dist = -1;

    for (auto p : metszespontok) {
        std::cout << p.x << " "  << p.y << " " << p.wire1_dist << " " << p.wire2_dist << std::endl;
        if (closest_wire_dist == -1 || (p.wire1_dist + p.wire2_dist) < closest_wire_dist ) {
            closest_wire_dist = (p.wire1_dist + p.wire2_dist); 
        }
    }

    std::cout << closest_wire_dist << std::endl; 

    return 0; 
}