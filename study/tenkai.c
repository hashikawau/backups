/*   f(x)= ( a[0][1]*x + a[0][0] ) * ... * ( a[n][1]*x + a[n][0] )   */

#include <stdio.h>

void main()
{
      FILE *fp;
      int i , j , k;
      int first = 1;
      float a[5][2] , c[6];
      float ctemp[6];
      int n = 5;
      for( i = 0 ; i <= n ; i ++ ){ c[i] = 0; }

      fp = fopen( "tenkai.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          for( j = 1 ; j >= 0 ; j -- ){
              fscanf( fp , "%g" , &a[i][j] );
          }
      }
      fclose(fp);

      c[0] = a[0][0];
      c[1] = a[0][1];
      for( k = 1 ; k < n ; k ++ ){
          for( i = 0 ; i <= n ; i ++ ){ ctemp[i] = 0; }
          for( i = 0 ; i <= k ; i ++ ){
              for( j = 0 ; j <= 1 ; j ++ ){
                  ctemp[i+j] += c[i] * a[k][j];
              }
          }
          for( i = 0 ; i <= k + 1 ; i ++ ){ c[i] = ctemp[i]; }
      }

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