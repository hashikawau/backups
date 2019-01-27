#include <iostream.h>
#include <fstream.h>
#include <math.h>
#include <stdlib.h>
//#include "header\header.h"
#include "header\dynamics.h"

class m
{
public:
    int val1, val2;
    m()
    {
        val1 = 1;
        val2 = 2;
        cout << val1 << "  ";
        cout << val2 << endl;
    }
    m(const m &obj)
    {
        cout << "copy constructor\n";
    }
    ~m()
    {
        cout << "destructor\n";
    }
    void getval()
    {
        cout << val1 << endl;
    }
    void set(int i)
    {
        val1 = i;
    }
};
/*
void display(m &obj)
{
    obj.getval();
}

m input(int i)
{
    m obj(0);
    obj.set(i);
    
    return obj;
}
*/

class kk
{
    static int ikk;
public:
    kk()
    {
        ikk++;
        cout << "KKcreated  " << ikk << endl;
    }
    kk(int i)
    {
        cout << "KKcreated\n";
        ikk = 0;
        show();
    }
    ~kk()
    {
        ikk--;
        cout << "KKDeleted  " << ikk << endl;
    }
    void show()
    {
        cout << ikk << endl;
        ikk++;
    }
};
int kk::ikk;

/*
class ll
{
    kk *pkk;
public:
    ll()
    {
        cout << "LLcreated\n";
        pkk = new kk [3];
    }
    ~ll()
    {
        delete [] pkk;
        cout << "LLdeleted\n";
    }
};
*/


class mm
{
public:
    int i;
    mm(int j)
    {
        i = j;
    }
    mm operator=(mm obj)
    {
        i = obj.i;
        cout << " = "<< this<<endl;
        return *this;
    }
    
    mm operator++()
    {
        i++;
        mm obj = *this;
        cout << this << " ++i " << i << "temp ";
        cout << &obj << endl;
        return *this;
    }
    mm operator++(int notused)
    {
        mm obj = *this;
        i++;
        cout << this << " i++ " << i << "temp ";
        cout << &obj << endl;
        return obj;
    }
};

mm plus(mm &obj1, mm &obj2)
{
    mm temp(0);
    temp.i = obj1.i + obj2.i;

    return temp;
}

class aa
{
public:
    int ii;
    int jj;
    aa()
    {
        ii = 234;
    }
    int operator++()
    {
        cout << ii << endl;
        return 234;
    }
    void show()
    {
        aa a1;
        jj = ++a1;
    }
};

void func(int p=0);

int main()
{
    /*
    char c[1000] = "12345";
    char ch;
    double d;
    
    ifstream in("data.txt", ios::binary);
    
    for(int i=0;i<1;i++)
    {
        //in.seekg(7,ios::beg);
        //int k = in.get();cout << k << endl;
        //in.get(ch);cout << ch;
        //in.get(c,1000,' ');cout << c << endl;
        //in.read(c,1000);cout << c << endl;
        //in.get(c,in.get());cout << c;
        //d = atof("34-5\n 99");d=in.tellg();cout << d << endl;
        
        //in.seekg(1,ios::cur);
        //cout << *c;
    }
    
    in.close();
    */
    
    /*
    ifstream in("datatens");
    char c;
    int ii=0;
    while(in.get(c))
    {
        ii++;
        cout << ii << "  " << c << endl;
    }
    in.close();
    */
    
    /*
    Tensor1<> t1(1);
    t1.show();
    t1.newData(2);
    t1.show();
    t1.newData(3);
    t1.show();
    t1.readData("datatens");
    t1.show();
    t1.newData(1);
    t1.show();
    
    
    
    //cout<<"0";
    Tensor2<> *t2;
    t2 = new Tensor2<>("datatens",4,4);
    t2->show();
    
    t2->readData("datatens",2,10);
    t2->show();
    
    t2->readData("datatens",2,2);
    t2->show();
    delete t2;
    cout<<"after";
    */
    
    /*
    ifstream in("datatens2");
    int **pi;
    int n=4, m=4;
    pi=new int *[n];
    for(int i=0;i<n;i++)
    {
        pi[i] = new int [m];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            in>>pi[i][j];
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout << pi[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i=0;i<n;i++)
    {
        delete [] pi[i];
    }
    delete [] pi;
    in.close();
    */
    /*
    int n = 100;
    int m = n+1;
    
    
    ofstream out("datatens");
    double d;
    for( int i=0; i< n; i++ )
    {
        for( int j=0; j< m; j++ )
        {
            d = random()%20;
            d -= 10;
            //d /= (double)10;
            out << d << " ";
        }
        out << endl;
    }
    out.close();
    out.open("datatens2");
    for( int i=0; i< n; i++ )
    {
        for( int j=0; j< m; j++ )
        {
            d = random()%20;
            d -= 10;
            //d /= (double)100;
            out << d << " ";
        }
        out << endl;
    }
    out.close();
    
    
    
    Tensor2<> t1("datatens", 4, 4);
    Tensor2<> t2("datatens2", 4, 1);
    t1.set(0,0) = 0;
    t1.show();
    t2.show();
    Tensor2<> t3;
    t3 = t1;
    t3.concatCol(t2);
    t3.solution();
    t3.show();
    */
    /*
    t3 = t1;
    cout << t1;
    t2.ident(4);
    t1.concatCol(t2);
    t1.gause();
    t3.inverse();
    cout << t1 << t3;
    */
    //t3.inverse();
    
    //t3.ident(800, 800);
    //t3.show();
    //t1.show();
    /*
    t2.show();
    t2.solution(n);
    t2 = t2+t1;
    t2.show();
    t2.ident(3,2);
    t2.show();
    */
    /*
    for( int i=0; i< 799; i++ )
    {
        t3.insert( t1, i, i );
    }
    Tensor2<> t2("datatens2", t3.row(), 1);
    t3.insert( t2, 0, t3.col() );
    //t3.show();
    t3.solution(t3.row());*/
    //t3.show();
    
    
    /*
    mm a=0,b=1,c=2;
    a = plus( b, c );
    cout <<a.i<<b.i<<c.i<< endl;
    */
    /*
    int kkn = 3;
    kk **pp = NULL;
    if( !pp )
    {
        pp = new kk *[kkn];
        for( int i=0; i< kkn; i++ )
        {
            pp[i] = new kk [2];
        }
    }
    
    if( pp )
    {
        for( int i=0; i< kkn; i++ )
        {
            if( pp[i] )
            {
                delete [] pp[i];
                pp[i] = NULL;
            }
        }
        delete [] pp;
        pp = NULL;
    }
    //-----------------------------
    if( !pp )
    {
        pp = new kk *[kkn];
        for( int i=0; i< kkn; i++ )
        {
            pp[i] = new kk [2];
        }
    }
    if( pp )
    {
        for( int i=0; i< kkn; i++ )
        {
            if( pp[i] )
            {
                delete [] pp[i];
                pp[i] = NULL;
            }
        }
        delete [] pp;
        pp = NULL;
    }
    if( pp )
    {
        for( int i=0; i< kkn; i++ )
        {
            if( pp[i] )
            {
                delete [] pp[i];
                pp[i] = NULL;
            }
        }
        delete [] pp;
        pp = NULL;
    }
    */
    
for(int i=0;i<5;i++)
{
    rotation();
    
    for( int i=0; i<4; i++ )
    {
        cout << pos_x[i]-300 << "  ";
    }
    cout << endl;
    
    for( int i=0; i<4; i++ )
    {
        cout << pos_y[i]-300 << "  ";
    }
    cout << endl;
    
    for( int i=0; i<4; i++ )
    {
        cout << deg[i]/100 << "  ";
    }
    cout << endl;
    
    for( int i=0; i<4; i++ )
    {
        cout << dt[i] << "  ";
    }
    cout << endl << endl;
    
}
    
    return 0;
}












