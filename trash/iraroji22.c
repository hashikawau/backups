#include <stdio.h>
#include <math.h>

int l = 20;
      int m = 2;
      int n = 2;
int count_num_black( FILE *fp );
void set_black( int mn , int m_or_n , int num_black[] , int black[][l] );
void check_colum( int *check_ablty , int colum , int colum_num_black[] , int colum_black[m][n] , int a[m][n] );
void check_row( int *check_ablty , int row , int row_num_black[] , int row_black[m][l] , int a[m][n] );
void ironuri( int m , int n , int frame[m][n] );


void main()
{
      int i , j , k;
      int a[m][n];
      int check_ablty;
      int *p;
      p = &a[0][0];
      for( i = 0 ; i < m * n ; i ++ ){ *( p + i ) = 0 ;}

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
      }

      for( i = 0 ; i < pow( 2 , m * n ) ; i ++ ){
          check_ablty = 1;

          if( check_ablty == 0 ){ break; }
          for( k = 0 ; k < m ; k ++ ){
              check_row( &check_ablty , k , row_num_black , row_black , a );
          }
          for( k = 0 ; k < n ; k ++ ){
              check_colum( &check_ablty , k , colum_num_black , colum_black , a );
          }

          *p += 1;
          for( j = 0 ; j < m * n ; j ++ ){
              if( *( p + j ) >= 2 ){
                  *( p + j + 1 ) += 1;
                  *( p + j ) = 0;
              }
          }

          if( check_ablty == 1 ){
              ironuri( m , n , a );
          }
      }


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

void check_colum( int *check_ablty , int colum , int colum_num_black[] , int colum_black[n][l] , int a[m][n] )
{
      int i , j;
      int judge_sum_black = 0;
      int judge_colum_black = 0;
      int judge_colum_white = 1;
      int judge_num_black = 0;
      int colum_num = 0;
      int colum_sum_black = 0;

      if( *check_ablty == 0){
          return;
      }

      for( j = 0 ; j < colum_num_black[colum] ; j ++ ){ colum_sum_black += colum_black[colum][j]; }

      for( j = m-1 ; j >= 0 ; j -- ){
          switch( a[j][colum] ){
              case 0:
                      if( judge_colum_white == 0 ){
                          if( judge_colum_black == colum_black[colum][colum_num] ){
                              colum_num ++;
                          }
                          else{
                              *check_ablty = 0;
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
          return;
      }
      else{
          *check_ablty = 0;
          return;
      }
}

void check_row( int *check_ablty , int row , int row_num_black[] , int row_black[m][l] , int a[m][n] )
{
      int i , j;
      int judge_sum_black = 0;
      int judge_row_black = 0;
      int judge_row_white = 1;
      int judge_num_black = 0;
      int row_num = 0;
      int row_sum_black = 0;

      if( *check_ablty == 0){
          return;
      }

      for( i = 0 ; i < row_num_black[row] ; i ++ ){ row_sum_black += row_black[i][row]; }

      for( j = n-1 ; j >= 0 ; j -- ){
          switch( a[row][j] ){
              case 0:
                      if( judge_row_white == 0 ){
                          if( judge_row_black == row_black[row_num][row] ){
                              row_num ++;
                          }
                          else{
                              *check_ablty = 0;
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
                      printf( "error a[%d][%d] is not correct" , row , j );
                      break;
          }
      }
      if( judge_sum_black == row_sum_black ){
          return;
      }
      else{
          *check_ablty = 0;
          return;
      }
}
void ironuri( int m , int n , int frame[m][n] )
{
      FILE *ironuri;
      int i , j;
      int success = 1;

      ironuri = fopen( "iraroji_kotae.txt" , "w" );
      for( i = 0 ; i < m ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              switch( frame[i][j] ){
                  case 0:
                         printf( "  " );
                         fprintf( ironuri , "  " );
                         break;
                  case 1:
                         printf( "¡" );
                         fprintf( ironuri , "¡" );
                         break;
                  default:
                         printf( "H" );
                         fprintf( ironuri , "H" );
                         success ++;
                         break;
              }
          }
          printf( "\n" );
          fprintf( ironuri , "\n" );
      }
      fclose( ironuri );
      if( success == 1 ){ printf( "\nŠ®¬‚Å‚·B" ); }
}