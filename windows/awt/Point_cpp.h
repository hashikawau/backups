

#ifndef __Windows_awt_Point_cpp
#define __Windows_awt_Point_cpp


//===========================================================
//===========================================================
#include "Point.h"
//===========================================================
//===========================================================
Point2D::Point2D(){}
Point2D::~Point2D(){}
//===========================================================
//===========================================================
Point::Point(): x(0), y(0){}
Point::Point(int x, int y): x(x), y(y){}
Point::~Point(){}
//===========================================================
//===========================================================
Dimension2D::Dimension2D(){}
Dimension2D::~Dimension2D(){}
//===========================================================
//===========================================================
Dimension::Dimension(): width(0), height(0){}
Dimension::Dimension(int width, int height): width(width), height(height){}
Dimension::~Dimension(){}
//===========================================================
//===========================================================
Rectangle2D::Rectangle2D(){}
Rectangle2D::~Rectangle2D(){}
//===========================================================
//===========================================================
Rectangle::Rectangle(): x(0), y(0), width(0), height(0){}
Rectangle::Rectangle(int x, int y, int width, int height):
    x(x), y(y), width(width), height(height)
{}
Rectangle::~Rectangle(){}
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Point_cpp

