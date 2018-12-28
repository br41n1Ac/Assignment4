//
//  DrawLine.cpp
//  assignment4
//
//  Created by Simon Åkesson on 2018-12-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <stdio.h>
#include "DrawLine.h"


void DrawLine::makePix(int x,int y, float red, float green, float blue){
    int pixLoc = (x * 3) + (y * height * 3);
    if(x<=width-1 && y <= height-1 && x >= 0 && y >= 0){
        PixelBuffer[pixLoc + 0] = red;
        PixelBuffer[pixLoc + 1] = green;
        PixelBuffer[pixLoc + 2] = blue;
    }
}


void DrawLine::drawDDA(point p1, point p2,int r, int g, int b){
    float deltax = p2.x-p1.x, deltay = p2.y-p1.y, x = p1.x, y = p1.y, dist=0, incy, incx;
    if(fabs(deltax) > fabs(deltay)){
        dist = fabs(deltax);
    } else{
        dist  = fabs(deltay);
    }
    incx = deltax/dist;
    incy = deltay/dist;
    makePix(p1.x, p1.y, r, g, b);
    makePix(p2.x, p2.y, r, g, b);
    for(int i=0; i<dist; i++){
        x+=incx;
        y+=incy;
        makePix(x, y, r, g, b);
    }
}
