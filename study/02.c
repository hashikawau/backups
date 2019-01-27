#include <stdio.h>
#define L 20

struct black{
      int b_number;
      int b_sum;
      int w_sum;
      int black[L];
      int head_first[L];
      int head_last[L];
      int end_first[L];
      int end_last[L];
};

void set_black_points( struct black *line );
void black_or_white( char r_c , int nth , struct black *line , int m , int n , int frame[][n] );
void set_struct( struct black row[] , struct black column[] , int m , int n );
int count_b_number( FILE *fp );
void ironuri( int m , int n , int frame[m][n] );
void borw( char r_c , int nth , int m , int n , struct black *line , int frame[][n] );

void main()
{
      int i , j;
      int m = 10;
      int n = 10;
      int frame[m][n];
      for( i = 0 ; i < m ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              frame[i][j] = 3;
      } }
      struct black row[m];
      struct black column[n];

      set_struct( row , column , m , n );

      for( i = 0 ; i < m ; i ++ ){
          set_black_points( &row[i] );
          black_or_white( 'r' , i , &row[i] , m , n , frame );
          set_black_points( &column[i] );
          black_or_white( 'c' , i , &column[i] , m , n , frame );
      }
      for( i = 0 ; i < m ; i ++ ){
          borw( 'r' , i , m , n , &row[i] , frame );
          black_or_white( 'r' , i , &row[i] , m , n , frame );
          borw( 'c' , i , m , n , &column[i] , frame );
          black_or_white( 'c' , i , &column[i] , m , n , frame );
      }

      ironuri( m , n , frame );

}

/*  F01  */
void set_black_points( struct black *line )
{
      int i , j , k;
      int temp_sum = 0;
      int sum = 0;

      for( i = 0 ; i < line->b_number ; i ++ ){
          line->head_first[i] = temp_sum;
          line->head_last[i] = line->head_first[i] + line->black[i];
          line->end_first[i] = line->head_first[i] + line->w_sum;
          line->end_last[i] = line->end_first[i] + line->black[i];
          temp_sum += line->black[i] + 1;
      }
      for( i = 0 ; i < 10 ; i ++ ){
          sum = 0;
          for( j = 0 ; j < line->b_number ; j ++ ){
              sum += line->black[j];
          }
          line->b_sum = sum + line->b_number - 1;
          line->w_sum = 10 - line->b_sum;
      }
}

/*  F02  */
void black_or_white( char r_c , int nth , struct black *line , int m , int n , int frame[][n] )
{
      int i , j;
      int det;

      for( i = 0 ; i < line->b_number ; i ++ ){
          det = line->head_last[i] - line->end_first[i];
          if( det >> 0 ){
              for( j = 0 ; j < det ; j ++ ){
                  if( r_c == 'r' ){ frame[nth][line->end_first[i]+j] = 1; }
                  if( r_c == 'c' ){ frame[line->end_first[i]+j][nth] = 1; }
              }
          }
      }
          
}

/*  F03 (04) */
void set_struct( struct black row[] , struct black column[] , int m , int n )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;
      int temp_sum;

      fp_char = fopen( "iraroji_row.txt" , "r" );
      fp_int = fopen( "iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          row[i].b_number = count_b_number( fp_char );
          for( j = 0 ; j < row[i].b_number ; j ++ ){
              fscanf( fp_int , "%d" , &row[i].black[j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );
      fp_char = fopen( "iraroji_column.txt" , "r" );
      fp_int = fopen( "iraroji_column.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          column[i].b_number = count_b_number( fp_char );
          for( j = 0 ; j < column[i].b_number ; j ++ ){
              fscanf( fp_int , "%d" , &column[i].black[j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );

/*
      for( i = 0 ; i < m ; i ++ ){
          temp_sum = 0;
          for( j = 0 ; j < row[i].b_number ; j ++ ){
              temp_sum += row[i].black[j];
          }
          row[i].b_sum = temp_sum + row[i].b_number - 1;
          row[i].w_sum = n - row[i].b_sum;
      }
      for( i = 0 ; i < n ; i ++ ){
          temp_sum = 0;
          for( j = 0 ; j < column[i].b_number ; j ++ ){
              temp_sum += column[i].black[j];
          }
          column[i].b_sum = temp_sum + column[i].b_number - 1;
          column[i].w_sum = m - column[i].b_sum;
      }
*/
}

/*  F04 (03)  */
int count_b_number( FILE *fp )
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

/**/
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

/*    */
void borw( char r_c , int nth , int m , int n , struct black *line , int frame[][n] )
{
      int i , j;
      int *x , *y;
      int l;
      if( r_c == 'r' ){
          l = n;
          x = &nth;
          y = &i;
      }
      if( r_c == 'c' ){
          l = m;
          x = &i;
          y = &nth;
      }
      int p_frame[l];
      for( i = 0 ; i < l ; i ++ ){
          p_frame[i] = frame[*x][*y];
      }
      int black = 0;
      int white = 1;
      int count = 0;

      for( i = 0 ; i < l ; i ++ ){
          switch( p_frame[i] ){
              case 0:
                     white = 1;
                     black = 0;
                     break;
              case 1:
                     if( white == 1 ){
                         line->head_last[count] = i + line->black[count];
                         line->end_first[count] = i;
                         count ++;
                     }
                     white = 0;
                     black ++;
                     break;
              default:
                     white = 0;
                     black = 0;
                     break;
          }
          if( count >= line->b_number ){
              if( p_frame[i] == 3 ){
                  frame[*x][*y] = 0;
              }
          }
      }
}
