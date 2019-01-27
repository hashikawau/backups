#include <stdio.h>

void main()
{
      int i , j , k , n;
      FILE *fp;
      float e[10][10];
      float a[10][10];
      float temp;
      float det = 1;
      printf( "行列Aの計算\n行列の次数を入力 n=" );
      scanf( "%d" , &n );

      /* 単位行列*/
      for( i = 0 ; i < n ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              e[i][j] = 0;
              e[i][i] = 1;
      }   }

      /*行列A*/
      printf( "\n行列A" );
      fp=fopen( "gyouretsu.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( j = 0 ; j < n ; j ++ ){
              fscanf( fp , "%g" , &a[i][j] );
              printf( "%g  " , a[i][j] );
      }   }
      fclose(fp);

      /*計算*/
      for( k = 0 ; k < n ; k ++ ){
          for( i = 0 ; i < n ; i ++ ){
              if( i != k ){
              temp = a[i][k] / a[k][k];
                  for( j = 0 ; j < n ; j ++ ){
                      a[i][j] -= temp * a[k][j];
                      e[i][j] -= temp * e[k][j];
      }   }   }   }

      printf( "\n\n行列式\n" );
      for( i = 0 ; i < n ; i ++ ){
          det *= a[i][i];
      }
      printf( "determinant A = %g\n" , det );

      printf( "\n逆行列" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( j = 0 ; j < n ; j ++ ){
              printf( "%g   " , e[i][j] /a[i][i] );
      }   }
}