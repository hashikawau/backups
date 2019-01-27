#include <stdio.h>

int check_row( int row , int n , int num_black_line , int black_line[][num_black_line] , int frame[][n] );

void main()
{
      int i , j , k;
      int row_num_black[3];
      row_num_black[0] = 1;
      row_num_black[1] = 1;
      row_num_black[2] = 1;
      int colum_num_black[3];
      colum_num_black[0] = 1;
      colum_num_black[1] = 1;
      colum_num_black[2] = 1;
      int a[3][3];
      a[0][0] = 0;
      a[0][1] = 0;
      a[0][2] = 0;
      a[1][0] = 0;
      a[1][1] = 0;
      a[1][2] = 0;
      a[2][0] = 0;
      a[2][1] = 0;
      a[2][2] = 1;
      int row[3];
      row[0] = 0;
      row[1] = 0;
      row[2] = 1;
      int colum[3];
      colum[0] = 0;
      colum[1] = 0;
      colum[2] = 1;

      for( i = 0 ; i < pow( 2 , m * n ) ; i ++ ){

          check_ablty = check_frame();
          if( check_ablty == 1 ){ break; }
      }
/*
      ironuri();
*/
}

/*    */
int check_frame( int m , int n , int num_black_line , int a[][] )
{
      int i , j;
      int check_ablty = 1;
      int row;
      int colum;

      for( row = 0 ; row < m ; row ++ ){
          if( check_ablty == 0 ){ return 0; }
          check_ablty = check_row();
      }
      for( colum = 0 ; colum < n ; colum ++ ){
          if( check_ablty == 0 ){ return 0; }
          check_ablty = check_colum();
      }              
}

/*    */
int check_row( int row , int n , int num_black_line , int black_line[][num_black_line] , int frame[][n] )
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
int check_colum()
{

}