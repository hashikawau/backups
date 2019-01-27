#include <stdio.h>
#define L 20

struct black{
      int b_number;
      int b_sum;
      int w_sum;
      int line_comp;
      int black[L];
      int black_comp[L];
      int head_first[L];
      int head_last[L];
      int end_first[L];
      int end_last[L];
};

void set_black_points( struct black *line , int num_frame );
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
      }   }
      struct black row[m];
      struct black column[n];
      int line_comp;

      set_struct( row , column , m , n );        /*  F03  */

   for( j = 0 ; j < 100 ; j ++ ){
      line_comp = 0;
      for( i = 0 ; i < m ; i ++ ){
          if( row[i].line_comp == 0 ){
              black_or_white( 'r' , i , &row[i] , m , n , frame );
          }
          if( column[i].line_comp == 0 ){
              black_or_white( 'c' , i , &column[i] , m , n , frame );
          }
          line_comp += row[i].line_comp + column[i].line_comp;
      }
      if( line_comp == m + n ){ break; }
      ironuri( m , n , frame );
   }
      ironuri( m , n , frame );

}

/*  F01  */
void set_black_points( struct black *line , int num_frame )
{
      int i , j , k;
      int temp_sum1 = 0;
      int temp_sum2 = 0;

      for( i = 0 ; i < line->b_number ; i ++ ){
          temp_sum1 += line->black[i];
      }
      line->b_sum = temp_sum1 + line->b_number - 1;
      line->w_sum = num_frame - line->b_sum;

      for( i = 0 ; i < line->b_number ; i ++ ){
          line->head_first[i] = temp_sum2;
          line->head_last[i] = line->head_first[i] + line->black[i];
          line->end_first[i] = line->head_first[i] + line->w_sum;
          line->end_last[i] = line->end_first[i] + line->black[i];
          temp_sum2 += line->black[i] + 1;
          line->black_comp[i] = 0;
      }
      line->line_comp = 0;
}

/*  F02  */
void black_or_white( char r_c , int nth , struct black *line , int m , int n , int frame[][n] )
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

      int unknown = 0;
      int black = 0;
      int white = 1;
      int count = 0;
      int count_pre = 0;
      int count_nxt = 1;
      int count_black_comp = 0;

      for( i = 0 ; i < l ; i ++ ){
          switch( frame[*x][*y] ){
              case 0:
                     if( black > 0 ){
                         if( count == line->b_number || black + unknown <= line->black[count] + line->black[count_nxt] ){
                             line->head_last[count] = i - 1;
                             line->end_first[count] = i - line->black[count];
                         }
                     }
                     unknown = 0;
                     black = 0;
                     white = 1;
                     break;
              case 1:
                     if( white == 1 ){
                         line->head_last[count] = i + line->black[count];
                         line->end_first[count] = i;
                         line->black_comp[count] = 1;
                         count_black_comp ++; 
                         count_pre = count;
                         count ++;
                         count_nxt ++;
                     }
                     if( unknown > 0 && unknown < line->black[count] ){
                         line->end_first[count] = i;
                     }
                     black ++;
                     white = 0;
                     break;
              default:
                     unknown ++;
                     white = 0;
                     if( black > 0 && line->black_comp[count_pre] == 1 ){
                         frame[*x][*y] = 0;
                         unknown = 0;
                         white = 1;
                     }
                     black = 0;
                     break;
          }
      }
      if( count_black_comp == line->b_number || line->black[0] == 0 ){
          for( i = 0 ; i < l ; i ++ ){
              frame[*x][*y] = 0;
          }
          line->line_comp = 1;
      }

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

/*  F03 (01 , 04) */
void set_struct( struct black row[] , struct black column[] , int m , int n )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;

      fp_char = fopen( "iraroji_row.txt" , "r" );
      fp_int = fopen( "iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          row[i].b_number = count_b_number( fp_char );           /*  F04  */
          for( j = 0 ; j < row[i].b_number ; j ++ ){
              fscanf( fp_int , "%d" , &row[i].black[j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );
      fp_char = fopen( "iraroji_column.txt" , "r" );
      fp_int = fopen( "iraroji_column.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          column[i].b_number = count_b_number( fp_char );        /*  F04  */
          for( j = 0 ; j < column[i].b_number ; j ++ ){
              fscanf( fp_int , "%d" , &column[i].black[j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );

      for( i = 0 ; i < m ; i ++ ){
          set_black_points( &row[i] , n );               /*  F01  */
      }
      for( i = 0 ; i < n ; i ++ ){
          set_black_points( &column[i] , m );             /*  F01  */
      }
}

/*  F04  */
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

/*  F05  */
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
      if( success == 1 ){ printf( "\nŠ®¬‚Å‚·B\n" ); }
}






























