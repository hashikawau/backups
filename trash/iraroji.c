#include <stdio.h>
#include <time.h>
#define L 20


void set_num_line( int *m , int *n );
void ironuri( int m , int n , int frame[m][n] );
int count_num_black( FILE *fp );
void set_struct_r( int m , int n , struct line line[] );
void set_struct_c( int m , int n , struct line line[] );
int ident_line( char r_c , int m , int n , struct line *line , int frame[][n] );
int line_trial( struct line *line , int check_frame[] );
int check_trial( struct line *line , int copy_check_frame[] );
int paint( int ini_point[] , struct line *line , int check_frame[] , int crnt_ini_black[] , int crnt_end_black[] );
int comb_black( struct line *line );
int set_sum_point( int num_black , int ini_point[] , int sum_point[] );


struct line{
          int line_no;
          int num_frame;
          int num_black;
          int num_white;
          int det_white;
          int comp_line;
          int black[L];
          int ini_black[L];
          int end_black[L];
};


/*  F00  */
void main()
{
      time_t start_time;
      time( &start_time );
      int i , j , k;
      int m , n;
      set_num_line( &m , &n );                /*  F01  */
      printf( "m = %d , n = %d\n" , m , n );
      struct line row[m];
      struct line clm[n];
      set_struct_r( m , n , row );            /*  F04-row  */
      set_struct_c( m , n , clm );            /*  F04-column  */

      int frame[m][n];
      int *p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){ *( p_frame + i ) = 0; }

      int complete = 0;
      while( complete < m + n ){
          for( i = 0 ; i < m  ; i ++ ){
              if( row[i].comp_line ){ continue; }
              row[i].comp_line = ident_line( 'r' , m , n , &row[i] , frame );   /*  F04  */
              if( row[i].comp_line ){ complete ++; }
          }
          for( i = 0 ; i < n ; i ++ ){
              if( clm[i].comp_line ){ continue; }
              clm[i].comp_line = ident_line( 'c' , m , n , &clm[i] , frame );   /*  F04  */
              if( clm[i].comp_line ){ complete ++; }
          }
ironuri( m , n , frame );
printf( "\n" );
      }

      printf( "\n" );
      ironuri( m , n , frame );                             /*  F01  */
      printf( "所要時間  %d  秒" , time(NULL) - start_time );
}


/*  F09  */
int comb_black( struct line *line )
{
      int i;
      int j = 0;

      int ini_point[line->num_black];
      for( i = 0 ; i < line->num_black ; i ++ ){ ini_point[i] = line->ini_black[i]; }

      int previous_tail;
      while( ini_point[0] <= line->end_black[0] ){
          j ++;
          ini_point[line->num_black - 1] ++;

          if( j < 0 ){ return 0; }                                         /**/

          ini_point[line->num_black - 1] ++;

          for( i = line->num_black - 1 ; i > 0 ; i -- ){
              if( ini_point[i] > line->end_black[i] ){
                  ini_point[i] = line->ini_black[i];
                  ini_point[i - 1] ++;
              }
          }

          previous_tail = ini_point[0];
          for( i = 0 ; i < line->num_black ; i ++ ){
              if ( previous_tail > ini_point[i] ){
                  ini_point[i] = previous_tail;
              }
              previous_tail += line->black[i] + 1;
          }
      }

      return 1;
}

/*  F08  */
int paint( int ini_point[] , struct line *line , int check_frame[] , int crnt_ini_black[] , int crnt_end_black[] )
{
      int i , j , k;
      
      int copy_check_frame[line->num_frame];
      for( i = 0 ; i < line->num_frame ; i ++){ copy_check_frame[i] = check_frame[i]; }

      int temp_black_point[line->num_black];

      for( i = 0 ; i < line->num_black ; i ++ ){
          for( j = ini_point[i] ; j < ini_point[i] + line->black[i] ; j ++ ){
              if( copy_check_frame[j] == -200 ){ return 0;}                         /**/
              else                             { copy_check_frame[j] = -1; }
          }
          temp_black_point[i] = ini_point[i];
      }

      if( check_trial( line , copy_check_frame ) ){                                           /*  F07  */
          for( i = 0 ; i < line->num_frame ; i ++ ){
              if( copy_check_frame[i] == -1 && check_frame[i] >= 0 ){
                  check_frame[i] ++;
              }
          }
          for( i = 0 ; i < line->num_black ; i ++ ){
              if( temp_black_point[i] < crnt_ini_black[i] ){
                  crnt_ini_black[i] = temp_black_point[i];
              }
              if( temp_black_point[i] > crnt_end_black[i] ){
                  crnt_end_black[i] = temp_black_point[i];
              }
          }
          return 1;                /**/
      }
      else{ return 0; }           /**/
}

/*  F07  */
int check_trial( struct line *line , int copy_check_frame[] )
{
      int i , j , k;
      int previous = 0;
      int black = 0;
      int num_black = 0;

      for( i = 0 ; i < line->num_frame ; i ++ ){
          if( copy_check_frame[i] == -100
          ||  copy_check_frame[i] == -1 ){
              if( previous == 0 ){
                  num_black ++;
              }
              if( num_black > line->num_black ){ return 0; }                /**/
              black ++;
              previous = 1;
          }
          else{
              if( previous == 1 && black != line->black[num_black - 1] ){ return 0; }            /**/
              previous = 0;
              black = 0;
          }
      }
      if( num_black != line->num_black ){ return 0; }                        /**/
      if( previous == 1 && black != line->black[num_black - 1] ){ return 0; }   /**/

      return 1;                                                             /**/
}

/*  F06  */
int line_trial( struct line *line , int check_frame[] )
{
      int i , j , k;

      int ini_point[line->num_black];
      for( i = 0 ; i < line->num_black ; i ++ ){ ini_point[i] = line->ini_black[i]; }

      int crnt_ini_black[line->num_black];
      int crnt_end_black[line->num_black];
      for( i = 0 ; i < line->num_black ; i ++ ){
          crnt_ini_black[i] = line->end_black[i];
          crnt_end_black[i] = line->ini_black[i];
      }

/*      if( !comb_black( line ) ){ return -10000; }  */                                 /**/     /*  F09  */

      int count_trial = 0;
      int previous_tail;
      while( ini_point[0] <= line->end_black[0] ){
          if( paint( ini_point , line , check_frame , crnt_ini_black , crnt_end_black ) ){               /*  F08  */
              count_trial ++;
          }
          ini_point[line->num_black - 1] ++;

          for( i = line->num_black - 1 ; i > 0 ; i -- ){
              if( ini_point[i] > line->end_black[i] ){
                  ini_point[i] = line->ini_black[i];
                  ini_point[i - 1] ++;
              }
          }

          previous_tail = ini_point[0];
          for( i = 0 ; i < line->num_black ; i ++ ){
              if ( previous_tail > ini_point[i] ){
                  ini_point[i] = previous_tail;
              }
              previous_tail = ini_point[i] + line->black[i] + 1;
          }
      }
      for( i = 0 ; i < line->num_black ; i ++ ){
          line->ini_black[i] = crnt_ini_black[i];
          line->end_black[i] = crnt_end_black[i];
      }
      return count_trial;                                 /*--F05--*/
}

/*  F05  */
int ident_line( char r_c , int m , int n , struct line *line , int frame[][n] )
{
      int i , j , k , l;
      int *x , *y;
      int *temp_frame[line->num_frame];
      int check_frame[line->num_frame];

      if( r_c == 'r' ){
          x = &line->line_no;
          y = &i;
      }
      if( r_c == 'c' ){
          x = &i;
          y = &line->line_no;
      }

      for( i = 0 ; i < line->num_frame ; i ++){ temp_frame[i] = &frame[*x][*y]; }
      for( i = 0 ; i < line->num_frame ; i ++){ check_frame[i] = *temp_frame[i]; }

      int num_blank = 0;
      int count_trial;
      count_trial = line_trial( line , check_frame );                          /*  F06  */
      if( count_trial == -10000 ){ return 0; }                                /*--F00--*/

      for( i = 0 ; i < line->num_frame ; i ++ ){
          if( check_frame[i] == 0 ){
              *temp_frame[i] = -200;
              line->det_white ++;
          }
          else{
              if( check_frame[i] == count_trial ){ *temp_frame[i] = -100; }
              else{
                  if( check_frame[i] >= 0 ){
                      *temp_frame[i] = 0;
                      num_blank ++;
                  }
              }
          }
      }

      if( num_blank ){ return 0; }                             /**/
      return 1;                                               /**/
}

/*  F04-column  */
void set_struct_c( int m , int n , struct line line[] )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;
      int sum;

      fp_char = fopen( "iraroji_column.txt" , "r" );
      fp_int = fopen( "iraroji_column.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          sum = -1;
          line[i].num_black = count_num_black( fp_char );      /*  F03  */
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &line[i].black[j] );
              sum += line[i].black[j] + 1;
          }
          line[i].line_no = i;
          line[i].num_frame = m;
          line[i].num_white = m - sum;
          line[i].det_white = 0;
          line[i].comp_line = 0;
          sum = 0;
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              line[i].ini_black[j] = sum;
              line[i].end_black[j] = line[i].ini_black[j] + line[i].num_white;
              sum += line[i].black[j] + 1;
          }
      }
      fclose( fp_char );
      fclose( fp_int );
}

/*  F04-row  */
void set_struct_r( int m , int n , struct line line[] )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;
      int sum;

      fp_char = fopen( "iraroji_row.txt" , "r" );
      fp_int = fopen( "iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          sum = -1;
          line[i].num_black = count_num_black( fp_char );      /*  F03  */
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &line[i].black[j] );
              sum += line[i].black[j] + 1;
          }
          line[i].line_no = i;
          line[i].num_frame = n;
          line[i].num_white = n - sum;
          line[i].det_white = 0;
          line[i].comp_line = 0;
          sum = 0;
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              line[i].ini_black[j] = sum;
              line[i].end_black[j] = line[i].ini_black[j] + line[i].num_white;
              sum += line[i].black[j] + 1;
          }
      }
      fclose( fp_char );
      fclose( fp_int );
}

/*  F03  */
int count_num_black( FILE *fp )
{      
      int i;
      int num_black = 1;
      char kuro;

      while( kuro != 10 ){                  /*  enter  */
          fscanf( fp , "%c" , &kuro );
          if( kuro == 32 ){                 /*  space  */
              num_black ++;
          }
      }
      return num_black;
}

/*  F02  */
void ironuri( int m , int n , int frame[m][n] )
{
      FILE *ironuri;
      int i , j;
      int success = 1;

      ironuri = fopen( "iraroji_kotae.txt" , "w" );

printf( "    " );
for( i = 1 ; i <= n ; i ++ ){ printf( "%2d" , i + m - 1 ); }
printf( "\n" );

      for( i = 0 ; i < m ; i ++ ){

printf( "%2d  " , i );

          for( j = 0 ; j < n ; j ++ ){
              switch( frame[i][j] ){
                  case -200:
                         printf( "  " );
                         fprintf( ironuri , "  " );
                         break;
                  case -100:
                         printf( "■" );
                         fprintf( ironuri , "■" );
                         break;
                  default:
                         printf( "？" );
                         fprintf( ironuri , "？" );
                         success ++;
                         break;
              }
          }
          printf( "\n" );
          fprintf( ironuri , "\n" );
      }
      fclose( ironuri );
      if( success == 1 ){ printf( "\n完成です。\n" ); }
}

/*  F01  */
void set_num_line( int *m , int *n )
{
      int kuro;
      FILE *fp;

      fp = fopen( "iraroji_row.txt" , "r" );
      for( *m = 0 ; ( kuro = getc( fp ) ) != EOF ;  ){
          if( kuro == 10 ){ ( *m ) ++; }
      }
      fclose( fp );

      fp = fopen( "iraroji_column.txt" , "r" );
      for( *n = 0 ; ( kuro = getc( fp ) ) != EOF ;  ){
          if( kuro == 10 ){ ( *n ) ++; }
      }
      fclose( fp );
}

