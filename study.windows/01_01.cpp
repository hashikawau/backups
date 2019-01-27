#include <windows.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <wchar.h>
#include "windows\list.h"

class sample1
{
private:
    char sam1private;
    
protected:
    char sam1protected;
    
public:
    sample1()
    {
        sam1private = 'a';
        sam1protected = 'b';
    }
    
    virtual void show()
    {
        cout << sam1private << "  " << sam1protected << endl;
    }
    
};

class sample2 : public sample1
{
public:
    void show(){cout << "sample2 show()";}
    void show2()
    {
        //sam1private = 'c';
        sam1protected = 'd';
        show();
        
    }
    
};

class sample3 : public sample2
{
public:
    void show3()
    {
        //sam1private = 'c';
        sam1protected = 'd';
        this->show();
        
    }
    
};


class sample4_2;
class sample4
{
    sample4_2 *ps;
public:
    sample4()
    {
        ps = new sample4_2;
    }
    void show();
};
class sample4_2 :public sample4
{
public:
    int x;
    sample4_2()
    {
        x = 2;
    }
};
    inline void sample4::show()
    {
        cout << ps->x << endl;
    }




void main()
{
    int p[] = {1,2,3,4,5,6,7,8};
    int pp[] = {1, 3, 5, 7, 9, 11};
    int ppp[] = {2,4,6,8,10,12};
    
    String *str;
    str = new String;
    delete str;
    str = new String;
    delete str;
    str = new String;
    
    *str = *str + "sss" + "dlsjf" + 2.34;
    cout << *str << endl;
    cout << *str << endl;
    delete str;
    
}



