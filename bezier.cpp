//
//  bezier.cpp
//  assignment4
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include "bezier.hpp"
#include <iostream>


point bezier::deCasteljau(std::vector<point> points, double t){
    std::vector<point> next;
    std::vector<point> curr;
    curr = points;
    double n = points.size();
    for(int j = 1; j < n; j++){
        next.clear();
        for(int i = 0; i < (n-j); i++){
            next.push_back(*new point((1-t)*curr[i].x + t * curr[i+1].x,(1-t)*curr[i].y + t * curr[i+1].y));
        }
        std::cout<<next[0].x<< " " << next[0].y << "\n";
        curr = next;
    }
    
    return curr[0];
}
std::vector<point> bezier::deCasteljauV(std::vector<point> points, double resolution){
    std::vector<point> castP;
    for(double t = 0; t <= 1; t+=1/resolution){
        std::vector<point> next;
        std::vector<point> curr;
        curr = points;
        double n = points.size();
        for(int j = 1; j < n; j++){
            next.clear();
            for(int i = 0; i < (n-j); i++){
                next.push_back(*new point((1-t)*curr[i].x + t * curr[i+1].x,(1-t)*curr[i].y + t * curr[i+1].y));
            }
            //  std::cout<<next[0].x<< " " << next[0].y << "\n";
            curr = next;
        }
        castP.push_back(curr[0]);
    }
    
    return castP;
}

