#include <stdio.h>
#include <math.h>

int l = 20;
int m = 10;
int n = 10;
void check_row( int check_ablty , int row , int row_num_black , int row_black[m][l] , int a[m][n] );

void main()
{
      int i , j;
      int check_ablty = 0;
      int colum_num_black[n];
      int colum_black[n][l];
      int a[m][n];
      for( i = 0 ; i < m ; i ++ ){ a[i][0] = 0; }
/*
      a[0][0] = 1;
      a[1][0] = 1;
      a[2][0] = 1;
      a[3][0] = 1;
      a[4][0] = 1;
      a[5][0] = 0;
      a[6][0] = 1;
      a[7][0] = 1;
      a[8][0] = 1;
      a[9][0] = 0;

      colum_black[0][2] = 3;*/
      colum_black[0][1] = 5;
      colum_black[0][0] = 3;



      for( i = 0 ; i < pow( 2 , n ) ; i ++ ){
          check_colum( check_ablty , 0 , 2 , colum_black , a );
          a[0][0] ++;
          for( j = 0 ; j < n ; j ++ ){
              if( a[j][0] >= 2 ){
                  a[j+1][0] ++;
                  a[j][0] = 0;
              }
          }
      }

}

void check_colum( int check_ablty , int colum , int colum_num_black , int colum_black[n][l] , int a[m][n] )
{
      int i , j;
      int judge_sum_black = 0;
      int judge_colum_black = 0;
      int judge_colum_white = 1;
      int judge_num_black = 0;
      int colum_num = 0;
      int colum_sum_black = 0;

      if( check_ablty == 0){
          return;
      }

      for( i = 0 ; i < colum_num_black ; i ++ ){ colum_sum_black += colum_black[colum][i]; }

      for( j = m-1 ; j >= 0 ; j -- ){
          switch( a[j][colum] ){
              case 0:
                      if( judge_colum_white == 0 ){
                          if( judge_colum_black == colum_black[colum][colum_num] ){
                              colum_num ++;
                          }
                          else{
                              check_ablty = 0;
                              return;
                          }
                      }
                      judge_colum_black = 0;
                      judge_colum_white ++;
                      break;
              case 1:
                      if( judge_colum_black == 0 ){
                          judge_num_black ++;
                      }
                      judge_colum_black ++;
                      judge_colum_white = 0;
                      judge_sum_black ++;
                      break;
              default:
                      printf( "error a[%d][%d] is not correct" , j , colum );
                      break;
          }
      }
      if( judge_sum_black == colum_sum_black ){
          if( judge_num_black == colum_num_black ){
              for( j = 0 ; j < m ; j ++ ){
                  printf( "%d\n" , a[j][colum] );
              }
          }
      }
      else{
          check_ablty = 0;
          return;
      }
}