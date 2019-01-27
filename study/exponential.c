#include <stdio.h>

main()
{
    int i , k;
    int n;
    double nprd = 1;    /* n! */
    double e = 1.0;


    printf( "自然対数を求めます。e=∑1/n! \n正の整数nを入力してください。\n\f" );
    scanf( "%d" , &n );


    /*              */
    for( k = 1 ; k <= n ; k ++ ){

       for( nprd = 1 , i = 1 ; i <= k ; i ++){ nprd = nprd * i; }

       printf( "1/%d!= %g  e= %g\n" , k , 1.0/nprd , e );
       e = e + 1.0 / nprd;    

    }

    printf( "\nn=%dのとき、自然対数は%fです。\n" , n , e );
}