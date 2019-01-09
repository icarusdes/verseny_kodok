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

struct point {
    int x = 0, y = 0; 
    int vx = 0, vy = 0; 
    int cx = 0, cy = 0; 
}; 

std::pair<float, float> center_of_weights(const std::vector<point> & points) {
    std::pair<float, float> center = {0.0, 0.0} ; 
    for (auto p : points) {
        center.first += p.cx; 
        center.second += p.cy;  
    }
    center.first = center.first / points.size(); 
    center.second = center.second / points.size();
    // std::cout << "Center cx: " << center.first << std::endl; 
    // std::cout << "Center cy: " << center.second << std::endl; 
    return center;
}

void update_current_pos(std::vector<point> & points, int time) {
    for (point & p: points) {
        p.cx = p.x + p.vx * time;
        p.cy = p.y + p.vy * time;
    }
    std::cout << "Updated" << std::endl;
}

std::pair<float, float> average_distance(const std::vector<point> & points) {
    auto center = center_of_weights(points); 
    // std::cout << "Center: {" << center.first << ", "  << center.second << "} " << std::endl;
    std::pair<float, float> dist = {0.0, 0.0}; 
    for (auto p: points) {
        dist.first += abs(p.cx - center.first);
        dist.second += abs(p.cy - center.second);
    }
    dist.first = dist.first / points.size(); 
    dist.second = dist.second / points.size(); 
    // std::cout << "Distance cx: " << dist.first << std::endl; 
    // std::cout << "Distance cy: " << dist.second << std::endl; 

    return dist; 
}

int main(int argc, char ** argv) {
    std::fstream input_file; 
    input_file.open("input_day10.txt");

    std::vector<point> points;

    // position=< 9,  1> velocity=< 0,  2> 
    boost::regex expr{"position=<\\s*(\\-?\\d+),\\s*(\\-?\\d+)> velocity=<\\s*(\\-?\\d+),\\s*(\\-?\\d+)>"}; 
    for( std::string line; getline( input_file, line ); ) {
        boost::smatch what;
        if (boost::regex_search(line, what, expr))
        {            
            point p; 
            p.x = std::stoi(what[1]);
            p.y = std::stoi(what[2]);
            p.vx = std::stoi(what[3]);
            p.vy = std::stoi(what[4]);
            p.cx = p.x;
            p.cy = p.y;
            points.push_back(p);
        }
    }

    std::pair<float, float> prevdist; 
    std::pair<float, float> curdist = average_distance(points);
    int time = 0; 
    for (auto p: points ) {
        std::cout << "{" << p.x << ", " << p.y << ", " << p.vx << ", " << p.vy << ", " << p.cx << ", " << p.cy << "}" << std::endl; 
    }
    do {
        prevdist = curdist; 
        time++; 
        update_current_pos(points, time); 
        /* for (auto p: points ) {
            std::cout << "{" << p.x << ", " << p.y << ", " << p.vx << ", " << p.vy << ", " << p.cx << ", " << p.cy << "}" << std::endl; 
        } */ 
        curdist = average_distance(points); 
    } while (curdist < prevdist); 

    /* 


    */ 

    int prev_time = time -1; 
    update_current_pos(points, prev_time);

    int left    = points[0].cx;
    int right   = points[0].cx;
    int top     = points[0].cy;
    int bottom  = points[0].cy;

    for (auto p: points ) {
        if ( left > p.cx ) 
            left = p.cx;
        if ( right < p.cx ) 
            right = p.cx; 
        if ( bottom > p.cy ) 
            bottom = p.cy;
        if ( top < p.cy ) 
            top = p.cy;
    }

    int width = right - left + 1 ; 
    int height = top - bottom + 1; 
    int * matrix = new int[ width * height]; 

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) 
            matrix[i * width + j] = 0; 

    for (auto p: points ) {
        matrix[(p.cy - bottom) * width + (p.cx - left) ] = 1; 
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            if (matrix[i * width + j]) 
                std::cout << "#"; 
            else 
                std::cout << "."; 
        }
        std::cout << std::endl; 
    }

    delete matrix; 

    std::cout << "Bounding box {(" << left << ", " << bottom << "), (" << right << ", " << top << ")}" << std::endl; 
    std::cout << "Time is: " << time << std::endl; 
}