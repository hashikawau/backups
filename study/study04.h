#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iomanip.h>
#include <time.h>

//*****************************************************************************

class Bclass
{
    char author[80];
public:
    void putAuthor( char *s ){ strcpy( author, s ); }
    void showAuthor(){ cout << author << endl; }
};
class Dclass : public Bclass
{
    char title[80];
public:
    void putTitle( char *num ){ strcpy( title, num ); }
    void showTitle()
    {
        cout << "Title: ";
        cout << title << endl;
    }
};
int Pointer_to_Derived01()
{
    Bclass *p;
    Bclass BOb;
    
    Dclass *dp;
    Dclass DOb;
    
    p = &BOb;
    p->putAuthor( "Tom Clancy" );
    
    p = &DOb;
    p->putAuthor( "William Shakespeare" );
    
    BOb.showAuthor();
    DOb.showAuthor();
    cout << endl;
    
    dp = &DOb;
    dp->putTitle( "The Tempest" );
    p->showAuthor();
    dp->showTitle();
    
    return 0;
}

//*****************************************************************************

class Base11
{
public:
    virtual void who()
    {
        cout << "Base\n";
    }
    void who(char *ch)
    {
        who();
        cout << ch << endl << endl;
    }
};
class First_d : public Base11
{
public:
    void who()
    {
        cout << "First derivation\n";
    }
    void who(char *ch)
    {
        who();
        cout << ch<< " first" << endl << endl;
    }
};
class Second_d : public Base11
{
public:
    void who()
    {
        cout << "Second derivation\n";
    }
    void who(char *ch)
    {
        who();
        cout << ch << " second" << endl << endl;
    }
};
int VirtualFunction01()
{
    Base11 baseObj;
    Base11 *p;
    First_d firstObj;
    Second_d secondObj;
    
    p = &baseObj;
    p->who();
    
    p = &firstObj;
    p->who();
    
    p = &secondObj;
    p->who();
    
    baseObj.who("base");
    firstObj.who("first");
    secondObj.who("second");

    return 0;
}

//*****************************************************************************

class Figure01
{
protected:
    double x, y;
public:
    void setDim( double i, double j=0 )
    {
        x = i;
        y = j;
    }
    virtual void showArea() = 0;
};
class Triangle01 : public Figure01
{
public:
    void showArea()
    {
        cout << "Triangle with height ";
        cout << x << " and base " << y;
        cout << " has an area of ";
        cout << x * 0.5 * y << ".\n";
    }
};
class Rectangle01 : public Figure01
{
public:
    void showArea()
    {
        cout << "Rectangle with dimensions ";
        cout << x << " x " << y;
        cout << " has an area of ";
        cout << x * y << ".\n";
    }
    void show()
    {
        cout << "rectangle\n";
    }
};
class Circle01 : public Figure01
{
public:
    void showArea()
    {
        cout << "Circle with radius ";
        cout << x;
        cout << " has an area of ";
        cout << 3.14 * x * x << ".\n";
    }
};
class Circle02 : public Circle01
{
public:
    void showArea()
    {
        Rectangle01  r01;
        Figure01    *pf;
        
        pf = &r01;
        pf->setDim( 10.0, 5.0 );
        pf->showArea();
    }
};
int VirtualFunction02()
{
    Figure01   *p;
    Triangle01  t;
    Rectangle01 r;
    Circle01    c;
    
    p = &t;
    p->setDim( 10.0, 5.0 );
    p->showArea();
    
    p = &r;
    p->setDim( 10.0, 5.0 );
    p->showArea();
    
    p = &c;
    p->setDim( 9.0 );
    p->showArea();
    
    Circle02 c02;
    c02.showArea();
    return 0;
}