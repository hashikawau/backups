



#ifndef __Windows_cpp_media_3d_Transform3D
#define __Windows_cpp_media_3d_Transform3D


#include "windows\cpp\vecmath\Vector3d.h"
#include "windows\cpp\vecmath\Point3d.h"
#include "windows\lang\Math.h"


//===========================================================
//===========================================================
class Transform3D
{
private:
    double _matrix[16];
    
    
public:
    Transform3D();
    ~Transform3D();
    
    Transform3D(const Transform3D& rhs);
    Transform3D& operator=(const Transform3D& rhs);
    Transform3D& operator+=(const Transform3D& rhs);
    Transform3D& operator-=(const Transform3D& rhs);
    const bool operator==(const Transform3D& rhs);
    const bool operator!=(const Transform3D& rhs);
    const Transform3D operator-();
    const Transform3D operator+(const Transform3D& obj);
    const Transform3D operator-(const Transform3D& obj);
    
    void setIdentity();
    void setZero();
    
    void add(const Transform3D& t1);
    void add(const Transform3D& t1, const Transform3D& t2);
    void sub(const Transform3D& t1);
    void sub(const Transform3D& t1, const Transform3D& t2);
    void transpose();
    void transpose(const Transform3D& t1);
    
    void rotX(double angle);
    void rotY(double angle);
    void rotZ(double angle);
    void setTranslation(const Vector3d& trans);
    
    void invert(const Transform3D& t1);
    void invert();
    const double determinant();
    void mul(double scaler);
    void mul(double scaler, const Transform3D& t1);
    void mul(const Transform3D& t1);
    void mul(const Transform3D& t1, const Transform3D& t2);
    
    void transform(Point3d& point);
    void transform(const Point3d& point, Point3d& pointOut);
    void transform(Vector3d& normal);
    void transform(const Vector3d& normal, Vector3d& normalOut);
    
    void perspective(
        double fovx,
        double aspect,
        double zNear,
        double zFar);
    void ortho(
        double left,
        double right,
        double bottom,
        double top,
        double near,
        double far);
};
//===========================================================
//===========================================================
Transform3D::Transform3D()
{
    for(int i=0; i< 16; ++i){
        _matrix[i] =0;
    }
    for(int i=0; i< 4; ++i){
        _matrix[5 *i] =1;
    }
}
Transform3D::~Transform3D(){}
Transform3D::Transform3D(const Transform3D& rhs)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] = rhs._matrix[i];
    }
}
Transform3D& Transform3D::operator=(const Transform3D& rhs)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] = rhs._matrix[i];
    }
    return *this;
}
//===========================================================
//===========================================================
void Transform3D::setIdentity()
{
    for(int i=0; i< 16; ++i){
        _matrix[i] =0;
    }
    for(int i=0; i< 4; ++i){
        _matrix[5 *i] =1;
    }
}
void Transform3D::setZero()
{
    for(int i=0; i< 16; ++i){
        _matrix[i] =0;
    }
}
//===========================================================
//===========================================================
void Transform3D::add(const Transform3D& t1)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] += t1._matrix[i];
    }
}
void Transform3D::add(const Transform3D& t1, const Transform3D& t2)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] = t1._matrix[i] + t2._matrix[i];
    }
}
//===========================================================
//===========================================================
void Transform3D::sub(const Transform3D& t1)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] -= t1._matrix[i];
    }
}
void Transform3D::sub(const Transform3D& t1, const Transform3D& t2)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] = t1._matrix[i] - t2._matrix[i];
    }
}
//===========================================================
//===========================================================
void Transform3D::transpose()
{
    double temp;
    for(int i=0; i< 3; ++i){
        for(int j= i+1; j< 4; ++j){
            temp = _matrix[4 *i +j];
            _matrix[4 *i +j] = _matrix[4 *j +i];
            _matrix[4 *j +i] = temp;
        }
    }
}
void Transform3D::transpose(const Transform3D& t1){}
//===========================================================
//===========================================================
void Transform3D::rotX(double angle)
{
    setIdentity();
    _matrix[5] = _matrix[10] = Math::cos(angle);
    _matrix[9] = Math::sin(angle);
    _matrix[6] = -_matrix[9];
}
void Transform3D::rotY(double angle)
{
    setIdentity();
    _matrix[0] = _matrix[10] = Math::cos(angle);
    _matrix[2] = Math::sin(angle);
    _matrix[8] = -_matrix[2];
}
void Transform3D::rotZ(double angle)
{
    setIdentity();
    _matrix[0] = _matrix[5] = Math::cos(angle);
    _matrix[4] = Math::sin(angle);
    _matrix[1] = -_matrix[4];
}
void Transform3D::setTranslation(const Vector3d& trans)
{
    setIdentity();
    double d[3];
    trans.get(d);
    _matrix[3] = d[0];
    _matrix[7] = d[1];
    _matrix[11] = d[2];
}
//===========================================================
//===========================================================
void Transform3D::invert(const Transform3D& t1)
{
    double copy[16];
    for(int i=0; i< 16; ++i){
        copy[i] = t1._matrix[i];
        _matrix[i] =0;
    }
    for(int i=0; i< 4; ++i){
        _matrix[5*i] =1;
    }
    
    for(int r=0; r< 4; ++r){
        
        double diagonal = copy[4 *r +r];
        for(int j=0; j< 4; ++j){
            _matrix[4 *r +j] /= diagonal;
            copy[4 *r +j] /= diagonal;
        }
        
        for(int i=0; i< r; ++i){
            double c = copy[4 *i +r];
            for(int j= 0; j< 4; ++j){
                _matrix[4 *i +j] -= _matrix[4 *r +j] *c;
                copy[4 *i +j] -= copy[4 *r +j] *c;
            }
        }
        for(int i= r+1; i< 4; ++i){
            double c = copy[4 *i +r];
            for(int j= 0; j< 4; ++j){
                _matrix[4 *i +j] -= _matrix[4 *r +j] *c;
                copy[4 *i +j] -= copy[4 *r +j] *c;
            }
        }
    }
}
void Transform3D::invert()
{
    double copy[16];
    for(int i=0; i< 16; ++i){
        copy[i] = _matrix[i];
        _matrix[i] =0;
    }
    for(int i=0; i< 4; ++i){
        _matrix[5*i] =1;
    }
    
    for(int r=0; r< 4; ++r){
        
        double diagonal = copy[4 *r +r];
        for(int j=0; j< 4; ++j){
            _matrix[4 *r +j] /= diagonal;
            copy[4 *r +j] /= diagonal;
        }
        
        for(int i=0; i< r; ++i){
            double c = copy[4 *i +r];
            for(int j= 0; j< 4; ++j){
                _matrix[4 *i +j] -= _matrix[4 *r +j] *c;
                copy[4 *i +j] -= copy[4 *r +j] *c;
            }
        }
        for(int i= r+1; i< 4; ++i){
            double c = copy[4 *i +r];
            for(int j= 0; j< 4; ++j){
                _matrix[4 *i +j] -= _matrix[4 *r +j] *c;
                copy[4 *i +j] -= copy[4 *r +j] *c;
            }
        }
    }
}
const double Transform3D::determinant()
{
    return 0
        + _matrix[0] *(0
                + _matrix[5] *(0
                    + _matrix[10] *_matrix[15]
                    - _matrix[11] *_matrix[14])
                - _matrix[6] *(0
                    + _matrix[9] *_matrix[15]
                    - _matrix[11] *_matrix[13])
                + _matrix[7] *(0
                    + _matrix[9] *_matrix[14]
                    - _matrix[10] *_matrix[13]))
        - _matrix[1] *(0
                + _matrix[4] *(0
                    + _matrix[10] *_matrix[15]
                    - _matrix[11] *_matrix[14])
                - _matrix[6] *(0
                    + _matrix[8] *_matrix[15]
                    - _matrix[11] *_matrix[12])
                + _matrix[7] *(0
                    + _matrix[8] *_matrix[14]
                    - _matrix[10] *_matrix[12]))
        + _matrix[2] *(0
                + _matrix[4] *(0
                    + _matrix[9] *_matrix[15]
                    - _matrix[11] *_matrix[13])
                - _matrix[5] *(0
                    + _matrix[8] *_matrix[15]
                    - _matrix[11] *_matrix[12])
                + _matrix[7] *(0
                    + _matrix[8] *_matrix[13]
                    - _matrix[9] *_matrix[12]))
        - _matrix[3] *(0
                + _matrix[4] *(0
                    + _matrix[9] *_matrix[14]
                    - _matrix[10] *_matrix[13])
                - _matrix[5] *(0
                    + _matrix[8] *_matrix[14]
                    - _matrix[10] *_matrix[12])
                + _matrix[6] *(0
                    + _matrix[8] *_matrix[13]
                    - _matrix[9] *_matrix[12]));
}
//===========================================================
//===========================================================
void Transform3D::mul(double scaler)
{
    for(int i=0; i< 16; ++i){
        _matrix[i] *= scaler;
    }
}
void Transform3D::mul(double scaler, const Transform3D& t1)
{
    double copy[16];
    for(int i=0; i< 16; ++i){
        copy[i] = _matrix[i];
    }
    for(int i=0; i< 4; ++i){
        for(int j=0; j< 4; ++j){
            _matrix[4 *i +j] = 0;
            for(int a=0; a< 4; ++a){
                _matrix[4 *i +j] += copy[4 *i +a] *t1._matrix[4 *a +j];
            }
            _matrix[4 *i +j] *= scaler;
        }
    }
}
void Transform3D::mul(const Transform3D& t1)
{
    double copy[16];
    for(int i=0; i< 16; ++i){
        copy[i] = _matrix[i];
    }
    for(int i=0; i< 4; ++i){
        for(int j=0; j< 4; ++j){
            _matrix[4 *i +j] = 0;
            for(int a=0; a< 4; ++a){
                _matrix[4 *i +j] += copy[4 *i +a] *t1._matrix[4 *a +j];
            }
        }
    }
}
void Transform3D::mul(const Transform3D& t1, const Transform3D& t2)
{
    for(int i=0; i< 4; ++i){
        for(int j=0; j< 4; ++j){
            _matrix[4 *i +j] = 0;
            for(int a=0; a< 4; ++a){
                _matrix[4 *i +j] += t1._matrix[4 *i +a] *t2._matrix[4 *a +j];
            }
        }
    }
}
//===========================================================
//===========================================================
void Transform3D::transform(Point3d& point)
{
    double copy[4];
    double temp[3];
    point.get(copy);
    copy[3] = 1;
    for(int i=0; i< 3; ++i){
        temp[i] =0;
        for(int j=0; j< 4; ++j){
            temp[i] += _matrix[4 *i +j] *copy[j];
        }
        temp[i] += _matrix[4 *i +3];
    }
    point.set(temp[0], temp[1], temp[2]);
}
void Transform3D::transform(const Point3d& point, Point3d& pointOut)
{
    double copy[4];
    double temp[3];
    point.get(copy);
    copy[3] = 1;
    for(int i=0; i< 3; ++i){
        temp[i] =0;
        for(int j=0; j< 4; ++j){
            temp[i] += _matrix[4 *i +j] *copy[j];
        }
        temp[i] += _matrix[4 *i +3];
    }
    pointOut.set(temp[0], temp[1], temp[2]);
}
//===========================================================
//===========================================================
void Transform3D::transform(Vector3d& normal)
{
    double copy[3];
    double temp[3];
    normal.get(copy);
    for(int i=0; i< 3; ++i){
        temp[i] =0;
        for(int j=0; j< 3; ++j){
            temp[i] += _matrix[4 *i +j] *copy[j];
        }
        temp[i] += _matrix[4 *i +3];
    }
    normal.set(temp[0], temp[1], temp[2]);
/*
//======================================
for(int i=0; i< 4; ++i){
    for(int j=0; j< 4; ++j){
        cout << _matrix[4 *i +j] << " ";
    }
    cout << endl;
}
cout << endl;
//======================================
*/
}
void Transform3D::transform(const Vector3d& normal, Vector3d& normalOut)
{
    double copy[3];
    double temp[3];
    normal.get(copy);
    for(int i=0; i< 3; ++i){
        temp[i] =0;
        for(int j=0; j< 3; ++j){
            temp[i] += _matrix[4 *i +j] *copy[j];
        }
        temp[i] += _matrix[4 *i +3];
    }
    normalOut.set(temp[0], temp[1], temp[2]);
}
//===========================================================
//===========================================================
void Transform3D::perspective(
    double fovx,
    double aspect,
    double zNear,
    double zFar)
{
    
}
void Transform3D::ortho(
    double left,
    double right,
    double bottom,
    double top,
    double near,
    double far)
{
    
}
//===========================================================
//===========================================================



#endif //ifndef __Windows_cpp_media_3d_Transform3D




