#include "iostream.h"
//#include <d3dx9.h>
//#include <direct.h>
//#include <cwchar>

void main()
{
	char str[] = "hello";
	char *p = 0;
	p = str;
	
	//*str = 'i';
	cout << *p << str;
}