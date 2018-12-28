//
//  polygon.h
//  assignment4
//
//  Created by Simon Åkesson on 2018-12-05.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef polygon_h
#define polygon_h


#include "point.h"
#include <vector>

struct polygon {
    int degree;
    int resolution = 100;
    std::vector<point> points;
    std::vector<int> knots;
    bool active = false;
    void addPoint(point p){points.push_back(p);}
    void addKnot(int p){knots.push_back(p);}
    int size = (int)points.size();
    void setDegree(int a){degree=a;}
    void setResolution(int res){resolution=res;}
};
#endif /* polygon_h */
