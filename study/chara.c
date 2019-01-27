#include <stdio.h>

void main()
{
    int i;
    int b[] = {0,1};
    char a[] = "hello";
    b[0] = 3;
    a[0] = 'g';
    printf( "%s  %c  %d\n" , a , a[6] , b[0] );
    for( i = 0 ; i <= 7 ; i ++ )
      printf( "a[%d]=%c\n" , i , a[i] );
    
}