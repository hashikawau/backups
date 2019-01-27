
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys\stat.h>
#include <direct.h>
#include "class01.h"

// main() is where program execution begins.

long double factorial( int );
static void c01();
void c02();
void c03();
void c04();
void c05();
void c06();

struct c1
{
	int b;
}a1, a2;

struct c2
{
	int b;
	int y;
}d1;

void u(c1 cc);
void u(c1* cc);


//--------------------05----------01/03
class tensor{
	int x, y;
public:
	tensor(){ x = 1; y = 1; }
	tensor( int i, int j ){ x = i; y = j; }
	
	int operator+( tensor ts2 ){ return (x + ts2.x)*(x + ts2.x) + (y + ts2.y)*(y + ts2.y); }
	int operator+( int i ){ return (x + i)*(x + i) + (y + i)*(y + i); }
	int operator++( int notused ){ return x+y; }
	int operator+(){ return 2*(x+y); }
	friend int operator*( tensor ts1, tensor ts2 ){ return ts1.x + ts1.y + ts2.x + ts2.y; }
	int operator==( tensor ts2 ){ return 2; }
	int operator^( tensor ts2 ){ return 6; }
	void show();
};
void tensor::show()
{
	
}


//--------------------06----------01/03
class base
{
	//int i;
protected:
	//int j;
public:
	int i;
	int j;
	base()
	{
		i = 1;
		j = 3;
	}
	
	/*virtual */void show()
	{
		cout << "base.show\t";
		cout << i << '\t';
		cout << j << '\n';
	}
};
class derived1 : public base
{

public:
	derived1()
	{
		i = 6;
		j = 7;
	}
	void show()
	{		
		cout << "derived1.show\t";
		cout << i << '\t';
		cout << j << '\n';
	}
};


//--------------------07----------01/02
template <class X, class Y> void glfunc(X x, Y y)
{
	cout << x << '\t' << y;
}


int main()
{
	/*
	cls c1;
	
	c1.f1();
	c1.f2();
	*/
	
	
	/*
	myclass a(10);
	myclass b = a;
	*/
	
	base1 *Pb1;
	derived1 d1;
	
	Pb1 = &d1;
	Pb1 = &d1;
	Pb1->show2();
	
	
	/*
	cout << "This is my first C++ program.\n";
	
	for( int i = 0; i < 1; i++ )
	{
		cout << &i << "\n";
		
		abs( -9 );
		8;
		inn();
		
		for( int i = 0; i < 1; i++ )
		{
			cout << &i << "\n";
		}
		
		cout << &i << "\n";
	}
	*/
	
	/*
	int a1 = 1;
	int& a2 = a1;
	//int& a3 = 3;
	const int* a3 = &a1;
	//a3++;
	cout << a2 << "\t";
	a2 = 2;
	cout << a2 << "\t";
	a2 = a1;
	cout << a2 << "\t";
	cout << *a3 << "\n";
	
	volatile int clock;
	cout << clock << "\n";
	cout << clock << "\n";
	*/
	
	/*
	long double e = 0;
	int number;
	cout << "enter integer\n";
	cin >> number;
	//long double fact = factorial( number );
	//cout << number << "! =  " << fact;
	for( int i = 0; i <= number; i++ )
	{
		long double fact = factorial( i );
		e += 1/fact;
		cout.precision(20);
		cout << i << "! =  " << fact << "\texp =  " << e << "\n";
	}
	cout << "exp =  " << e;
	*/
	
	/*
	int u;
	do
	{
		double o0 = 1;
		long double o1 = 1;
		cout << "enter integer\n";
		cin >> u;
		for( int i = 0; i < u; i++ )
		{
			o0 = o1 *= 10;
		}
		cout <<"double = " << o0 << "\nlong double = " << o1;
		
	}while(u);
	*/

	
	/*
	//--------------------01----------01/02
	c01();
	c01();
	//c01_01 = 4;
	c01();
	*/


	/*
	//--------------------02----------01/02
	c02();
	*/
	
	/*
	//--------------------03----------01/02
	c03();
	*/
	
	
	/*
	//--------------------04----------01/03
	c04();
	*/
	
	/*
	//--------------------05----------02/03
	c05();
	printf("hello");
	exit(1);
	*/
	
	
	/*
	//--------------------06----------02/03
	c06();
	*/
	
	/*
	glfunc(1,1);
	*/
	
	return 0;
} 

long double factorial( int number )
{ 
	if( number <= 1 )
	{
		return 1;
	}
	
	return (long double)number * factorial( number -1 );
}

//--------------------01----------02/02
static void c01()
{
	static int c01_01 = 0;
	
	++c01_01;
	cout << c01_01;
}


//--------------------02----------02/02
void c02()
{
	unsigned int i;
	register unsigned int j;
	unsigned int delay;
	long start, end;
	char cc;
	
	cout << "Press button to start\n";
	cin >> cc;
	start = clock();
	for( delay = 0; delay < 50; delay++ )
	{
		for( i = 0; i < 64000000; i++ )
		{
		
		}
	}
	end = clock();
	cout << "Number of clock ticks for non-register loop: ";
	cout << end - start << '\n';
	
	cout << "Press button to start\n";
	cin >> cc;	
	start = clock();
	for( delay = 0; delay < 50; delay++ )
	{
		for( j = 0; j < 64000000; j++ )
		{
		
		}
	}
	end = clock();
	cout << "Number of clock ticks for register loop: ";
	cout << end - start << '\n';
}


//--------------------03----------02/02
void c03()
{
	int* cc3;
	cc3 = new int[100];
	for( int i = 0; i < 100; i++ ) cc3[i] = i;
	
	for( int i = 0; i < 100; i++ ) cout << *( cc3 + i ) << '\n';
	
	//delete [] cc3;
	
	int* cc31;
	cc31 = new int[100];
	for( int i = 0; i < 100; i++ ) cc31[i] = 10 * i;
	
	for( int i = 0; i < 100; i++ ) cout << *( cc3 + i ) << '\n';
	
	delete [] cc31;
	
	return;
}

//--------------------04----------02/03
void c04()
{
	c1 a3;
	c1 *a4;
	a4 = &a3;
	cout << a3.b << '\n';
	u(a3);
	cout << a3.b << '\n';
	u(a4);
	cout << a3.b << '\n';
}


//--------------------04----------03/03
void u(c1 cc)
{
	cc.b = 0;
}
void u(c1* cc)
{
	cc->b = 0;
}


//--------------------05----------03/03
void c05()
{
	tensor a, b;
	a = tensor(1, 3);
	
	cout << a+b << '\n';
	cout << a+1 << '\n';
	cout << a++ << '\n';
	cout << +a << '\n';
	cout << a*b << '\n';
	if(a==b) cout << "a==b" << '\n';
	cout << (a^b) << '\n';
	
	int c, d;
	c = d = 9;
	cout << c+d << '\n';
	bool e = true;
	cout << e << '\n';
}


//--------------------06----------03/03
void c06()
{
	base *bp;
	base bo;
	derived1 d1;
	bo.show();
	d1.show();
	
	bp = &bo;
	bp->show();
	
	
	cout << (bp+1)->i << '\n';
	cout << bp->j << '\n';
	
	bp = &d1;
	bp->show();
	cout << (bp-1)->i << '\n';
	cout << bp->j << '\n';
}