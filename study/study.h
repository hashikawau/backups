#include <iostream.h>
#include <math.h>

long double calcCd( long double, double, double, double );

int study()
{
    cout << (long double)( 1.449 + (0.945-1.449)*2/5 );
    
    double g = 9.8;
    double temper   = 22;
    double lenfall  = 39.5;
    double densgris = 1261;
    double viscgris = 1.247;
    double secfall[6] = { 0.86, 0.69, 0.86, 0.47, 0.47, 0.44 };
    double mass[6] = { 6.0, 6.4, 5.7, 8.3, 3.5, 2.0 };
    double diameter[6][3] = { 16.60, 16.59, 16.67,
                              16.98, 16.92, 16.94,
                              16.27, 16.39, 16.29,
                              12.72, 12.73, 12.72,
                               9.54,  9.61,  9.56,
                               7.97,  7.98,  7.96 };
    long double U,
                Srf,
                Vol,
                Re,
                D;
                dm[6];
    for( int i=0; i<6; i++ )
    {
        dm[i] = 0;
        
        for( int j=0; j<3; j++ )
        {
            dm[i] += diameter[i][j];
        }
        
        dm[i] /= 3;
    }
    
    cout << "Cd by 1" << endl;
    for( int i=0; i<6; i++ )
    {
        U   = lenfall/secfall[i];
        Srf = M_PI*dm[i]*dm[i];
        Vol = M_PI*dm[i]*dm[i]*dm[i]/6;
        Re  = (densgris[i] * dm[i] * lenfall)/( secfall[i] * viscgris );
        D   = mass[i]*g - densgris*Vol;
        cout << "Re    = " << Re << endl;
        cout << "Cd[" << i << "] = "
             << calcCd( D, densgris, U, Srf )
             << endl << endl;
    }
    
    return 0;
}

long double calcCd( long double D, double r, double U, double S )
{
    return (2*D)/(r*U*U*S);
}