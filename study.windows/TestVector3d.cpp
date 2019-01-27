

#include "windows\awt\Frame.h"
#include "windows\awt\Button.h"
#include "windows\lang\String.h"

#include <iostream.h>

#include "windows\lang\Thread.h"
#include "windows\cpp\vecmath\Vector3d.h"
#include "windows\cpp\vecmath\Point3d.h"
#include "windows\cpp\media\3d\Transform3D.h"


#include "windows\awt\Polygon.h"

//===========================================================
//===========================================================
class Sphere
{
public:
    Transform3D _transform;
    Vector3d _position;
    double _radius;
    
public:
    Sphere();
    Sphere(double x, double y, double z, double r);
    ~Sphere();
    
    void set(double x, double y, double z, double r);
    void project(double& x, double& y, double& r);
    
    
};
//===========================================================
//===========================================================
Sphere::Sphere(): _position(1, 1, 1), _radius(1)
{
    _transform.setTranslation(Vector3d(2, 3, 4));
    //_transform.transpose();
    
    Transform3D t1, t2;
    t1.rotZ(3.14 /4);
    t2.rotZ(3.14 /4);
    //_transform.mul(t1, t2);
    //t1.invert();
    _transform.invert(t1);
    
    _position.set(1, 0, 0);
    cout << _position.angle(Vector3d(0, -1, 0)) /Math::PI << endl;
    
    cout << _position.x << " , ";
    cout << _position.y << " , ";
    cout << _position.z << endl;
}
Sphere::Sphere(double x, double y, double z, double r):
    _position(x, y, z), _radius(r){}
Sphere::~Sphere(){}
//===========================================================
//===========================================================
void Sphere::set(double x, double y, double z, double r)
{
    _position.set(x, y, z);
    _radius = r;
}
//===========================================================
//===========================================================
void Sphere::project(double& x, double& y, double& r)
{
    r = _radius /(1 -_position.z);
    x = _position.x /(1 -_position.z) +100;
    y = _position.y /(1 -_position.z) *-1 +100;
}
//===========================================================
//===========================================================


//===========================================================
//===========================================================
class Cube: public Transform3D
{
public:
    //Transform3D _transform;
    Point3d _vertices[8];
    Color _color[8];
    
public:
    Cube();
    ~Cube();
    
    void project(double x[], double y[]);
    
    
};
//===========================================================
//===========================================================
Cube::Cube()
{
    _vertices[0].set( 1,  1,  1);
    _vertices[1].set(-1,  1,  1);
    _vertices[2].set( 1, -1,  1);
    _vertices[3].set(-1, -1,  1);
    _vertices[4].set( 1,  1, -1);
    _vertices[5].set(-1,  1, -1);
    _vertices[6].set( 1, -1, -1);
    _vertices[7].set(-1, -1, -1);
    
    _color[0] = Color(0xFF0000);
    _color[1] = Color(0x00FF00);
    _color[2] = Color(0x0000FF);
    _color[3] = Color(0xFFFF00);
    _color[4] = Color(0xFF00FF);
    _color[5] = Color(0x00FFFF);
    _color[6] = Color(0x000000);
    _color[7] = Color(0x888888);
    
    /*
    _position.set(1, 0, 0);
    cout << _position.angle(Vector3d(0, -1, 0)) /Math::PI << endl;
    
    cout << _position.x << " , ";
    cout << _position.y << " , ";
    cout << _position.z << endl;
    */
}
Cube::~Cube(){}
//===========================================================
//===========================================================
void Cube::project(double x[], double y[])
{
    Point3d p[8];
    for(int i=0; i< 8; ++i){
        transform(_vertices[i], p[i]);
        x[i] = p[i].x *50 +200;// p[i].z;
        y[i] = p[i].y *50 +200;// p[i].z;
    }
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
class Test:
    public Frame,
    public ActionListener,
    public Thread
{
private:
    Button* _button;
    Sphere _sphere[1];
    Transform3D _transform;
    
    Cube _cube;
    int _angle[3];
    double _angled;
    
public:
    Test(const String& str);
    virtual void paint(Graphics& g);
    virtual void actionPerformed(ActionEvent& e);
    virtual void run();
    
    void teststart();
};
//===========================================================
//===========================================================
Test::Test(const String& str): Frame(str)
{
    _sphere[0] = Sphere(0, 0, 0.1, 20);
    _transform.setTranslation(Vector3d(2, -1, 0.01));
    Transform3D t1, t2;
    t1.rotX(0.1);
    t2.rotZ(3.14 /4);
    //_transform.rotZ(0.1);
    //_transform.mul(t1);
    
    _angle[0] = 0;
    _angle[1] = 1;
    _angle[2] = 2;
    _angled =0;
}
//===========================================================
//===========================================================
void Test::paint(Graphics& g)
{
    double x[3];
    double y[3];
    double r[3];
    _sphere[0].project(x[0], y[0], r[0]);
    
    g.setColor(Color(0));
    g.drawRect(x[0] -r[0]/2, y[0] -r[0]/2, r[0], r[0]);
    g.fillOval(x[0] -r[0]/2, y[0] -r[0]/2, r[0], r[0]);
    //cout << x[0] -r[0]/2 << " , ";
    //cout << y[0] -r[0]/2 << " , ";
    //cout << r[0] << endl;
    
    //cout << "cube" << endl;
    double cubex[8];
    double cubey[8];
    _cube.project(cubex, cubey);
    for(int i=0; i< 8; ++i){
        g.setColor(_cube._color[i]);
        g.fillOval(cubex[i] -4, cubey[i] -4, 8, 8);
        //cout << cubex[i] << " , " << cubey[i] << endl;
    }
    /*
    _vertices[0].set( 1,  1,  1);
    _vertices[1].set(-1,  1,  1);
    _vertices[2].set( 1, -1,  1);
    _vertices[3].set(-1, -1,  1);
    _vertices[4].set( 1,  1, -1);
    _vertices[5].set(-1,  1, -1);
    _vertices[6].set( 1, -1, -1);
    _vertices[7].set(-1, -1, -1);
    */
    g.setColor(Color(0));
    g.drawLine(cubex[0], cubey[0], cubex[1], cubey[1]);
    g.drawLine(cubex[0], cubey[0], cubex[2], cubey[2]);
    g.drawLine(cubex[0], cubey[0], cubex[4], cubey[4]);
    g.drawLine(cubex[1], cubey[1], cubex[3], cubey[3]);
    g.drawLine(cubex[1], cubey[1], cubex[5], cubey[5]);
    g.drawLine(cubex[2], cubey[2], cubex[3], cubey[3]);
    g.drawLine(cubex[2], cubey[2], cubex[6], cubey[6]);
    g.drawLine(cubex[3], cubey[3], cubex[7], cubey[7]);
    g.drawLine(cubex[4], cubey[4], cubex[5], cubey[5]);
    g.drawLine(cubex[4], cubey[4], cubex[6], cubey[6]);
    g.drawLine(cubex[5], cubey[5], cubex[7], cubey[7]);
    g.drawLine(cubex[6], cubey[6], cubex[7], cubey[7]);
}
//===========================================================
//===========================================================
void Test::actionPerformed(ActionEvent& e)
{

}
//===========================================================
//===========================================================
void Test::run()
{
    while(100){
        //_sphere[0]._position.x += 1;
        //_sphere[0]._position.y -= 1;
        //_sphere[0]._position.z += 0.01;
        //_sphere[0]._position.add(Vector3d(0, -1, 0.01));
        //_transform.transform(_sphere[0]._position);
        
        
        /*
        int count = 1000;
        _angle[0] += 1;
        _angle[1] += 2;
        _angle[2] += 3;
        for(int i=0; i< 3; ++i){
            _angle[i] %= count;
        }
        Transform3D t;
        t.rotX((_angle[0]) *0.0001);
        _cube.mul(t);
        t.rotY((_angle[1]) *0.0001);
        _cube.mul(t);
        t.rotZ((_angle[2]) *0.0001);
        _cube.mul(t);
        */
        _angled += 0.01;
        if(_angled > 3.14){ _angled =0; }
        Transform3D t;
        t.rotX(Math::sin(_angled *3) *0.02 +0.06);
        _cube.mul(t);
        t.rotY(Math::sin(_angled *2) *0.03 +0.08);
        _cube.mul(t);
        t.rotZ(Math::sin(_angled   ) *0.05 +0.05);
        _cube.mul(t);
        
        repaint();
        sleep(30);
    }
}
//===========================================================
//===========================================================
void Test::teststart()
{
    setBounds(10, 20, 600, 300);
    setVisible(true);
    start();
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR lpCmdLine,
                   int nCmdShow)
{
    Test test(GetCommandLineW());
    test.teststart();
    
    while(GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return msg.wParam;
}
//===========================================================
//===========================================================
