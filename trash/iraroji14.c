#include <stdio.h>

void ttt( FILE *fp ); 

void main()
{
      FILE *fp_char;
      FILE *fp_int;
      int i , j;
      int m = 10;
      int n = 10;
      int row_num_black[m];
      int colum_num_black[n];
      int row_black[m][4];
      int colum_black[n][4];

      fp_char = fopen( "iraroji_row.txt" , "r" );
      fp_int = fopen( "iraroji_row.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          row_num_black[i] = count_num_black( fp_char );
          for( j = 0 ; j < row_num_black[i] ; j ++ ){
              fscanf( fp_int , "%d" , &row_black[i][j] );
          }
      }
      fclose( fp_char );
      fclose( fp_int );

for( i = 0 ; i < m ; i ++ ){
    printf( "\n" );
    for( j = 0 ; j < row_num_black[i] ; j ++ ){
        printf( "%d " , row_black[i][j] );
    }
}

      fp_char = fopen( "iraroji_colum.txt" , "r" );
      fp_int = fopen( "iraroji_colum.txt" , "r" );
      for( i = 0 ; i < m ; i ++ ){
          colum_num_black[i] = count_num_black( fp_char );
          for( j = 0 ; j < row_num_black[i] ; j ++ ){
              fscanf( fp_int , "%d" , &colum_black[i][j] );
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