
#include <iostream.h>
#include <fstream.h>
#include <alloc.h>
#include <win32\WINDOWS.H>
#include "class02.h"
#include "class03.h"


void main()
{

	/*
	//--------------------class02----------
	two_d a(0, 0), b(1, 2), c(10, 20);
	
	cout << a;
	cin >> a;
	cout << a << b << c;
	
	cout << 8 << '\n' << "tr";
	*/
	
	
	/*
	//--------------------class03----------
	filemnp mnp1;
	cout << "Now writing\n";
	mnp1.output << "hello2\n";
	*/
	
	char *argv = "j.txt";
	filemnp mnp1( argv );
	cout << "Now writing\n";
	mnp1.output << "\n\nhello hello!\n\n";
	
	/*
	ofstream out( argv, ios::in | ios::binary );
	out << "hello3\n";
	out.close();
	*/
	
	
	//char *argv = "test.txt";
	char ch;
	ifstream in( argv, ios::in | ios::binary );
	if(!in)
	{
		cout << "Cannot open file.\n";
		return;
	}
	while(in)
	{
		in.get(ch);
		if(in) cout << ch;
	}
	in.close();
	
}