#include <stdio.h>

main()
{
    int a = 100 , b = 201;

    if( a == 100 ){
      if( b == 200 ){ printf( "a=100  b=200 \n" ); }
      else          { printf( "bは200ではない \n" ); }
    }
    else{
      if( b == 200 ){ printf( "aは100ではない \n" ); }
      else          { printf( "aは100ではないし、bも200ではない \n" );}
    }
}