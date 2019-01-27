#include <stdio.h>
#include <math.h>

int l = 20;
int count_num_black( FILE *fp );
void set_black( int mn , int m_or_n , int num_black[] , int black[][l] );
void set_white( int i , int row_white[][l] , int row_sum_white );


void main()
{
      int i , j;
      int m = 5;
      int n = 5;

      /*    */
      int row_num_black[m];
      int row_black[m][l];
      int colum_num_black[n];
      int colum_black[n][l];

      set_black( 'm' , m , row_num_black , row_black );
      set_black( 'n' , n , colum_num_black , colum_black );

            printf( "    " );
            for( i = 0 ; i < n ; i ++ ){
                for( j = colum_num_black[i]-1 ; j >= 0 ; j -- ){
                    printf( "%d " , colum_black[i][j] );
                }
            }
            for( i = 0 ; i < m ; i ++ ){
                printf( "\n" );
                for( j = 0 ; j < row_num_black[i] ; j ++ ){
                    printf( "%d " , row_black[i][j] );
                }
            }

      /*    */
      int end = 0;
      int row_sum_black[m];
      int row_num_white[m];
      int row_sum_white[m];
      int row_white[m][l];
      int num_order_white[m];

      for( i = 0 ; i < m ; i ++ ){
          row_sum_black[i] = 0;
          row_num_white[i] = row_num_black[i] + 1;
          num_order_white[i] = pow( row_sum_white[i] , row_num_white[i] );
          for( j = 0 ; j < row_num_black[i] ; j ++ ){
              row_sum_black[i] += row_black[i][j];
          }
          row_sum_white[i] = n - ( row_sum_black[i] + ( row_num_black[i] - 1 ) );
          printf( "%d\n" , row_sum_white[i] );
      }



      while( end != 1 ){
          row_white[i][0] ++;
          for( j = 0 ; j < row_sum_white[i] ; j ++ ){
              if( row_white[i][j] >= row_sum_white[i] ){
                  row_white[i][j+1] ++;
                  row_white[i][j] = 0;
              }
          }
      }


/*
      while( 1 ){
          row_white[m][0] ++;
          for( i = 0 ; i < row_sum_white[m] ; i ++ ){
              if( row_white[m][i] >= row_sum_white[m] ){
                  row_white[m][i+1] ++;
                  row_white[m][i] = 0;
              }
          }
      }
*/


}

void set_black( int mn , int m_or_n , int num_black[] , int black[][l] )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;

      switch( mn ){
          case 109:
                   fp_char = fopen( "iraroji_row.txt" , "r" );
                   fp_int = fopen( "iraroji_row.txt" , "r" );
                   break;
          case 110:
                   fp_char = fopen( "iraroji_colum.txt" , "r" );
                   fp_int = fopen( "iraroji_colum.txt" , "r" );
                   break;
          default:
                   break;
      }
      for( i = 0 ; i < m_or_n ; i ++ ){
          num_black[i] = count_num_black( fp_char );
          for( j = 0 ; j < num_black[i] ; j ++ ){
              fscanf( fp_int , "%d" , &black[i][j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );
}

int count_num_black( FILE *fp )
{      
      int i;
      int num_black = 1;
      char kuro;

      while( kuro != 10 ){
          fscanf( fp , "%c" , &kuro );
          if( kuro == 32 ){ 
              num_black ++;
          }
      }
      return num_black;
}

void set_white( int i , int row_white[][l] , int row_sum_white )
{
      int j;

      for( j = 0 ; j < row_sum_white ; j ++ ){
          if( row_white[i][j] >= row_sum_white ){
              row_white[i][j+1] ++;
              row_white[i][j] = 0;
          }
      
      }
      row_white[i][0] ++;
}