

#include "lang/String.h"
#include "lang/String_cpp.h"
#include <typeinfo.h>


//==========================================================
//==========================================================
class Test
{
private:
public:
    Test();
    ~Test();
    void teststart();
};
//==========================================================
//==========================================================
Test::Test(){}
Test::~Test(){}
void Test::teststart()
{
    String s1(true);
    String s2(878);
    String s3(double(8.4));
    String s4('a');
    String s5(L'k');
    
    cout << s1 << ", " << s1.length() << endl;
    cout << s2 << ", " << s2.length() << endl;
    cout << s3 << ", " << s3.length() << endl;
    cout << s4 << ", " << s4.length() << endl;
    cout << s5 << ", " << s5.length() << endl;
}
//==========================================================
//==========================================================

//==========================================================
//==========================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow)
{
    wchar_t programname[MAX_PATH +1];
    GetModuleFileNameW(0, programname, MAX_PATH);
    Test test;
    test.teststart();
    
    //while(GetMessage(&msg, NULL, 0, 0)){
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}
    
    return msg.wParam;
}
//==========================================================
//==========================================================

