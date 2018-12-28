//
//  bspline.h
//  assignment4
//
//  Created by Simon Åkesson on 2018-11-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef bspline_h
#define bspline_h
#include "point.h"
#include <vector>
//extern vector<int> knots;

class bspline{
    
public:
    std::vector<point> dbhHelper(int k, int n, std::vector<point>points,int resolution,std::vector<int> knots);
    
private:
    int calcBigI(float u,std::vector<int> knots);
    std::vector<float> genU(int k, int n, int resolution,std::vector<int>knots);
    std::vector<point> dBoor(int k, int n, std::vector<point>points,int resolution, int number, std::vector<int> knots);

};


#endif /* bspline_h */
