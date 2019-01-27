#include <stdio.h>
#define L 20


void ironuri( int m , int n , int frame[m][n] );
int count_num_black( FILE *fp );
void set_struct( int m , int n , struct line line[] );
int ident_line( int trial_no , int m , int n , struct line *line , int frame[][n] );
int line_trial( struct line *line , int check_frame[] );
int check_trial( struct line *line , int copy_check_frame[] );
int paint( int ini_point[] , struct line *line , int check_frame[] );
int set_sum_point( int num_black , int ini_point[] , int sum_point[] );
void set_num_line( int *m , int *n );


struct line{
          int line_no;
          int num_frame;
          int num_black;
          int num_white;
          int comp_line;
          int black[L];
};


/*  F00  */
void main()
{
      int i , j , k;
      int m = 30;
      int n = 30;
printf( "m = %d , n = %d\n" , m , n );
      struct line line[m + n];
      set_struct( m , n , line );            /*  F03  */

      int frame[m][n];
      int *p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){ *( p_frame + i ) = 0; }

      int complete = 0;
      while( complete < m + n ){
          for( i = 0 ; i < m + n ; i ++ ){
              if( line[i].comp_line ){ continue; }
              line[i].comp_line = ident_line( i , m , n , &line[i] , frame );   /*  F04  */
              if( line[i].comp_line ){ complete ++; }
          }
      }

      printf( "\n" );
      ironuri( m , n , frame );                             /*  F01  */
}

/*  F09  */
void set_num_line( int *m , int *n )
{
      FILE *fp_char;
      char read;

      fp_char = fopen( "iraroji_row.txt" , "r" );
      for( *m = 0 ; read == EOF ; *m ++ ){
          read = getc( fp_char );
          if( read != 10 ){ continue; }
      }
      fclose( fp_char );

      fp_char = fopen( "iraroji_column.txt" , "r" );
      for( *n = 0 ; read != EOF ; *n ++ ){
          read = getc( fp_char );
      }
      fclose( fp_char );
printf( "%d %d\n" , *m , *n );
}

/*  F08  */
int set_sum_point( int num_black , int ini_point[] , int sum_point[] )
{
      int i;
      int sum = 0;

      for( i = num_black - 1 ; i >= 0 ; i -- ){
          sum_point[i] = sum;
          sum += ini_point[i];
      }

      return 0;
}

/*  F07  */
int paint( int ini_point[] , struct line *line , int check_frame[] )
{
      int i , j;
      
      int copy_check_frame[line->num_frame];
      for( i = 0 ; i < line->num_frame ; i ++){ copy_check_frame[i] = check_frame[i]; }

      j = 0;
      int current_frame;
      for( i = 0 ; i < line->num_black ; i ++ ){
          j += ini_point[i];
          current_frame = j;
          for(  ; j < current_frame + line->black[i] ; j ++ ){
              if( copy_check_frame[j] == -200 ){ return 0; }                    /**/
              copy_check_frame[j] = 100;
          }
          j ++;
      }
      if( check_trial( line , copy_check_frame ) ){                                           /*  F06  */
          for( i = 0 ; i < line->num_frame ; i ++ ){
              if( copy_check_frame[i] == 100 && check_frame[i] >= 0 ){
                  check_frame[i] ++;
              }
          }
          return 1;                /**/
      }
      else{ return 0; }           /**/
}

/*  F06  */
int check_trial( struct line *line , int copy_check_frame[] )
{
      int i , j , k;
      int previous = 0;
      int black = 0;
      int num_black = 0;

      for( i = 0 ; i < line->num_frame ; i ++ ){
          if( copy_check_frame[i] == -100
          ||  copy_check_frame[i] ==  100 ){
              if( previous == 0 ){
                  num_black ++;
                  black ++;
              }
              else{
                  black ++;
              }
              if( num_black > line->num_black ){ return 0; }                /**/
              previous = 1;
          }
          else{
              if( previous == 1 && black != line->black[num_black - 1] ){ return 0; }            /**/
              previous = 0;
              black = 0;
          }
      }
      if( num_black != line->num_black ){return 0; }                        /**/
      if( previous == 1 && black != line->black[num_black - 1] ){ return 0; }   /**/
      
      return 1;
}

/*  F05  */
int line_trial( struct line *line , int check_frame[] )
{
      int i , j;

      int ini_point[line->num_black];
      for( i = 0 ; i < line->num_black ; i ++ ){ ini_point[i] = 0; }

      int sum_point[line->num_black];
      int key_sum_point;
      key_sum_point = set_sum_point( line->num_black , ini_point , sum_point );       /*  F08  */

      int count_trial = 0;
      while( ini_point[line->num_black - 1] <= line->num_white ){
          if( paint( ini_point , line , check_frame ) ){                           /*  F07  */
              count_trial ++;
              if( count_trial < 0 ){ return -10000; }                          /**/
          }
          ini_point[0] ++;

          for( i = 0 ; i < line->num_black - 1 ; i ++ ){
              if( ini_point[i] > line->num_white - sum_point[i] ){
                  ini_point[i] = 0;
                  ini_point[i + 1] ++;
                  key_sum_point = 1;
              }
          }

          if( key_sum_point ){ key_sum_point = set_sum_point( line->num_black , ini_point , sum_point ); }   /*  F08  */
      }

      return count_trial;
}

/*  F04  */
int ident_line( int trial_no , int m , int n , struct line *line , int frame[][n] )
{
      int i , j , k , l;
      int *x , *y;
      int *temp_frame[line->num_frame];
      int check_frame[line->num_frame];

      if( trial_no < m ){
          x = &line->line_no;
          y = &i;
      }
      if( trial_no >= m ){
          x = &i;
          y = &line->line_no;
      }
      for( i = 0 ; i < line->num_frame ; i ++){ temp_frame[i] = &frame[*x][*y]; }
      for( i = 0 ; i < line->num_frame ; i ++){ check_frame[i] = *temp_frame[i]; }

      int num_blank = 0;
      int count_trial;
      count_trial = line_trial( line , check_frame );                          /*  F05  */
      if( count_trial == -10000 ){ return 0; }                                /**/

      for( i = 0 ; i < line->num_frame ; i ++ ){
          if( check_frame[i] == 0 ){ *temp_frame[i] = -200; }
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

      if( num_blank ){ return 0; }
      return 1;
}

/*  F03  */
void set_struct( int m , int n , struct line line[] )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;
      int sum;

      fp_char = fopen( "neko-iraroji_row.txt" , "r" );
      fp_int = fopen( "neko-iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          sum = -1;
          line[i].num_black = count_num_black( fp_char );      /*  F02  */
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &line[i].black[j] );
              sum += line[i].black[j] + 1;
          }
          line[i].line_no = i;
          line[i].num_frame = n;
          line[i].num_white = n - sum;
          line[i].comp_line = 0;
      }
      fclose( fp_char );
      fclose( fp_int );

      fp_char = fopen( "neko-iraroji_column.txt" , "r" );
      fp_int = fopen( "neko-iraroji_column.txt" , "r" );
      for( i = m ; i < m + n ; i ++ ){
          sum = -1;
          line[i].num_black = count_num_black( fp_char );      /*  F02  */
          for( j = 0 ; j < line[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &line[i].black[j] );
              sum += line[i].black[j] + 1;
          }
          line[i].line_no = i - m;
          line[i].num_frame = m;
          line[i].num_white = m - sum;
          line[i].comp_line = 0;
      }
}

/*  F02  */
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

/*  F01  */
void ironuri( int m , int n , int frame[m][n] )
{
      FILE *ironuri;
      int i , j;
      int success = 1;

      ironuri = fopen( "iraroji_kotae.txt" , "w" );
      for( i = 0 ; i < m ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              switch( frame[i][j] ){
                  case -200:
                         printf( "  " );
                         fprintf( ironuri , "  " );
                         break;
                  case -100:
                         printf( "��" );
                         fprintf( ironuri , "��" );
                         break;
                  default:
                         printf( "�H" );
                         fprintf( ironuri , "�H" );
                         success ++;
                         break;
              }
          }
          printf( "\n" );
          fprintf( ironuri , "\n" );
      }
      fclose( ironuri );
      if( success == 1 ){ printf( "\n�����ł��B\n" ); }
}

