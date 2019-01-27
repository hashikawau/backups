

#ifndef __Windows_awt_Polygon_cpp
#define __Windows_awt_Polygon_cpp


//===========================================================
//===========================================================
#include "Polygon.h"
//===========================================================
//===========================================================
Polygon::Polygon()
{
    _capacity = 8;
    npoints = 0;
    xpoints = new int[_capacity];
    ypoints = new int[_capacity];
}
Polygon::Polygon(int xpoints[], int ypoints[], int npoints)
{
    _capacity = npoints;
    this->npoints = npoints;
    this->xpoints = new int[_capacity];
    this->ypoints = new int[_capacity];
    for(int i=0; i< npoints; ++i){
        this->xpoints[i] = xpoints[i];
        this->ypoints[i] = ypoints[i];
    }
}
Polygon::~Polygon()
{
    delete [] xpoints;
    delete [] ypoints;
}
//===========================================================
//===========================================================
void Polygon::addPoint(int x, int y)
{
    if(_capacity >= npoints){
        _capacity *= 2;
        int* newx = new int[_capacity];
        int* newy = new int[_capacity];
        
        for(int i= 0; i< npoints; ++i){
            newx[i] = xpoints[i];
            newy[i] = ypoints[i];
        }
        delete [] xpoints;
        delete [] ypoints;
        xpoints = newx;
        ypoints = newy;
    }
    
    xpoints[npoints] = x;
    ypoints[npoints] = y;
    ++npoints;
}
void Polygon::translate(int deltaX, int deltaY)
{
    for(int i= 0; i< npoints; ++i){
        xpoints[i] += deltaX;
        ypoints[i] += deltaY;
    }
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Polygon_cpp

