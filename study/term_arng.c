/*   f(x)= ( a[0][1]*x + a[0][0] ) * ... * ( a[n][1]*x + a[n][0] )
           + ( a[0][1]*x + a[0][0] ) * ... * ( a[n][1]*x + a[n][0] )   */

#include <stdio.h>

void tenkai( int n , float a[][2] , float b[] );
void output( int n , float c[] );

void main()
{
      FILE *fp;
      int i , j , k;
      int n = 5;
      int const_term;
      float a[n][2] , b[n+1] , c[n+1];
      int n_term = 3;
      for( i = 0 ; i <= n ; i ++ ){ c[i] = 0; }

      fp = fopen( "tenkai.txt" , "r" );
      for( k = 0 ; k < n_term ; k ++ ){
          fscanf( fp , "%d" , &const_term );
          for( i = 0 ; i < n ; i ++ ){
              for( j = 1 ; j >= 0 ; j -- ){
                  fscanf( fp , "%g" , &a[i][j] );
              }
          }
          tenkai( n , a , b );
          for( i = 0 ; i <= n ; i ++ ){ c[i] += const_term * b[i]; }
      }
      fclose(fp);

      output( n , c );
}

void tenkai( int n , float a[][2] , float b[] )
{
      int i , j , k;
      float btemp[6];                  /*   n_order + 1   */

      b[0] = a[0][0];
      b[1] = a[0][1];
      for( k = 1 ; k < n ; k ++ ){
          for( i = 0 ; i <= n ; i ++ ){ btemp[i] = 0; }
          for( i = 0 ; i <= k ; i ++ ){
              for( j = 0 ; j <= 1 ; j ++ ){
                  btemp[i+j] += b[i] * a[k][j];
              }
          }
          for( i = 0 ; i <= k + 1 ; i ++ ){ b[i] = btemp[i]; }
      }
}

void output( int n , float c[] )
{
      int i;
      int first = 1;

      printf( "f(x)=" );
      for( i = n ; i >= 0 ; i -- ){
          if( c[i] != 0 ){
              if( first == 1 ){
                  printf( " " );
                  first = 0;
              }
              else{
                  if( c[i] > 0 ){ printf( " +" ); }
                  else          { printf( " " ); }
              }
              switch( i ){
                  case 0:
                          printf( "%g" , c[i] );
                          break;
                  case 1:
                          if( c[i] == 1 )     { printf( "x" ); }
                          else{
                              if( c[i] == -1 ){ printf( "-x" ); }
                              else            { printf( "%gx^%d" , c[i] , i ); }
                          }
                          break;
                  default:
                          if( c[i] == 1 )     { printf( "x^%d" , i ); }
                          else{
                              if( c[i] == -1 ){ printf( "-x^%d" , i ); }
                              else            { printf( "%gx^%d" , c[i] , i ); }
                          }
                          break;
              }
          }
      }
}