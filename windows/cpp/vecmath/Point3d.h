



#ifndef __Windows_cpp_vecmath_Point3d
#define __Windows_cpp_vecmath_Point3d


#include "windows\cpp\vecmath\Tuple3d.h"
#include "windows\lang\Math.h"


//===========================================================
//===========================================================
class Point3d: public Tuple3d
{
public:
    Point3d();
    Point3d(const double p[]);
    Point3d(double x, double y, double z);
    virtual ~Point3d();
    
    //Point3d& operator=(const Point3d& rhs);
    Point3d& operator+=(const Point3d& rhs);
    Point3d& operator-=(const Point3d& rhs);
    Point3d& operator*=(const Point3d& rhs);
    const bool operator==(const Point3d& rhs);
    const bool operator!=(const Point3d& rhs);
    const Point3d operator-();
    const Point3d operator+(const Point3d& obj);
    const Point3d operator-(const Point3d& obj);
    const Point3d operator*(const Point3d& obj);
    
    const double distanceSquared(const Point3d& p1);
    const double distance(const Point3d& p1);
    const double distanceL1(const Point3d& p1);
    const double distanceLinf(const Point3d& p1);
    //void project(const Point4d& p1);
};
//===========================================================
//===========================================================
Point3d::Point3d(){}
Point3d::Point3d(const double p[]): Tuple3d(p){}
Point3d::Point3d(double x, double y, double z): Tuple3d(x, y, z){}
Point3d::~Point3d(){}
//===========================================================
//===========================================================
Point3d& Point3d::operator+=(const Point3d& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
Point3d& Point3d::operator-=(const Point3d& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}
//===========================================================
//===========================================================
const bool Point3d::operator==(const Point3d& rhs)
{
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}
const bool Point3d::operator!=(const Point3d& rhs)
{
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}
//===========================================================
//===========================================================
const Point3d Point3d::operator-()
{
    return Point3d(-x, -y, -z);
}
const Point3d Point3d::operator+(const Point3d& obj)
{
    return Point3d(x +obj.x, y +obj.y, z +obj.z);
}
const Point3d Point3d::operator-(const Point3d& obj)
{
    return Point3d(x -obj.x, y -obj.y, z -obj.z);
}
//===========================================================
//===========================================================
const double Point3d::distanceSquared(const Point3d& p1)
{
    return 
        (x -p1.x) *(x -p1.x)
        + (y -p1.y) *(y -p1.y)
        + (z -p1.z) *(z -p1.z);
}
const double Point3d::distance(const Point3d& p1)
{
    return Math::sqrt(
        (x -p1.x) *(x -p1.x)
        + (y -p1.y) *(y -p1.y)
        + (z -p1.z) *(z -p1.z));
}
const double Point3d::distanceL1(const Point3d& p1)
{
    return (x -p1.x) + (y -p1.y) + (z -p1.z);
}
const double Point3d::distanceLinf(const Point3d& p1)
{
    return Math::max(
        (x -p1.x),
        Math::max((y -p1.y), (z -p1.z)));
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_vecmath_Point3d




