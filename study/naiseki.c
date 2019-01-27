#include <stdio.h>

void main()
{
      FILE *fp;
      int i , j , k;
      int n;
      printf( "s—ñ‚ÌŸ” n=" );
      scanf( "%d" , &n );
      float a[n][n] , b[n][n] , c[n][n];
      for( i = 0 ; i < n ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              c[i][j] = 0;
          }
      }

      fp = fopen( "naiseki.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              fscanf( fp , "%g" , &a[i][j] );
          }
      }
      for( i = 0 ; i < n ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              fscanf( fp , "%g" , &b[i][j] );
          }
      }
      fclose(fp);

      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( j = 0 ; j < n ; j ++ ){
              for( k = 0 ; k < n ; k ++ ){
                  c[i][j] += a[i][k] * b[k][j];
              }
              printf( "%g  " , c[i][j] );
          }
      }
}