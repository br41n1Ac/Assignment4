//
//  bezier.hpp
//  assignment4
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef bezier_hpp
#define bezier_hpp

#include <stdio.h>
#include "point.h"
#include <vector>


class bezier{
public:
    point deCasteljau(std::vector<point> points, double t);
    std::vector<point> deCasteljauV(std::vector<point> points, double resolution);
};


#endif /* bezier_hpp */
