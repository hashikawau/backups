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
    
    printf( "‚PƒoƒCƒg•¶š‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢" );
    scanf( "%c", &c );
    d = MyChar.show(c);
    printf( "“ü—Í‚µ‚½‚Ì‚Í%c‚¾‚Ë\n", d );
    printf( "®”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢" );
    scanf( "%i", &i );
    j = MyInt.show(i);
    
}