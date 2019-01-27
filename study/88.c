#include <stdio.h>
#include <math.h>

void main()
{
	float x1, x2;
	float y1, y2;
	float x, y;
	float r;
	int a = -1;

	while( 1 ){
		scanf( "%f %f %f %f", &x1, &x2, &y1, &y2 );
		x = 180*(x1 + x2)/2 - 10;
		y = 180*(y1 + y2)/2 + 10;
		r = sqrt( x*x + y*y );
		printf( "%f\n", r );
		puts( "\n" );
	}
}