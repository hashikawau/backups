#include <stdio.h>

void main()
{
      int i , j;
      int m = 10;
      int colum_num_black = 3;
      int a[m];
      int colum[colum_num_black];

      a[0] = 1;
      a[1] = 1;
      a[2] = 1;
      a[3] = 0;
      a[4] = 0;
      a[5] = 1;
      a[6] = 0;
      a[7] = 1;
      a[8] = 1;
      a[9] = 0;

      colum[2] = 3;
      colum[1] = 1;
      colum[0] = 2;
      int colum_sum_black = 0;
      for( i = 0 ; i < colum_num_black ; i ++ ){
          colum_sum_black += colum[i];
      }

      int judge_sum_black = 0;
      int judge_colum_black = 0;
      int judge_colum_white = 0;
      int judge_num_black = 0;
      int colum_num = 0;
      for( j = m-1 ; j >= 0 ; j -- ){
          switch( a[j] ){
              case 0:
                      if( judge_colum_white == 0 ){
                          if( judge_colum_black == colum[colum_num] ){
                              colum_num ++;
                          }
                          else{
                              printf( "tyau tyau!" );
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
                      printf( "[%d]  %d\n" , colum_num , judge_colum_black );
                      break;
              default:
                      printf( "error a[%d] is not correct" , j );
                      break;
          }
      }
      if( judge_sum_black == colum_sum_black ){
          if( judge_num_black == colum_num_black ){
              for( j = 0 ; j < m ; j ++ ){
                  printf( "%d\n" , a[j] );
              }
          }
      }
      else{
          printf( "that is wrong!" );
      }
}

int check_colum()
{

}