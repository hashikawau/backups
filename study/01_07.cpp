#include <iostream.h>

class C01
{
public:
    int iC01_1;
    int *piC01_1;
    
    C01()
    {
        iC01_1 = 0;
        piC01_1 = &iC01_1;
    }
    
    void show()
    {
        cout << iC01_1 << " " << *piC01_1 << endl;
    }
};

int main()
{
    int i = 3;
    C01 c;
    c.show();
    c.iC01_1 = 2;
    *c.piC01_1 = i;
    c.show();

    return 0;
}