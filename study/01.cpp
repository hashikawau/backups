
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <sys\socket.h>
#include <netinet\in.h>

// main() is where program execution begins.

long double factorial( int );
void c01();
void c02();
void c03();
void c04();

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


class D1
{
public:
    D1(){ cout << "D1 constructor" << endl; }
    ~D1(){ cout << "D1 destructor" << endl; }
};

D1 createD1(){ return D1(); }


int main()
{  sa.sin_family = AF_INET;
  sa.sin_port = htons( SERVICE_PORT );
  sa.sin_addr.s_addr = htonl( INADDR_ANY );
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
    int num = 6;
    struct Code{
        char _byte[4];
    };
    union{
        int number;
        Code code;
    }uni;
    uni.number = num;
    int size;
    if(uni.code._byte[3]){
        size = 4;}
    else if(uni.code._byte[2]){
        size = 3;}
    else if(uni.code._byte[1]){
        size = 2;}
    else{
        size = 1;}
    bool b[size*8];
    for(int i=0; i< size; ++i)
    {
        for(int j=0; j< 8; ++j)
        {
            b[i*8+j] = (uni.code._byte[i] >>j) & 1;
            cout << b[i*8+j];
        }
    }
    cout << endl;
    
    char str[size*8+1];
    for(int i=0; i< size*8; ++i)
    {
        str[i] = b[size*8-1-i] == true?
            '1':
            '0';
            cout << b[i] << "  " << str[i] << "  " << b[size*8-1-i] << endl;
    }
    str[size*8] = '\0';
    */
    
    createD1();
    cout << "createD1" << endl;
    D1 d1;
    cout << "declare d1" << endl;
    
    
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
void c01()
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