#include <stdio.h>
#include <math.h>

void main()
{
	FILE *fp;
	int n = 0;
	int fth = 45;
	float e = 0;
	float f, z;

	fp = fopen( "data2.txt" , "r" );
	while( fscanf( fp, "%f", &f ) != EOF ){
		z = (0.0000246/54/54*f*f)/sqrt((1-f*f/54/54)*(1-f*f/54/54) + f*f/25/25/27/27);
		printf( "%f %f\n", f, z*1000000 );
	}
	fclose( fp );

}