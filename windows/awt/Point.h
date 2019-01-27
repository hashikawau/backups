

#ifndef __Windows_awt_Point
#define __Windows_awt_Point


//===========================================================
//===========================================================
class Point2D
{
protected:
    Point2D();
    
public:
    virtual ~Point2D() =0;
    //virtual double getX() =0;
    //virtual double getY() =0;
};
//===========================================================
//===========================================================
class Point: public Point2D
{
public:
    int x;
    int y;
    
    Point();
    Point(int x, int y);
    ~Point();
    //virtual double getX();
    //virtual dobule getY();
};
//===========================================================
//===========================================================
class Dimension2D
{
protected:
    Dimension2D();
    
public:
    virtual ~Dimension2D() =0;
};
//===========================================================
//===========================================================
class Dimension: public Dimension2D
{
public:
    int width;
    int height;
    
    Dimension();
    Dimension(int width, int height);
    ~Dimension();
};
//===========================================================
//===========================================================
class Rectangle2D
{
protected:
    Rectangle2D();
    
public:
    virtual ~Rectangle2D() =0;
};
//===========================================================
//===========================================================
class Rectangle: public Rectangle2D
{
public:
    int x;
    int y;
    int width;
    int height;
    
    Rectangle();
    Rectangle(int x, int y, int width, int height);
    ~Rectangle();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_awt_Point

