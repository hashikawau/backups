#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iomanip.h>
#include <time.h>

//*****************************************************************************

class queue
{
    int q[100];
    int sloc, rloc;
    int who;
public:
    queue(int id)
    {
        sloc = rloc = 0;
        who = id;
        cout << "Queue " << who << " initialized.\n";
    }
    ~queue()
    {
        cout << "Queue " << who << " destroyed.\n";
    }
    void init();
    void qput( int i );
    int qget();
};
void queue::init()
{
    rloc = sloc = 0;
}
void queue::qput( int i )
{
    if( sloc == 100 )
    {
        cout << "Queue is full.\n";
        return;
    }
    sloc++;
    q[sloc] = i;
}
int queue::qget()
{
    if( rloc == sloc )
    {
        cout << "Queue underflow.\n";
        return 0;
    }
    rloc++;
    return q[rloc];
}
void class01()
{
    queue a(1), b(2);
    
    a.qput( 10 );
    b.qput( 19 );
    a.qput( 20 );
    b.qput( 1 );
    cout << "Contents of queue a: ";
    cout << a.qget() << " ";
    cout << a.qget() << endl;
    cout << "Contents of queue b: ";
    cout << b.qget() << " ";
    cout << b.qget() << endl;
}

//*****************************************************************************

class myclass
{
    int a, b;
public:
    myclass( int i, int j )
    {
        a = i;
        b = j;
    }
    int geta()
    {
        return a;
    }
    /*
    void reset()
    {
        setab(0);
    }
    */
    void setab( int i, int j )
    {
        a = i;
        b = j;
    }
    void showab()
    {
        cout << "a is " << a << endl;
        cout << "b is " << b << endl;
    }
    friend int sum( myclass x );
};
int sum( myclass x )
{
    return x.a + x.b;
}
void class02()
{
    /*
    myclass ob;
    
    ob.setab(5);
    cout << "ob after setab(5): ";
    cout << ob.geta() << " ";
    cout << ob.b << endl;
    
    ob.b = 20;
    cout << "ob after ob.b=20: ";
    cout << ob.geta() << " ";
    cout << ob.b << endl;
    
    ob.reset();
    cout << "ob after ob.reset(): ";
    cout << ob.geta() << " ";
    cout << ob.b << endl;
    */
    
    myclass n( 3, 4 );
    cout << sum(n);
}

//*****************************************************************************

enum resolution
{
    low,
    medium,
    high
};
class display
{
    int width;
    int height;
    resolution res;
public:
    void set_dim( int w, int h )
    {
        width = w;
        height = h;
    }
    void get_dim( int &w, int &h )
    {
        w = width;
        h = height;
    }
    void set_res( resolution r )
    {
        res = r;
    }
    resolution get_res()
    {
        return res;
    }
};
char names[3][7] = {
    "low",
    "medium",
    "high"
};
void class03()
{
    display display_mode[3];
    int i, w, h;
    display_mode[0].set_res( low );
    display_mode[0].set_dim( 640, 480 );
    display_mode[1].set_res( medium );
    display_mode[1].set_dim( 800, 600 );
    display_mode[2].set_res( high );
    display_mode[2].set_dim( 1600, 1200 );
    
    cout << "Available display modes:\n\n";
    
    for( i = 0; i < 3; i++ )
    {
        cout << names[display_mode[i].get_res()] << ": ";
        display_mode[i].get_dim( w, h );
        cout << w << " by " << h << endl;
    }
}

//*****************************************************************************

class samp
{
    int a;
public:
    samp( int n )
    {
        a = n;
    }
    int get_a()
    {
        return a;
    }
};
void class04()
{
    samp sampArray[4] = {
        -1,
        -2,
        -3,
        -4
    };
    
    for( int i = 0; i < 4; i++ )
    {
        cout << sampArray[i].get_a() << setw(4);
    }
    cout << endl;
}

//*****************************************************************************

class P_example
{
    int num;
public:
    void set_num( int val )
    {
        num = val;
    }
    void show_num()
    {
        cout << num << endl;
    }
};
void class05()
{
    P_example ob[2], *p;
    ob[0].set_num(10);
    ob[1].set_num(20);
    
    p = &ob[0];
    p->show_num();
    
    p++;
    p->show_num();
    
    p--;
    p->show_num();
}

//*****************************************************************************

const int IDLE = 0;
const int INUSE = 1;
class C2;
class C1
{
    int status;
public:
    void set_status( int state )
    {
        status = state;
    }
    friend int idle( C1 a, C2 b );
    int idle2( C2 b );
};
class C2
{
    int status;
public:
    void set_status( int state )
    {
        status = state;    
    }
    friend int idle( C1 a, C2 b );
    friend int C1::idle2( C2 b );
};
int idle( C1 a, C2 b )
{
    if( a.status || b.status ){ return 0; }
    else{ return 1; }
}
int C1::idle2( C2 b )
{
    if( status || b.status ){ return 0; }
    else{ return 1; }
}
void class06()
{
    C1 x;
    C2 y;
    x.set_status( IDLE );
    y.set_status( IDLE );
    if( idle(x, y) )
    {
        cout << "Screen Can Be Used.\n";
    }
    else
    {
        cout << "Pop-up In Use.\n";
    }
    
    x.set_status( INUSE );
    
    if( idle(x, y) )
    {
        cout << "Screen Can Be Used.\n";
    }
    else
    {
        cout << "Pop-up In Use.\n";
    }
    
    if( x.idle2(y) )
    {
        cout << "Screen Can Be Used.\n";
    }
    else
    {
        cout << "Pop-up In Use.\n";
    }
    
    x.set_status( INUSE );
    
    if( x.idle2(y) )
    {
        cout << "Screen Can Be Used.\n";
    }
    else
    {
        cout << "Pop-up In Use.\n";
    }
}

//*****************************************************************************

class timer
{
    int seconds;
public:
    timer( char *t )
    {
        seconds = atoi(t);
    }
    timer( int t )
    {
        seconds = t;
    }
    timer( int min, int sec )
    {
        seconds = min*60 + sec;
    }
    void run()
    {
        clock_t t1;
        t1 = clock();
        while( (clock()/CLOCKS_PER_SEC - t1/CLOCKS_PER_SEC) < seconds ){ ; }
        cout << "\a";
    }
};
void class07()
{
    timer a(10);
    a.run();
    
    cout << "Enter number of seconds: ";
    char str[80];
    cin >> str;
    timer b(str);
    b.run();
    
    cout << "Enter minutes and seconds: ";
    int min, sec;
    cin >> min >> sec;
    timer c( min, sec );
    c.run();
}

//*****************************************************************************

void class08()
{
    myclass ob1( 10, 20 ), ob2( 0, 0 );
    
    ob1.setab( 10, 20 );
    ob2.setab( 0, 0 );
    cout << "ob1 before assignment: \n";
    ob1.showab();
    cout << "ob2 before assignment: \n";
    ob2.showab();
    cout << endl;
    
    ob2 = ob1;
    
    cout << "ob1 after assignment: \n";
    ob1.showab();
    cout << "ob2 after assignment: \n";
    ob2.showab();
}

//*****************************************************************************

class OBJ
{
    int i;
public:
    void set_i( int x )
    {
        i = x;
    }
    void out_i()
    {
        cout << i << setw(4);
    }
};
void f( OBJ x )
{
    x.out_i();
    x.set_i(100);
    x.out_i();
}
void class09()
{
    OBJ o;
    
    o.set_i(10);
    f(o);
    o.out_i();
}