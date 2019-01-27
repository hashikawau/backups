#include <stdio.h>
#include <math.h>


void ttt( int *temp_frame[] );

void main()
{
      int i , j , k;
      int m = 5 , n = 5;
      int frame[m][n];
      int *p_frame;
      p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){ *( p_frame + i ) = i; }
      
      int *temp_frame[m];

      

      for( i = 0 ; i < 10 ; i ++ ){
          printf( "%d\n" , temp_frame[i] );
      }
      temp_frame[0] = p_frame;
      temp_frame[1] = p_frame + 5;
      temp_frame[2] = p_frame + 10;
      temp_frame[3] = p_frame + 15;
      temp_frame[4] = p_frame + 20;	

      for( i = 0 ; i < 10 ; i ++ ){
          printf( "%d\n" , temp_frame[i] );
      }
}


void ttt( int *temp_frame[] )
{
      int i;
      for( i = 0 ; i < 5 ; i ++ ){
          printf( "%d %d\n" , *temp_frame[i] , &temp_frame[i] );
      }
}



















