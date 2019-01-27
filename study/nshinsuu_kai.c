#include <stdio.h>
#include <math.h>

int judg_j( int n , int j[] );

void main()
{
      int i , k , l;
      int n = 4;
      int nn_pow;  /*  n^n  */
      int j[n];
      nn_pow = pow( n , n );
      for( i = 0 ; i < n ; i ++ ){ j[i] = 0; }

      for( k = 0 ; k < nn_pow ; k ++ ){
          if( judg_j( n , j ) == 1 ){
              for( i = n-1 ; i >= 0 ; i -- ){
                  printf( "%d " , j[i] );
              }
              printf( "\n" );
          }
          j[0] ++;
          for( i = 0 ; i < n ; i ++ ){
              if( j[i] >= n ){             /*  ni•\¦  */
                  j[i+1] ++;
                  j[i] = 0;
              }
          }
      }
}

/*  j[n] ‚É 0 ‚©‚ç n-1 ‚Ü‚Å‚ªŠÜ‚Ü‚ê‚Ä‚¢‚½‚ç 1 ‚ğ•Ô‚·  */
int judg_j( int n , int j[] )
{
      int i;
      int j_num[n];      /*  j[n]‚ÌŒÂ”  */
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