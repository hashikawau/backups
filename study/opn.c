#include <stdio.h>

void main()
{
    FILE* fp;
    fp = fopen( "test.txt", "w" );
    fprintf( fp , "hello" );
    fclose( fp );

}