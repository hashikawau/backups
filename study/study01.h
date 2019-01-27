#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//*****************************************************************************

void pointer01()
{
    int    *i, j[10];
    double *d, e[10];

    i = j;
    d = e;

    for( int x = 0; x < 10; x++ )
    {
        cout << i + x << "\t";
        cout << d + x << "\n";
    }
}

//*****************************************************************************

void pointer02()
{
    char str[80];
    char token[80];
    char *p, *q;

    cout << "Enter a sentence: ";
    gets( str );

    p = str;
    q = token;

    while( *p )
    {
        while( *p!=' ' && *p )
        {
            *q = *p;
            p++;
            q++;
        }

        *q = ' ';
        q++;

        while( *p==' ' && *p )
        {
            p++;
        }

        *q = '\0';
    }
    cout << token << "\n";
}

//*****************************************************************************

void pointer03()
{
    char str[80];
    char token[80];
    
    cout << "Enter a sentence: ";
    gets( str );
    
    for( int i = 0; ; i++ )
    {
        for( int j = 0; str[i]!=' ' && str[i]; j++, i++ )
        {
            token[j] = str[i];
        }
        
        token[i] = '\0';
        cout << token << "\n";
        if( !str[i] ) break;
    }
}

//*****************************************************************************

void pointer04()
{
    char str[20] = "hello tom";
    char *p;
    
    p = str;
    
    for( int i = 0; p[i]; i++ )
    {
        p[i] = toupper( p[i] );
    }
    
    cout << p;
}

//*****************************************************************************

void pointer05()
{
    char *str;
    
    str = "Pointers are fun to use.\n";
    
    cout << str;
}

//*****************************************************************************

void pointer06()
{
    int num[10];
    int *start, *end;
    
    start = num;
    end = &num[9];
    
    while( start <= end )
    {
        cout << "Enter a number: ";
        cin >> *start;
        start++;
    }
    
    start = num;
    
    while( start <= end )
    {
        cout << *start << ' ';
        start++;
    }
}

//*****************************************************************************

void pointer07()
{
    char *fortunes[] = { "0000", "1111", "2222", "3333", "4444" };
    int chance;
    
    cout << "To see your fortune, press a key: ";
    
    while( !kbhit() ){ rand(); }
    
    cout << "\n";
    
    chance = rand();
    chance = chance % 5;
    cout << fortunes[chance];
}

//*****************************************************************************

void pointer08()
{
    int choice;
    
    cout << "(1) add number or ";
    cout << "(2) concatnate strings?: ";
    
    cin >> choice;
    if( choice == 1 )
    {
        int a, b;
        cout << "Enter two numbers: ";
        cin >> a >> b;
        cout << "Sum is " << a + b << "\n";
    }
    else
    {
        char s1[80], s2[80];
        cout << "Enter two strings: ";
        cin >> s1;
        cin >> s2;
        strcat( s1, s2 );
        cout << "Concatnation is " << s1 << "\n";
    }
}

//*****************************************************************************

void ref01_func( int&, int& );
void reference01()
{
    int i, j;
    
    i = 10;
    j = 20;
    
    cout << "Initial values of i and j: ";
    cout << i << " " << j << "\n";
    ref01_func( j, i );
    cout << "Swapped values of i and j: ";
    cout << i << " " << j << "\n";
}
void ref01_func( int& x, int& y )
{
    int temp;
    
    temp = x;
    x = y;
    y = temp;
}

//*****************************************************************************

double &ref02_func();
double ref02_val = 100.0;
void reference02()
{
    double newval;
    
    cout << ref02_func() << "\n";
    
    newval = ref02_func();
    cout << newval << "\n";
    ref02_func() = 99.1;
    cout << ref02_func() << "\n";
}
double &ref02_func()
{
    return ref02_val;
}

//*****************************************************************************

void defarg01_func( int size=25 );
void default_argment01()
{
    for( int i = 0; i < 30; i++ )
    {
        cout << i << endl;
    }
    defarg01_func();
    
    for( int i = 0; i < 30; i++ )
    {
        cout << i << endl;
    }
    defarg01_func( 10 );
}
void defarg01_func( int size )
{
    for( ; size; size-- ){ cout << "\n"; }
}