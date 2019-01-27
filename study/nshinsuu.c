#include <stdio.h>
#include <math.h>

void main()
{
      int i , k;
      int n = 2;
      int nn_pow;
      int j_order[10];
      nn_pow = pow( n , n );
      for( i = 0 ; i < n ; i ++ ){ j_order[i] = 0; }

      for( k = 0 ; k < nn_pow ; k ++ ){
          for( i = n-1 ; i >= 0 ; i -- ){
              printf( "%d " , j_order[i] );
          }
          printf( "\n" );
          j_order[0] ++;
          for( i = 0 ; i < n ; i ++ ){
              if( j_order[i] >= n ){
                  j_order[i+1] ++;
                  j_order[i] = 0;
              }
          }
      }
}