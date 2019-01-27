#include <stdio.h>
#define L 20

void ident_frame( struct line *line1 , struct info_line *line2 , int *frame[] );

struct line{
          int line_no;      /*  0 + 50xi  */
          int num_black;    /*  1         */
          int comp_line;    /*  2         */
          int nothing[7];
          int black[L];     /*  10 +      */
          int comp_black[L];/*  30 +      */
          
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
      int m , n , m_or_n;
      m = 1;
      n = 10;
      if( m >= n ){ m_or_n = m; }
      else        { m_or_n = n; }
      int frame[m][n];
      int *p_frame = &frame[0][0];
      for( i = 0 ; i < m * n ; i ++ ){
          *( p_frame + i ) = 103;
      }
      struct line line[2][m_or_n];
      int *temp_frame[m_or_n];

      k = 0;
      for( i = 0 ; i < info_line[k].num_line ; i ++ ){
          for( j = 0 ; j < info_line[k].num_frame ; j ++){
              temp_frame[j] = ( p_frame ) + ( i * info_line[k].temp_i ) + ( j * info_line[k].temp_j );
          }
          ident_frame( line[k][i] , info_line[k] , &temp_frame[0] );
      }
}

void ident_frame( struct line *line1 , struct info_line *line2 , int *frame[] )
{
      int i , j , k;
      int count_num_part = 0;
      int count_num_frame = 0;
      int *p_ini_part;
      int *p_num_frame;
      int blank = 0;

      for( i = 0 ; i < line2->num_frame ; i ++ ){
          switch( *frame[i] ){
              case 100:
                       if( blank == 1 ){
                           count_num_part ++;
                           *( p_ini_part + count_num_part - 1 ) = i - count_num_frame;
                           *( p_num_frame + count_num_part - 1 ) = count_num_frame;
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
          *( p_ini_part + count_num_part - 1 ) = ( line2->num_frame - 1 ) - count_num_frame;
          *( p_num_frame + count_num_part - 1 ) = count_num_frame;
      }

      int *ini_part[count_num_part];
      int *num_frame[count_num_part];
      for( i = 0 ; i < count_num_part ; i ++ ){
          ini_part[i] = p_ini_part + i;
          num_frame[i] = p_num_frame + i;
      }
      int **p_p[count_num_part];
      for( i = 0 ; i < count_num_part ; i ++ ){
          *p_p[i] = p_ini_part + i;
      }

      int *current_frame;
      int sum_black;
      j = 0;
      for( i = 0 ; i < count_num_part ; i ++ ){
          current_frame = *p_p[i];
          sum_black = 0;
          for(  ; j < line1->num_black ; j ++ ){
              if( sum_black + line1->black[j] > *( p_num_frame + j ) ){
                  if( sum_black == 0 ){
                      for( k = 0 ; k < 
                  }
                  break;
              }
              current_frame += line1->black[j];
          }
      }
}





















	