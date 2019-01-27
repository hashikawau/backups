#include <stdio.h>
#define L 20

void set_struct( int , int , struct line * , struct line * , struct info_line * );
int count_num_black( FILE *fp );
void ironuri( int m , int n , int frame[m][n] );
int ident_frame( struct line * , struct info_line * , int * );

struct line{
          int line_no;
          int num_black;
          int comp_line;
          int black[L];
          int comp_black[L];
};

struct info_line{
          int num_line;
          int num_frame;
          int temp_i;     /*  info_line[0].num_frame  ,             0              */
          int temp_j;     /*            1             ,  info_line[1].num_frame    */
}info_line[2];


void main()
{
      int i , j , k;
      int m = 1;
      int n = 10;
      struct line row[m];
      struct line clm[n];
      set_struct( m , n , row , clm , info_line );            /*  F01  */
      
      int frame[m][n];
      int *p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){ *( p_frame + i ) = 103; }

      i = ident_frame( &row[0] , &info_line[0] , p_frame );

      ironuri( m , n , frame );
}

/*  F04  */
int ident_frame( struct line *line1 , struct info_line *line2 , int frame[] )
{
      int i , j , k , l;
      int *temp_frame[line2->num_frame];

      for( i = 0 ; i < line2->num_frame ; i ++){
          temp_frame[i] = &frame[( line1->line_no * line2->temp_i ) + ( i * line2->temp_j )];
      }
*temp_frame[2] = 100;
*temp_frame[3] = 101;
      int count_num_part = 0;
      int count_num_frame = 0;
      int blank = 0;
      for( i = 0 ; i < line2->num_frame ; i ++ ){
          switch( *temp_frame[i] ){
              case 100:
                       if( blank == 1 ){
                           count_num_part ++;
                       }
                       blank = 0;
                       count_num_frame = 0;
                       break;
              case 101:
                       count_num_frame ++;
                       break;
              case 103:
                       blank = 1;
                       count_num_frame ++;
                       break;
          }
      }
      if( blank == 1 ){
          count_num_part ++;
      }

      int *ini_frame[count_num_part];
      int num_frame[count_num_part];
      count_num_part = 0;
      count_num_frame = 0;
      for( i = 0 ; i < line2->num_frame ; i ++ ){
          switch( *temp_frame[i] ){
              case 100:
                       if( blank == 1 ){
                           count_num_part ++;
                           ini_frame[count_num_part - 1] = temp_frame[i - count_num_frame];
                           num_frame[count_num_part - 1] = count_num_frame;
                       }
                       blank = 0;
                       count_num_frame = 0;
                       break;
              case 101:
                       count_num_frame ++;
                       break;
              case 103:
                       blank = 1;
                       count_num_frame ++;
                       break;
          }
      }
      if( blank == 1 ){
          count_num_part ++;
          ini_frame[count_num_part - 1] = temp_frame[i - count_num_frame];
          num_frame[count_num_part-1] = count_num_frame;
      }

      int *current_frame;
      int sum_black;
      j = 0;
      for( i = 0 ; i < count_num_part ; i ++ ){
          current_frame = ini_frame[i];
          sum_black = 0;
          for(  ; j < line1->num_black ; j ++ ){
              if( sum_black + line1->black[j] > num_frame[i] ){
                  if( sum_black == 0 ){
                      for( k = 0 ; k < num_frame[i] ; k ++ ){ *( ini_frame[i] + k ) = 100; }
                  }
                  break;
              }
              for( k = 0 ; k < line1->black[j] ; k ++ ){ *( current_frame + k ) = j; }
              current_frame += line1->black[j] + 1;
              sum_black += line1->black[j] + 1;
          }
      }

      int *end_frame[count_num_part];
      int count_black;
      for( i = count_num_part - 1 ; i >= 0 ; i -- ){ end_frame[i] = ini_frame[i] + num_frame[i] - 1; }
      j = line1->num_black - 1;
      for( i = count_num_part - 1 ; i >= 0 ; i -- ){
          current_frame = end_frame[i];
          sum_black = 0;
          for(  ; j >= 0 ; j -- ){
              if( sum_black + line1->black[j] > num_frame[i] ){
                  if( sum_black == 0 ){
                      for( k = 0 ; k < num_frame[i] ; k ++ ){ *( end_frame[i] - k ) = 100; }
                  }
                  break;
              }
              count_black = 0;
              for( k = 0 ; k < line1->black[j] ; k ++ ){
                  if( *( current_frame - k ) == 101 ){
                      l = k;
                      for(  ; l < line1->black[j] ; l ++ ){
                          *( current_frame - l ) = j;
                      }
                  }
                  if( *( current_frame - k ) == j ){
                      *( current_frame - k ) = 101;
                      count_black ++;
                  }
              }
              if( count_black == line1->black[j] ){ *( current_frame - line1->black[j] ) = 100; }
              current_frame -= ( line1->black[j] + 1 );
              sum_black += line1->black[j] + 1;
          }
      }

      for( i = 0 ; i < line2->num_frame ; i ++ ){
          if( *temp_frame[i] < 100 ){
              *temp_frame[i] = 103;
          }
      }
}

/*  F01  */
void set_struct( int m , int n , struct line row[] , struct line clm[] , struct info_line info_line[] )
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;

      fp_char = fopen( "iraroji_row.txt" , "r" );
      fp_int = fopen( "iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          row[i].num_black = count_num_black( fp_char );      /*  F02  */
          for( j = 0 ; j < row[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &row[i].black[j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );

      fp_char = fopen( "iraroji_column.txt" , "r" );
      fp_int = fopen( "iraroji_column.txt" , "r" );
      for( i = 0 ; i < n ; i ++ ){
          clm[i].num_black = count_num_black( fp_char );      /*  F02  */
          for( j = 0 ; j < clm[i].num_black ; j ++ ){
              fscanf( fp_int , "%d" , &clm[i].black[j] );
          }
      }

      for( i = 0 ; i < m ; i ++ ){ row[i].line_no = i; }
      for( i = 0 ; i < n ; i ++ ){ clm[i].line_no = i; }

      info_line[0].num_line = m;
      info_line[0].num_frame = n;
      info_line[0].temp_i = info_line[0].num_frame;
      info_line[0].temp_j = 1;

      info_line[1].num_line = n;
      info_line[1].num_frame = m;
      info_line[1].temp_i = 0;
      info_line[1].temp_j = info_line[1].num_frame;
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

/*  F03  */
void ironuri( int m , int n , int frame[m][n] )
{
      FILE *ironuri;
      int i , j;
      int success = 1;

      ironuri = fopen( "iraroji_kotae.txt" , "w" );
      for( i = 0 ; i < m ; i ++ ){
          for( j = 0 ; j < n ; j ++ ){
              switch( frame[i][j] ){
                  case 100:
                         printf( "  " );
                         fprintf( ironuri , "  " );
                         break;
                  case 101:
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





























