#include <stdio.h>

main()
{
    int a = 100 , b = 201;

    if( a == 100 ){
      if( b == 200 ){ printf( "a=100  b=200 \n" ); }
      else          { printf( "bÇÕ200Ç≈ÇÕÇ»Ç¢ \n" ); }
    }
    else{
      if( b == 200 ){ printf( "aÇÕ100Ç≈ÇÕÇ»Ç¢ \n" ); }
      else          { printf( "aÇÕ100Ç≈ÇÕÇ»Ç¢ÇµÅAbÇ‡200Ç≈ÇÕÇ»Ç¢ \n" );}
    }
}