#include <stdio.h>

main()
{
    int a = 100 , b = 201;

    if( a == 100 ){
      if( b == 200 ){ printf( "a=100  b=200 \n" ); }
      else          { printf( "b��200�ł͂Ȃ� \n" ); }
    }
    else{
      if( b == 200 ){ printf( "a��100�ł͂Ȃ� \n" ); }
      else          { printf( "a��100�ł͂Ȃ����Ab��200�ł͂Ȃ� \n" );}
    }
}