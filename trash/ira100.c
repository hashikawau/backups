#include <stdio.h>
#define L 20

struct black{
      int b_number;
      int b_sum;
      int w_sum;
      int line_number;
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
      ironuri( m , n , frame );

}

/*  F01  */
void set_black_points( struct black *line )
{
      int i , j , k;
      int temp_sum = 0;

      for( i = 0 ; i < line->b_number ; i ++ ){
          line->head_first[i] = temp_sum;
          line->head_last[i] = line->head_first[i] + line->black[i];
          line->end_first[i] = line->head_first[i] + line->w_sum;
          line->end_last[i] = line->end_first[i] + line->black[i];
          temp_sum += line->black[i] + 1;
      }
}

/*  F02  */
void black_or_white( char r_c , int nth , struct black *line , int m , int n , int frame[][n] )
{
      int i , j;
      int det;

      for( i = 0 ; i < line->b_number ; i ++ ){
          det = line->b_sum + line->black[i] - line->line_number;
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

      for( i = 0 ; i < m ; i ++ ){
          temp_sum = 0;
          for( j = 0 ; j < row[i].b_number ; j ++ ){
              temp_sum += row[i].black[j];
          }
          row[i].b_sum = temp_sum + row[i].b_number - 1;
          row[i].w_sum = n - row[i].b_sum;
          row[i].line_number = m;
      }
      for( i = 0 ; i < n ; i ++ ){
          temp_sum = 0;
          for( j = 0 ; j < column[i].b_number ; j ++ ){
              temp_sum += column[i].black[j];
          }
          column[i].b_sum = temp_sum + column[i].b_number - 1;
          column[i].w_sum = m - column[i].b_sum;
          column[i].line_number = n;
      }
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