



#ifndef __Windows_cpp_vecmath_Vector3d
#define __Windows_cpp_vecmath_Vector3d


#include "windows\cpp\vecmath\Tuple3d.h"
#include "windows\lang\Math.h"


//===========================================================
//===========================================================
class Vector3d: public Tuple3d
{
public:
    Vector3d();
    Vector3d(const double v[]);
    Vector3d(double x, double y, double z);
    virtual ~Vector3d();
    
    //Vector3d& operator=(const Vector3d& rhs);
    Vector3d& operator+=(const Vector3d& rhs);
    Vector3d& operator-=(const Vector3d& rhs);
    const bool operator==(const Vector3d& rhs);
    const bool operator!=(const Vector3d& rhs);
    const Vector3d operator-();
    const Vector3d operator+(const Vector3d& obj);
    const Vector3d operator-(const Vector3d& obj);
    
    void cross(const Vector3d v1, const Vector3d v2);
    void normalize(const Vector3d v1);
    void normalize();
    const double dot(const Vector3d v1) const;
    const double lengthSquared() const;
    const double length() const;
    const double angle(const Vector3d v1) const;
};
//===========================================================
//===========================================================
Vector3d::Vector3d(){}
Vector3d::Vector3d(const double v[]): Tuple3d(v){}
Vector3d::Vector3d(double x, double y, double z): Tuple3d(x, y, z){}
Vector3d::~Vector3d(){}
//===========================================================
//===========================================================
Vector3d& Vector3d::operator+=(const Vector3d& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}
Vector3d& Vector3d::operator-=(const Vector3d& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}
//===========================================================
//===========================================================
const bool Vector3d::operator==(const Vector3d& rhs)
{
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}
const bool Vector3d::operator!=(const Vector3d& rhs)
{
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}
//===========================================================
//===========================================================
const Vector3d Vector3d::operator-()
{
    return Vector3d(-x, -y, -z);
}
const Vector3d Vector3d::operator+(const Vector3d& obj)
{
    return Vector3d(x +obj.x, y +obj.y, z +obj.z);
}
const Vector3d Vector3d::operator-(const Vector3d& obj)
{
    return Vector3d(x -obj.x, y -obj.y, z -obj.z);
}
//===========================================================
//===========================================================
void Vector3d::cross(const Vector3d v1, const Vector3d v2)
{
    x = v1.y *v2.z - v1.z *v2.y;
    y = v1.z *v2.x - v1.x *v2.z;
    z = v1.x *v2.y - v1.y *v2.x;
}
//===========================================================
//===========================================================
void Vector3d::normalize(const Vector3d v1)
{
    double length = Math::sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
    x = v1.x /length;
    y = v1.y /length;
    z = v1.z /length;
}
void Vector3d::normalize()
{
    double length = Math::sqrt(x*x + y*y + z*z);
    x /= length;
    y /= length;
    z /= length;
}
//===========================================================
//===========================================================
const double Vector3d::dot(const Vector3d v1) const
{
    return x *v1.x + y *v1.y + z *v1.z;
}
const double Vector3d::lengthSquared() const
{
    return x*x + y*y + z*z;
}
const double Vector3d::length() const
{
    return Math::sqrt(x*x + y*y + z*z);
}
const double Vector3d::angle(const Vector3d v1) const
{
    double i = y *v1.z - z *v1.y;
    double j = z *v1.x - x *v1.z;
    double k = x *v1.y - y *v1.x;
    double dot = x *v1.x + y *v1.y + z *v1.z;
    double rad = Math::atan(
        Math::sqrt(i*i + j*j + k*k)
        / (x *v1.x + y *v1.y + z *v1.z));
    
    return dot <0?
        rad + Math::PI:
        rad;
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_vecmath_Vector3d




