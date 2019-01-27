#include <stdio.h>
#include <math.h>

void main()
{
	FILE *fp;
	int n = 0;
	int cw = 45;
	float e = 0;
	float w, x[2], y[2], r;
	float xm, ym;

	fp = fopen( "data.txt" , "r" );
	while( fscanf( fp, "%f %f %f %f %f", &w, &x[0], &x[1], &y[0], &y[1] ) != EOF ){
		n ++;
		xm = 180*( x[0] + x[1] )/2 - 10.;
		ym = 180*( y[0] + y[1] )/2 + 10.;
		r = sqrt( xm*xm + ym*ym );
		e += r*sqrt( ( (cw/w)*(cw/w) - 1 )*( (cw/w)*(cw/w) - 1 ) );
		printf( "%f %f %f %f %f\n", w, x[0], x[1], y[0], y[1] );
		printf( "%d %f %f %f %f\n", n, xm, ym, r, r*sqrt( ( (cw/w)*(cw/w) - 1 )*( (cw/w)*(cw/w) - 1 ) ) );
		printf( "%f\n", e/n );
	}
	fclose( fp );


	printf( "%f\n", e/n );
}