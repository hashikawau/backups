/*   f(x)= ( a[m]*x^m + ... + a[0] )*( b[n]*x^n + ... + b[0] )  */


#include <stdio.h>

void main()
{
      FILE *fp;
      int i , j , k;
      int first = 1;
      float a[5] , b[5] , c[9];
      int m = 5 , n = 5;
      for( k = 0 ; k <= m + n -2 ; k ++ ){ c[k] = 0; }

      fp = fopen( "product_mn.txt" , "r" );
      for( i = m-1 ; i >= 0 ; i -- ){ fscanf( fp , "%g" , &a[i] ); }
      for( j = n-1 ; j >= 0 ; j -- ){ fscanf( fp , "%g" , &b[j] ); }
      fclose(fp);

      for( i = 0 ; i < m ; i ++ ){
          for( j = 0 ; j < n ; j ++){
              c[i+j] += a[i] * b[j];
          }
      }

      printf( "f(x)=" );
      for( k = n + m - 2 ; k >= 0 ; k -- ){
          if( c[k] != 0 ){
              if( first == 1 ){
                  printf( " " );
                  first = 0;
              }
              else{
                  if( c[k] > 0 ){ printf( " +" ); }
                  else          { printf( " " ); }
              }
              switch( k ){
                  case 0:
                          printf( "%g" , c[k] );
                          break;
                  case 1:
                          if( c[k] == 1 )     { printf( "x" ); }
                          else{
                              if( c[k] == -1 ){ printf( "-x" ); }
                              else            { printf( "%gx^%d" , c[k] , k ); }
                          }
                          break;
                  default:
                          if( c[k] == 1 )     { printf( "x^%d" , k ); }
                          else{
                              if( c[k] == -1 ){ printf( "-x^%d" , k ); }
                              else            { printf( "%gx^%d" , c[k] , k ); }
                          }
                          break;
              }
          }
      }
}