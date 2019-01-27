#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iomanip.h>
#include <time.h>

//*****************************************************************************

class Problem02
{
    int *p;
public:
    Problem02( int i )
    {
        cout << "Allocating p\n";
        p = new int;
        *p = i;
    }
    Problem02( const Problem02 &ob )
    {
        p = new int;
        *p = *ob.p;
        cout << "Copy constructor called.\n";
    }
    ~Problem02()
    {
        cout << "Freeing p\n";
        delete p;
    }
    int getval()
    {
        return *p;
    }
};
void display( Problem02 ob )
{
    cout << ob.getval() << endl;
}
void CopyConstructor01()
{
    Problem02 a(10);
    display(a);
}

//*****************************************************************************

class Problem03
{
    int *p;
public:
    Problem03( int i )
    {
        cout << "Normal constructor allocating p.\n";
        p = new int;
        *p = i;
    }
    Problem03( const Problem03 &ob )
    {
        p = new int;
        *p = *ob.p;
        cout << "Copy constructor allocating p\n";
    }
    ~Problem03()
    {
        cout << "Freeing p\n";
        delete p;
    }
};
void CopyConstructor02()
{
    Problem03 a(10);
    Problem03 b = a;
}

//*****************************************************************************

class Problem04
{
public:
    Problem04()
    {
        cout << "Normal constructor.\n";
    }
    Problem04( const Problem04 &ob )
    {
        cout << "Copy constructor.\n";
    }
};
Problem04 f4( Problem04 ob1 )
{
    cout << "03\n";
    Problem04 ob;
    cout << "04\n";
    return ob1;
}
void CopyConstructor03()
{
    cout << "00\n";
    Problem04 a;
    cout << "01\n";
    Problem04 b;
    cout << "02\n";
    a = f4(b);
}

//*****************************************************************************

class Problem01
{
    int *p;
public:
    Problem01( int i )
    {
        cout << "Allocating p\n";
        p = new int;
        *p = i;
    }
    ~Problem01()
    {
        cout << "Freeing p\n";
    }
    int getval()
    {
        return *p;
    }
};
void display( Problem01 &ob )
{
    cout << ob.getval() << endl;
}
void class10()
{
    Problem01 a(10);
    display(a);
}

//*****************************************************************************

class sample
{
    char s[80];
public:
    void show()
    {
        cout << s << endl;
    }
    void set( char *str )
    {
        strcpy( s, str );
    }
};
sample input()
{
    char instr[80];
    sample str;
    
    cout << "Enter a string: ";
    cin >> instr;
    
    str.set( instr );
    
    return str;
}
void class11()
{
    sample ob;
    
    ob = input();
    ob.show();
}

//*****************************************************************************

