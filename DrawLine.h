//
//  DrawLine.h
//  assignment4
//
//  Created by Simon Åkesson on 2018-11-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#ifndef DrawLine_h
#define DrawLine_h
#include <math.h>
#include "point.h"
extern int height;
extern int width;
extern float* PixelBuffer;
//turning on pixels

class DrawLine{
public:
    void drawDDA(point p1, point p2,int r, int g, int b);
private:
    void makePix(int x,int y, float red, float green, float blue);
    
};



#endif /* DrawLine_h */
