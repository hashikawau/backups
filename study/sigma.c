#include <stdio.h>

int sigma( int n , int j[] );

void main()
{
      int k;
      int n;
      printf( "enter" );
      scanf( "%d" , &n );
      int j_order[n];

      j_order[0] = 1;
      j_order[1] = 0;
      j_order[2] = 2;
      j_order[3] = 3;

      for( k = 0 ; k < n ; k ++ ){ printf( "%d " , j_order[k] ); }
      printf( "\nsigma=%d" , sigma( n , j_order ) );

      printf( "\n" );
      for( k = 0 ; k < n ; k ++ ){ printf( "%d " , j_order[k] ); }
}


int sigma( int n , int j[] )
{
      int k , l;
      int sign = 1;
      int j_dum[n];
      for( k = 0 ; k < n ; k ++ ){
          j_dum[k] = j[k];
      }

      for( k = 0 ; k < n ; k ++ ){
          if( j_dum[k] != k ){
              for( l = k ; l < n ; l ++ ){
                  if( j_dum[l] == k ){
                      j_dum[l] = j[k];
                      j_dum[k] = k;
                      sign *= -1;
                      break;
                  }
              }
          }
      }
      return sign;
}