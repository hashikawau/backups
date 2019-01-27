



#ifndef __Windows_cpp_vecmath_Tuple3f
#define __Windows_cpp_vecmath_Tuple3f


//===========================================================
//===========================================================
class Tuple3f
{
private:
    
public:
    float x;
    float y;
    float z;
    
    Tuple3f();
    Tuple3f(const float t[]);
    Tuple3f(float x, float y, float z);
    //Tuple3f(const Tuple3f& rhs);
    virtual ~Tuple3f() =0;
    
    void set(const float t[]);
    void set(float x, float y, float z);
    void get(float t[]) const;
    void clamp(float min, float max);
    void clamp(float min, float max, const Tuple3f& t);
    void clampMax(float max);
    void clampMax(float max, const Tuple3f& t);
    void clampMin(float min);
    void clampMin(float min, const Tuple3f& t);
    const bool equals(const Tuple3f& t1);
    const bool epsilonEquals(const Tuple3f& t1, float epsilon);
    
    void absolute();
    void absolute(const Tuple3f& t);
    void negate();
    void negate(const Tuple3f& t);
    void add(const Tuple3f& t1);
    void add(const Tuple3f& t1, const Tuple3f& t2);
    void sub(const Tuple3f& t1);
    void sub(const Tuple3f& t1, const Tuple3f& t2);
    void scale(float s);
    void scale(float s, const Tuple3f& t1);
    void interpolate(const Tuple3f& t1, float alpha);
    void interpolate(const Tuple3f& t1, const Tuple3f& t2, float alpha);
};
//===========================================================
//===========================================================
Tuple3f::Tuple3f(): x(0), y(0), z(0){}
Tuple3f::Tuple3f(const float t[]): x(t[0]), y(t[1]), z(t[2]){}
Tuple3f::Tuple3f(float x, float y, float z): x(x), y(y), z(z){}
//Tuple3f::Tuple3f(const Tuple3f& rhs): x(rhs.x), y(rhs.y), z(rhs.z){}
Tuple3f::~Tuple3f(){}
//===========================================================
//===========================================================
void Tuple3f::set(const float t[])
{
    this->x = t[0];
    this->y = t[1];
    this->z = t[2];
}
void Tuple3f::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Tuple3f::get(float t[]) const
{
    t[0] = x;
    t[1] = y;
    t[2] = z;
}
//===========================================================
//===========================================================
void Tuple3f::clamp(float min, float max)
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
void Tuple3f::clamp(float min, float max, const Tuple3f& t)
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
void Tuple3f::clampMax(float max)
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
void Tuple3f::clampMax(float max, const Tuple3f& t)
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
void Tuple3f::clampMin(float min)
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
void Tuple3f::clampMin(float min, const Tuple3f& t)
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
const bool Tuple3f::equals(const Tuple3f& t1)
{
    return
        (x -t1.x == 0)
        && (y -t1.y == 0)
        && (z -t1.z == 0);
}
const bool Tuple3f::epsilonEquals(const Tuple3f& t1, float epsilon)
{
    return
        (x -t1.x <= epsilon)
        && (y -t1.y <= epsilon)
        && (z -t1.z <= epsilon);
}
//===========================================================
//===========================================================
void Tuple3f::absolute()
{
    x *= x <0? -1: 1;
    y *= y <0? -1: 1;
    z *= z <0? -1: 1;
}
void Tuple3f::absolute(const Tuple3f& t)
{
    x = t.x <0? t.x *-1: t.x;
    y = t.y <0? t.y *-1: t.y;
    z = t.z <0? t.z *-1: t.z;
}
//===========================================================
//===========================================================
void Tuple3f::negate()
{
    x *= -1;
    y *= -1;
    z *= -1;
}
void Tuple3f::negate(const Tuple3f& t)
{
    x = t.x *-1;
    y = t.y *-1;
    z = t.z *-1;
}
//===========================================================
//===========================================================
void Tuple3f::add(const Tuple3f& t1)
{
    x += t1.x;
    y += t1.y;
    z += t1.z;
}
void Tuple3f::add(const Tuple3f& t1, const Tuple3f& t2)
{
    x = t1.x + t2.x;
    y = t1.y + t2.y;
    z = t1.z + t2.z;
}
//===========================================================
//===========================================================
void Tuple3f::sub(const Tuple3f& t1)
{
    x -= t1.x;
    y -= t1.y;
    z -= t1.z;
}
void Tuple3f::sub(const Tuple3f& t1, const Tuple3f& t2)
{
    x = t1.x - t2.x;
    y = t1.y - t2.y;
    z = t1.z - t2.z;
}
//===========================================================
//===========================================================
void Tuple3f::scale(float s)
{
    x *= s;
    y *= s;
    z *= s;
}
void Tuple3f::scale(float s, const Tuple3f& t1)
{
    x = s * t1.x;
    y = s * t1.y;
    z = s * t1.z;
}
//===========================================================
//===========================================================
void Tuple3f::interpolate(const Tuple3f& t1, float alpha)
{
    x = (1 -alpha) *x + alpha *t1.x;
    y = (1 -alpha) *y + alpha *t1.y;
    z = (1 -alpha) *z + alpha *t1.z;
}
void Tuple3f::interpolate(const Tuple3f& t1, const Tuple3f& t2, float alpha)
{
    x = (1 -alpha) *t1.x + alpha *t2.x;
    y = (1 -alpha) *t1.y + alpha *t2.y;
    z = (1 -alpha) *t1.z + alpha *t2.z;
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_vecmath_Tuple3f




