



#ifndef __Windows_cpp_vecmath_Tuple3d
#define __Windows_cpp_vecmath_Tuple3d


//===========================================================
//===========================================================
class Tuple3d
{
private:
    
public:
    double x;
    double y;
    double z;
    
    Tuple3d();
    Tuple3d(const double t[]);
    Tuple3d(double x, double y, double z);
    //Tuple3d(const Tuple3d& rhs);
    virtual ~Tuple3d() =0;
    
    void set(const double t[]);
    void set(double x, double y, double z);
    void get(double t[]) const;
    void clamp(double min, double max);
    void clamp(double min, double max, const Tuple3d& t);
    void clampMax(double max);
    void clampMax(double max, const Tuple3d& t);
    void clampMin(double min);
    void clampMin(double min, const Tuple3d& t);
    const bool equals(const Tuple3d& t1);
    const bool epsilonEquals(const Tuple3d& t1, double epsilon);
    
    void absolute();
    void absolute(const Tuple3d& t);
    void negate();
    void negate(const Tuple3d& t);
    void add(const Tuple3d& t1);
    void add(const Tuple3d& t1, const Tuple3d& t2);
    void sub(const Tuple3d& t1);
    void sub(const Tuple3d& t1, const Tuple3d& t2);
    void scale(double s);
    void scale(double s, const Tuple3d& t1);
    void interpolate(const Tuple3d& t1, double alpha);
    void interpolate(const Tuple3d& t1, const Tuple3d& t2, double alpha);
};
//===========================================================
//===========================================================
Tuple3d::Tuple3d(): x(0), y(0), z(0){}
Tuple3d::Tuple3d(const double t[]): x(t[0]), y(t[1]), z(t[2]){}
Tuple3d::Tuple3d(double x, double y, double z): x(x), y(y), z(z){}
//Tuple3d::Tuple3d(const Tuple3d& rhs): x(rhs.x), y(rhs.y), z(rhs.z){}
Tuple3d::~Tuple3d(){}
//===========================================================
//===========================================================
void Tuple3d::set(const double t[])
{
    this->x = t[0];
    this->y = t[1];
    this->z = t[2];
}
void Tuple3d::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Tuple3d::get(double t[]) const
{
    t[0] = x;
    t[1] = y;
    t[2] = z;
}
//===========================================================
//===========================================================
void Tuple3d::clamp(double min, double max)
{
    x = x <min?
        min:
        x >max?
            max:
            x;
    y = y <min?
        min:
        y >max?
            max:
            y;
    z = z <min?
        min:
        z >max?
            max:
            z;
}
void Tuple3d::clamp(double min, double max, const Tuple3d& t)
{
    x = t.x <min?
        min:
        t.x >max?
            max:
            t.x;
    y = t.y <min?
        min:
        t.y >max?
            max:
            t.y;
    z = t.z <min?
        min:
        t.z >max?
            max:
            t.z;
}
//===========================================================
//===========================================================
void Tuple3d::clampMax(double max)
{
    x = x >max?
        max:
        x;
    y = y >max?
        max:
        y;
    z = z >max?
        max:
        z;
}
void Tuple3d::clampMax(double max, const Tuple3d& t)
{
    x = t.x >max?
        max:
        t.x;
    y = t.y >max?
        max:
        t.y;
    z = t.z >max?
        max:
        t.z;
}
//===========================================================
//===========================================================
void Tuple3d::clampMin(double min)
{
    x = x <min?
        min:
        x;
    y = y <min?
        min:
        y;
    z = z <min?
        min:
        z;
}
void Tuple3d::clampMin(double min, const Tuple3d& t)
{
    x = t.x <min?
        min:
        t.x;
    y = t.y <min?
        min:
        t.y;
    z = t.z <min?
        min:
        t.z;
}
//===========================================================
//===========================================================
const bool Tuple3d::equals(const Tuple3d& t1)
{
    return
        (x -t1.x == 0)
        && (y -t1.y == 0)
        && (z -t1.z == 0);
}
const bool Tuple3d::epsilonEquals(const Tuple3d& t1, double epsilon)
{
    return
        (x -t1.x <= epsilon)
        && (y -t1.y <= epsilon)
        && (z -t1.z <= epsilon);
}
//===========================================================
//===========================================================
void Tuple3d::absolute()
{
    x *= x <0? -1: 1;
    y *= y <0? -1: 1;
    z *= z <0? -1: 1;
}
void Tuple3d::absolute(const Tuple3d& t)
{
    x = t.x <0? t.x *-1: t.x;
    y = t.y <0? t.y *-1: t.y;
    z = t.z <0? t.z *-1: t.z;
}
//===========================================================
//===========================================================
void Tuple3d::negate()
{
    x *= -1;
    y *= -1;
    z *= -1;
}
void Tuple3d::negate(const Tuple3d& t)
{
    x = t.x *-1;
    y = t.y *-1;
    z = t.z *-1;
}
//===========================================================
//===========================================================
void Tuple3d::add(const Tuple3d& t1)
{
    x += t1.x;
    y += t1.y;
    z += t1.z;
}
void Tuple3d::add(const Tuple3d& t1, const Tuple3d& t2)
{
    x = t1.x + t2.x;
    y = t1.y + t2.y;
    z = t1.z + t2.z;
}
//===========================================================
//===========================================================
void Tuple3d::sub(const Tuple3d& t1)
{
    x -= t1.x;
    y -= t1.y;
    z -= t1.z;
}
void Tuple3d::sub(const Tuple3d& t1, const Tuple3d& t2)
{
    x = t1.x - t2.x;
    y = t1.y - t2.y;
    z = t1.z - t2.z;
}
//===========================================================
//===========================================================
void Tuple3d::scale(double s)
{
    x *= s;
    y *= s;
    z *= s;
}
void Tuple3d::scale(double s, const Tuple3d& t1)
{
    x = s * t1.x;
    y = s * t1.y;
    z = s * t1.z;
}
//===========================================================
//===========================================================
void Tuple3d::interpolate(const Tuple3d& t1, double alpha)
{
    x = (1 -alpha) *x + alpha *t1.x;
    y = (1 -alpha) *y + alpha *t1.y;
    z = (1 -alpha) *z + alpha *t1.z;
}
void Tuple3d::interpolate(const Tuple3d& t1, const Tuple3d& t2, double alpha)
{
    x = (1 -alpha) *t1.x + alpha *t2.x;
    y = (1 -alpha) *t1.y + alpha *t2.y;
    z = (1 -alpha) *t1.z + alpha *t2.z;
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_vecmath_Tuple3d




