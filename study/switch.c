#include <stdio.h>

main()
{
    int a = 1;

    switch( a ){
       case 1 : printf( "aは1です。\n" ); break;
       case 2 : printf( "aは2です。\n" ); break;
       default : printf( "aは1でも2でもありません。\n" ); break;
    }
}