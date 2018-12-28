//
//  bspline.cpp
//  assignment4
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "bspline.h"



int bspline::calcBigI(float u,std::vector<int> knots){
    int number = 0;
    for(int bigI = 0; bigI <= knots.size();bigI++){
        if(knots[bigI] <= u && knots[bigI+1] > u){
            number = bigI;
            break;
        }
    }
    return number;
}

std::vector<float> bspline::genU(int k, int n, int resolution,std::vector<int>knots){
    std::vector<float> uVal;
    float delta = (float)(knots[n+1]-knots[k-1])/resolution;
    for(float i = knots[k-1]; i < knots[n+1]; i += delta){
        uVal.push_back(i);
    }
    return uVal;
}

std::vector<point> bspline::dBoor(int k, int n, std::vector<point>points,int resolution, int number, std::vector<int> knots){
    int rows = n+1;
    std::vector<float> uVal = genU(k, n, resolution,knots);
    std::vector<point> splinePoints;
    int bigI=0;
    int nextSeg=number;
    std::vector<std::vector<point> > splineMat(rows,std::vector<point>());
    int next=calcBigI(uVal[0],knots);
    for(int u = 0; u<=uVal.size();u++){
        bigI = calcBigI(uVal[u],knots);
        if(bigI != next){
            break;
            //   std::cout<<"when increase\n";
        }
        next = bigI;
        for(int temp = 0; temp < k;temp++){
            splineMat[0].push_back(points[temp+nextSeg]);
        }
        for(int j = 1; j <= k-1; j++){
            for(int i = bigI-k+1; i <= bigI-j; i++){
                float factor1 = (knots[i+k]-uVal[u])/(knots[i+k] - knots[i+j]);
                float factor2 = (uVal[u]-knots[i+j])/(knots[i+k] - knots[i+j]);
                splineMat[j].push_back(*new point(factor1*splineMat[j-1][i].x+factor2*splineMat[j-1][i+1].x,factor1*splineMat[j-1][i].y+factor2*splineMat[j-1][i+1].y));
            }
        }
        if(splineMat[k-1].front().x != 0){
            splinePoints.push_back(splineMat[k-1].front());
        } else{
            break;
        }
        for(int t = 0; t < rows;t++){
            splineMat[t].clear();
        }
    }
    return splinePoints;
}

std::vector<point> bspline::dbhHelper(int k, int n, std::vector<point>points,int resolution,std::vector<int> knots){
    std::vector<point>collect;
    for(int i = 0; i <= n+1-k;i++){
        std::vector<point> temp = dBoor(k, n, points, resolution, i,knots);
        for(int j=0; j<temp.size();j++){
            collect.push_back(temp[j]);
        }
    }
    return collect;
}

