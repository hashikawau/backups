#include <stdio.h>
#include <math.h>

void aa( struct s * );
void bb( struct s * );
int cc( int i );
int dd( int , int );
int set_sum_point( int num_black , int ini_point[] , int sum_point[] );
int ee( int num_black , int num_white );

struct s{
      int u[4];
      int v;
      int w;
}ss[2];

void main()
{
      int i = 0;
      int j;
      int nw = 45;
      int nb = 3;
      int bi[nb];
      int num_black = 15;
      int num_white = 10;


 /*     i = ee( num_black , num_white );*/
      j = dd( num_black , num_white );

      printf( "ee = %d\ndd = %d\n" , i , j );
      
}

int dd( int num_black , int num_white )
{
      int i;
      int j = 0;

      int ini_point[num_black];
      for( i = 0 ; i < num_black ; i ++ ){ ini_point[i] = 0; }

      int sum_point[num_black];
      int key_sum_point;
      key_sum_point = set_sum_point( num_black , ini_point , sum_point );

      while( ini_point[num_black - 1] <= num_white ){
          j ++;
          ini_point[0] ++;

          for( i = 0 ; i < num_black - 1 ; i ++ ){
              if( ini_point[i] > num_white - sum_point[i] ){
                  ini_point[i] = 0;
                  ini_point[i + 1] ++;
                  key_sum_point = 1;
              }
          }

          if( key_sum_point ){ key_sum_point = set_sum_point( num_black , ini_point , sum_point ); }
      }

      return j;
}

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

int ee( int num_black , int num_white )
{
      int i;
      int j = 0;

      int ini_point[num_black];
      for( i = 0 ; i < num_black ; i ++ ){ ini_point[i] = 0; }

      int sum;
      while( ini_point[num_black - 1] <= num_white ){
          for( i = 0 ; i < num_black - 1 ; i ++ ){
              if( ini_point[i] > num_white ){
                  ini_point[i] = 0;
                  ini_point[i + 1] ++;
              }
          }
          sum = 0;
          for( i = 0 ; i < num_black ; i ++ ){ sum += ini_point[i]; }
          if( sum <= num_white ){ j ++; }
          ini_point[0] ++;
      }

      return j;
}













void aa( struct s *s1 )
{
      int i;

      
      for( i = 0 ; i < 4 ; i ++ ){
          printf( "aa%d\n" , s1->u[i] );
      }
      bb( s1 );
}

void bb( struct s *s1 )
{
      int i;

      for( i = 0 ; i < 4 ; i ++ ){
          printf( "bb%d\n" , s1->u[i] );
      }
}

int cc( int i )
{
      int t[10];
      int *tt = &t[0];
      for( i = 0 ; i < 10 ; i ++ ){ t[i] = i; }
      int s[10];

      printf( "%d\n" , i );

      return i;
}


























