#include <stdio.h>
#include <math.h>

int judg_j( int n , int j[] );
int sigma( int n , int j[] );

void main()
{
      FILE *fp;
      int i , k , l;
      int n;
      scanf( "%d" , &n );

      /*�s��A*/
      float a[n][n];
      printf( "\n�s��A" );
      fp = fopen( "gyouretsu.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( k = 0 ; k < n ; k ++ ){
              fscanf( fp , "%g" , &a[i][k] );
              printf( "%g  " , a[i][k] );
          }
      }
      fclose(fp);

      /*  �s�񎮂̌v�Z  */
      float det_A = 0;
      int nn_pow;
      int j[n];
      nn_pow = pow( n , n );
      for( i = 0 ; i < n ; i ++ ){ j[i] = 0; }

      for( k = 0 ; k < nn_pow ; k ++ ){
          if( judg_j( n , j ) == 1 ){
              float temp_a = 1;
              for( i = 0 ; i < n ; i ++ ){
                  temp_a *= a[i][j[i]];
              }
              det_A += sigma( n , j ) * temp_a;
          }
          j[0] ++;
          for( i = 0 ; i < n ; i ++ ){
              if( j[i] >= n ){             /*  n�i�\��  */
                  j[i+1] ++;
                  j[i] = 0;
              }
          }
      }
      printf( "\nA�̍s�� = %g" , det_A );
}

/*  j[n] �� 0 ���� n-1 �܂ł��܂܂�Ă����� 1 ��Ԃ�  */
int judg_j( int n , int j[] )
{
      int i;
      int j_num[n];      /*  j[n]�̌�  */
      for( i = 0 ; i < n ; i ++ ){
          j_num[i] = 0;
      }

      for( i = 0 ; i < n ; i ++ ){
          j_num[j[i]] ++;
          if( j_num[j[i]] >= 2 ){
              return 0;
          }
      }
      return 1;
}

/*  �ЋL��  */
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
              for( l = 0 ; l < n ; l ++ ){
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