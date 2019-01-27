#include <stdio.h>
#include <math.h>

int judg_j( int n , int j[] );
int sigma( int n , int j[] );
void tenkai( int n , float a[][2] , float b[] );
void output( int n , float c[] );

void main()
{
      FILE *fp;
      int i , k , l;
      int n;
      printf( "行列Aの次数 n=" );
      scanf( "%d" , &n );

      /*行列A*/
      float a[n][n];
      printf( "\n行列A" );
      fp = fopen( "gyouretsu.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          printf( "\n" );
          for( k = 0 ; k < n ; k ++ ){
              fscanf( fp , "%g" , &a[i][k] );
              printf( "%g  " , a[i][k] );
          }
      }
      fclose(fp);

      /*  行列式の計算  */
      FILE *fterm;
      float koyuuchi;
      float det_A = 0;
      int nn_pow;
      int j[n];
      nn_pow = pow( n , n );
      for( i = 0 ; i < n ; i ++ ){ j[i] = 0; }

      fterm = fopen( "koyuuhouteishiki.txt" , "w" );
      for( k = 0 ; k < nn_pow ; k ++ ){
          if( judg_j( n , j ) == 1 ){
              fprintf( fterm , "\n%d\n" , sigma( n , j ) ); 
              float temp_a = 1;
              for( i = 0 ; i < n ; i ++ ){
                  if( j[i] == i ){ koyuuchi = -1; }
                  else           { koyuuchi =  0; }
                  fprintf( fterm , "%g %g\n" , koyuuchi , a[i][j[i]] );
                  temp_a *= a[i][j[i]];
              }
              det_A += sigma( n , j ) * temp_a;
          }
          j[0] ++;
          for( i = 0 ; i < n ; i ++ ){
              if( j[i] >= n ){             /*  n進表示  */
                  j[i+1] ++;
                  j[i] = 0;
              }
          }
      }
      fclose(fterm);
      printf( "\nAの行列式 = %g\n" , det_A );

      /*  固有方程式の展開  */
      float p[n][2] , q[n+1] , r[n+1];
      int n_fact = 1;
      for( i = 1 ; i <= n ; i ++ ){ n_fact *= i; }
      int n_term = n_fact;
      int const_term;
      for( i = 0 ; i <= n ; i ++ ){ r[i] = 0; }

      fterm = fopen( "koyuuhouteishiki.txt" , "r" );
      for( k = 0 ; k < n_term ; k ++ ){
          fscanf( fterm , "%d" , &const_term );
          for( i = 0 ; i < n ; i ++ ){
              for( l = 1 ; l >= 0 ; l -- ){
                  fscanf( fterm , "%g" , &p[i][l] );
              }
          }
          tenkai( n , p , q );
          for( i = 0 ; i <= n ; i ++ ){ r[i] += const_term * q[i]; }
      }
      fclose(fterm);

      printf( "固有方程式\n" );
      output( n , r );
}


/*  j[n] に 0 から n-1 までが含まれていたら 1 を返す  */
int judg_j( int n , int j[] )
{
      int i;
      int j_num[n];      /*  j[n]の個数  */
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

/*  σ記号  */
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
void tenkai( int n , float p[][2] , float q[] )
{
      int i , l , k;
      float qtemp[6];                  /*   n_order + 1   */

      q[0] = p[0][0];
      q[1] = p[0][1];
      for( k = 1 ; k < n ; k ++ ){
          for( i = 0 ; i <= n ; i ++ ){ qtemp[i] = 0; }
          for( i = 0 ; i <= k ; i ++ ){
              for( l = 0 ; l <= 1 ; l ++ ){
                  qtemp[i+l] += q[i] * p[k][l];
              }
          }
          for( i = 0 ; i <= k + 1 ; i ++ ){ q[i] = qtemp[i]; }
      }
}

void output( int n , float r[] )
{
      int i;
      int first = 1;

      printf( "f(x)=" );
      for( i = n ; i >= 0 ; i -- ){
          if( r[i] != 0 ){
              if( first == 1 ){
                  printf( " " );
                  first = 0;
              }
              else{
                  if( r[i] > 0 ){ printf( " +" ); }
                  else          { printf( " " ); }
              }
              switch( i ){
                  case 0:
                          printf( "%g" , r[i] );
                          break;
                  case 1:
                          if( r[i] == 1 )     { printf( "x" ); }
                          else{
                              if( r[i] == -1 ){ printf( "-x" ); }
                              else            { printf( "%gx^%d" , r[i] , i ); }
                          }
                          break;
                  default:
                          if( r[i] == 1 )     { printf( "x^%d" , i ); }
                          else{
                              if( r[i] == -1 ){ printf( "-x^%d" , i ); }
                              else            { printf( "%gx^%d" , r[i] , i ); }
                          }
                          break;
              }
          }
      }
}