#include <stdio.h>
#include <math.h>

int l = 20;
int m = 10;
int n = 10;
void check_row( int row , int row_num_black , int row_black[][l] , int a[m][n] );

void main()
{
      int i , j;
      int row_num_black[m];
      int row_black[m][l];
      int a[m][n];
      for( j = 0 ; j < n ; j ++ ){ a[0][j] = 0; }
/*
      a[0][0] = 1;
      a[0][1] = 1;
      a[0][2] = 1;
      a[0][3] = 1;
      a[0][4] = 1;
      a[0][5] = 0;
      a[0][6] = 1;
      a[0][7] = 1;
      a[0][8] = 1;
      a[0][9] = 0;
*/
      row_black[0][2] = 3;
      row_black[0][1] = 1;
      row_black[0][0] = 3;



      for( i = 0 ; i < pow( 2 , n * m ) ; i ++ ){
          check_row( 0 , 3 , row_black , a );
          a[0][0] ++;
              for( j = 0 ; j < n ; j ++ ){
                  if( a[0][j] >= 2 ){
                      a[0][j+1] ++;
                      a[0][j] = 0;
                  }
             
          }
      }

}

void check_row( int row , int row_num_black , int row_black[][l] , int a[m][n] )
{
      int i , j;
      int judge_sum_black = 0;
      int judge_row_black = 0;
      int judge_row_white = 1;
      int judge_num_black = 0;
      int row_num = 0;
      int row_sum_black = 0;
      for( i = 0 ; i < row_num_black ; i ++ ){ row_sum_black += row_black[i][row]; }

      for( j = n-1 ; j >= 0 ; j -- ){
          switch( a[row][j] ){
              case 0:
                      if( judge_row_white == 0 ){
                          if( judge_row_black == row_black[row_num][row] ){
                              row_num ++;
                          }
                          else{
                              return;
                          }
                      }
                      judge_row_black = 0;
                      judge_row_white ++;
                      break;
              case 1:
                      if( judge_row_black == 0 ){
                          judge_num_black ++;
                      }
                      judge_row_black ++;
                      judge_row_white = 0;
                      judge_sum_black ++;
                      break;
              default:
                      printf( "error a[%d][%d] is not correct" , j , row );
                      break;
          }
      }
      if( judge_sum_black == row_sum_black ){
          if( judge_num_black == row_num_black ){
              for( j = 0 ; j < n ; j ++ ){
                  printf( "%d\n" , a[row][j] );
              }
          }
      }
      else{
          return;
      }
      printf( "\n" );
}