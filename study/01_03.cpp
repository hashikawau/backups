#include <stdio.h>
#include <string.h>

template <typename T> class Test
{
public:
    T show(T);
};

template <typename T> T Test <T>::show(T userinput)
{
    return userinput;
}

void main()
{
    char c, d;
    int i, j;
    char str[256], *strx;
    
    Test<char> MyChar;
    Test<int> MyInt;
    Test<char *>Mystr;
    
    printf( "１バイト文字を入力してください" );
    scanf( "%c", &c );
    d = MyChar.show(c);
    printf( "入力したのは%cだね\n", d );
    printf( "整数を入力してください" );
    scanf( "%i", &i );
    j = MyInt.show(i);
    
}