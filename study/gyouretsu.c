#include <stdio.h>

void main()
{
      int i , j , k , n;
      FILE *fp;
      float e[10][10];
      float a[10][10];
      float temp;
      float det = 1;
      printf( "�s��A�̌v�Z\n�s��̎�������� n=" );
      scanf( "%d" , &n );

      /* �P�ʍs��*/
      for( i = 0 ; i < n ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              e[i][j] = 0;
              e[i][i] = 1;
      }   }

      /*�s��A*/
      printf( "\n�s��A" );
      fp=fopen( "gyouretsu.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( j = 0 ; j < n ; j ++ ){
              fscanf( fp , "%g" , &a[i][j] );
              printf( "%g  " , a[i][j] );
      }   }
      fclose(fp);

      /*�v�Z*/
      for( k = 0 ; k < n ; k ++ ){
          for( i = 0 ; i < n ; i ++ ){
              if( i != k ){
              temp = a[i][k] / a[k][k];
                  for( j = 0 ; j < n ; j ++ ){
                      a[i][j] -= temp * a[k][j];
                      e[i][j] -= temp * e[k][j];
      }   }   }   }

      printf( "\n\n�s��\n" );
      for( i = 0 ; i < n ; i ++ ){
          det *= a[i][i];
      }
      printf( "determinant A = %g\n" , det );

      printf( "\n�t�s��" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( j = 0 ; j < n ; j ++ ){
              printf( "%g   " , e[i][j] /a[i][i] );
      }   }
}