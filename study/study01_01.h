#include <iostream.h>

class cls
{
	int v1;
public:
	cls();
	~cls();
	int v2;
	void f1();
	void f2();
};

cls::cls()
{
	v1 = 1;
	v2 = 2;
}

cls::~cls()
{
	cout << "destructor";
}

void cls::f1()
{
	cout << v1;
}

void cls::f2()
{
	cout << v2;
}

class myclass{
	int *p;
public:
	myclass(const myclass &ob)
	{
		p = new int;
		*p = *ob.p;
		cout << "copy constructor\n";
	}
	myclass(int i)
	{
		cout << "normal\n";
		p = new int;
		*p = i;
	}
	~myclass()
	{
		cout << "freeing\n";
		delete p;
	}
};


class base1
{
public:
	virtual void show1() = 0;
	void show2()
	{
		cout << "base1-show2";
	}
};
class derived1: public base1
{
public:
	void show1()
	{
		cout << "derived1-show1";
	}
	void show3()
	{
		cout << "derived1-show3";
	}
};

