#include <stdio.h>

main()
{
    char end;
    int i = 1;
    printf( "%d\n%d\n" , i , &i );
    
    {
        int i = 5;
        printf( "%d\n%d\n" , i , &i );
    }
    
    printf( "%d\n%d\n" , i , &i );


    scanf( "%c" , &end );
}