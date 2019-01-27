#include <stdio.h>
#include <math.h>

int check_row( int row , int n , int num_black_line , int black_line[][20] , int frame[][n] );
int check_colum( int colum , int m , int n , int num_black_line , int black_line[][20] , int frame[][n] );

void main()
{
      int i , j , k;
      int m = 3;
      int n = 3;
      int l = 20;
      int end = 0;
      int row;
      int colum;
      int check_ablty;
      int row_num_black[m];
      int colum_num_black[n];
      int row_black[m][l];
      int colum_black[n][l];
      int frame[m][n];
      int *p_frame;
      p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){
          *( p_frame + i ) = 0;
      }
/*
      row_num_black[0] = 1;
      row_num_black[1] = 1;
      row_num_black[2] = 1;
      colum_num_black[0] = 1;
      colum_num_black[1] = 1;
      colum_num_black[2] = 1;
      row_black[0][0] = 1;
      row_black[0][1] = 1;
      row_black[1][0] = 3;
      row_black[2][0] = 1;
      row_black[2][1] = 1;
      colum_black[0][0] = 3;
      colum_black[1][0] = 1;
      colum_black[2][0] = 3;
*/
      for( i = 0 ; i < 2 ; i ++ ){
          row_num_black[i] = 1;
          colum_num_black[i] = 2;
          row_black[i][0] = 1;
          colum_black[0][i] = 1;
      }
      for( i = 0 ; end == 0 ; i ++ ){
          for(  ; 
          a[0][i] = 
          end = 1;
      }
/*
      while( end == 0 ){
          *p_frame += 1;
          for( j = 0 ; j < m * n ; j ++ ){
              if( *( p_frame + j ) >= 2 ){
                  *( p_frame + j + 1 ) += 1;
                  *( p_frame + j ) = 0;
              }
          }
          for( row = 0 ; row < m ; row ++ ){
              check_ablty = check_row( row , n , row_num_black[row] , row_black , frame );
              if( check_ablty == 0 ){ break; }
          }
          if( check_ablty == 0 ){ continue; }
          for( colum = 0 ; colum < n ; colum ++ ){
              check_ablty = check_colum( colum , m , n , colum_num_black[colum] , colum_black , frame );
              if( check_ablty == 0 ){ break; }
          }
          if( check_ablty == 0 ){ continue; }

          printf( "\n" );
          for( i = 0 ; i < m ; i ++ ){
              for( j = 0 ; j < n ; j ++ ){
                  printf( "%d " , frame[i][j] );
              }
              printf( "\n" );
          }
      }
*/
}

/*    */
int check_row( int row , int n , int num_black_line , int black_line[][20] , int frame[][n] )
{
      int j , k;
      int num_black = 0;
      int check_white = 1;
      int check_num_black = 0;

      for( j = 0 ; j < n ; j ++ ){
          switch( frame[row][j] ){
              case 1:
                     if( check_num_black == 1 ){ return 0; }   /**/
                     if( check_white == 0 ){ return 0; }       /**/
                     check_white = 0;
                     k = j + black_line[row][num_black];
                     if( k > n ){ return 0; }                  /**/
                     for(  ; j < k ; j ++ ){
                         if( frame[row][j] == 0 ){ return 0; } /**/
                     }
                     j --;
                     num_black ++;
                     if( num_black == num_black_line ){ check_num_black = 1; }
                     break;
              case 0:
                     check_white ++;
                     break;
             default:
                     printf( "error in check_row\n" );
                     break;
          }
      }
      if( check_white == n + 1 ){
          if( black_line[row][0] == 0 ){
              return 1;
          }
      }
      if( check_num_black == 0 ){ return 0; }
      else{ return 1; }
}

/*    */
int check_colum( int colum , int m , int n , int num_black_line , int black_line[][20] , int frame[][n] )
{
      int i , k;
      int num_black = 0;
      int check_white = 1;
      int check_num_black = 0;

      for( i = 0 ; i < m ; i ++ ){
          switch( frame[i][colum] ){
              case 1:
                     if( check_num_black == 1 ){ return 0; }   /**/
                     if( check_white == 0 ){ return 0; }       /**/
                     check_white = 0;
                     k = i + black_line[colum][num_black];
                     if( k > n ){ return 0; }                  /**/
                     for(  ; i < k ; i ++ ){
                         if( frame[i][colum] == 0 ){ return 0; } /**/
                     }
                     i --;
                     num_black ++;
                     if( num_black == num_black_line ){ check_num_black = 1; }
                     break;
              case 0:
                     check_white ++;
                     break;
             default:
                     printf( "error in check_colum\n" );
                     break;
          }
      }
      if( check_white == m + 1 ){
          if( black_line[colum][0] == 0 ){
              return 1;
          }
      }
      if( check_num_black == 0 ){ return 0; }
      else{ return 1; }
}
