#include <iostream.h>
#include <stdlib.h>


char* concat( char*, char* );
int   length( char* );


void main()
{
    char *str1 = "hello";
    char *str2 = "word";
    
    cout << concat( str1, str2 );
}


char *concat( char *s1, char *s2 )
{
    int lens1 = length( s1 );
    int lens2 = length( s2 );
    char *s3;
    s3 = new char [ (lens1+lens2) ];
    char *pch;
    pch = s3;
    
    while( *s1 )
    {
        *pch = *s1;
        s1++;
        pch++;
    }
    *pch = ' ';
    pch++;
    
    while( *s2 )
    {
        *pch = *s2;
        s2++;
        pch++;
    }
    *pch = '\0';
    
    return s3;
}


int length( char *string )
{
    register int i = 0;
    
    while( *string )
    {
        i++;
        string++;
    }
    
    return i+1;
}