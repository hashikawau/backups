#include <stdio.h>

main()
{
    int i , k;
    int n;
    double nprd = 1;    /* n! */
    double e = 1.0;


    printf( "���R�ΐ������߂܂��Be=��1/n! \n���̐���n����͂��Ă��������B\n\f" );
    scanf( "%d" , &n );


    /*              */
    for( k = 1 ; k <= n ; k ++ ){

       for( nprd = 1 , i = 1 ; i <= k ; i ++){ nprd = nprd * i; }

       printf( "1/%d!= %g  e= %g\n" , k , 1.0/nprd , e );
       e = e + 1.0 / nprd;    

    }

    printf( "\nn=%d�̂Ƃ��A���R�ΐ���%f�ł��B\n" , n , e );
}