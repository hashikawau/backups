#include <stdio.h>

main()
{
    int a = 1;

    switch( a ){
       case 1 : printf( "a��1�ł��B\n" ); break;
       case 2 : printf( "a��2�ł��B\n" ); break;
       default : printf( "a��1�ł�2�ł�����܂���B\n" ); break;
    }
}