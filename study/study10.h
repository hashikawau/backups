#include <iostream.h>
#include <math.h>
#include "longd.h"

int exp1();
int exp2();
void show1(long double *, char*);
void show2(long double *, char*);

int exp1()
{
    int ndata = 6;
    long double g   = 9.8;
    long double T   = 22;
    long double H   = 0.395;
    long double rho = 1261;
    long double mu  = 1.247;
    long double sec[]         = { 0.86, 0.69, 0.86, 0.47, 0.47, 0.44 };//sec
    long double mass[]        = { 6.0, 6.4, 5.7, 8.3, 3.5, 2.0 };   //gram
    long double diameter[][3] = { 16.60, 16.59, 16.67,
                                  16.98, 16.92, 16.94,
                                  16.27, 16.39, 16.29,
                                  12.72, 12.73, 12.72,
                                   9.54,  9.61,  9.56,
                                   7.97,  7.98,  7.96 };   //mili meter
                
    long double dm[ndata];
    long double A[ndata];
    long double V[ndata];
    long double U[ndata];
    long double Re[ndata];
    long double D1[ndata];
    long double D2[ndata];
    long double Cd1[ndata];
    long double Cd2[ndata];
    long double Fg[ndata];
    long double Ff[ndata];
                
    for( int i=0; i<6; i++ )
    {
        mass[i] /= 100;
        dm[i]  = mean(3, diameter[i]);
        dm[i] /= 1000;
        A[i]   = M_PI*dm[i]*dm[i]/4;
        V[i]   = M_PI*dm[i]*dm[i]*dm[i]/6;
        U[i]   = H/sec[i];
        Re[i]  = rho*U[i]*dm[i]/mu;
        Fg[i]  = mass[i]*g;
        Ff[i]  = rho*V[i]*g;
        D1[i]  = mass[i]*g - rho*V[i]*g;
        D2[i]  = M_PI*3*mu*dm[i]*U[i];
        Cd1[i] = (2*D1[i])/(rho*U[i]*U[i]*A[i]);
        Cd2[i] = (2*D2[i])/(rho*U[i]*U[i]*A[i]);
    }
    
    
    //show1(mass, "mass");
    //show1(dm, "L");
    //show1(A,  "A");
    //show1(V,  "V");
    //show1(U,  "U");
    show1(Re, "Re");
    show1(D1, "D1");
    show1(D2, "D2");
    show1(Cd1, "Cd1");
    show1(Cd2, "Cd2");
    show1(Fg,  "Fg");
    show1(Ff,  "Ff");
    
    return 0;
}

void show1(long double pld[], char *msg)
{
    cout << msg << endl;
    for( int i=0; i<6; i++ )
    {
        cout << pld[i] << endl;
    }
    cout << endl;
}

int exp2()
{
    int ndata = 5;
    long double g = 9.8;
    long double rhoW = 0.9975;
    long double rhoA = 1.180;
    long double muA  = 0.0000180;
    long double diameter = 0.091;//m
    long double S = M_PI*diameter*diameter/4;
    long double mass = 0.034;    //kg
    long double pitot[] = { 1.6  , 4.0  , 6.0  , 8.2  , 11   };  //mm
    long double F[][5]  = { 0.75 , 1.375, 1.5  , 1.875, 2.125,
                            0.625, 1.25 , 1.5  , 1.75 , 2.0  ,
                            0.625, 1.2  , 1.5  , 1.875, 2.5  };  //N
    long double F0 = 0.315;
    long double U[ndata];
    long double Re[ndata];
    long double D[3][ndata];
    long double Cd[3][ndata];
    
    for( int i=0; i<ndata; i++ )
    {
        U[i]  = sqrt( 2*rhoW*g*pitot[i]/rhoA );
        Re[i] = rhoA*U[i]*diameter/muA;
        for( int j=0; j<3; j++ )
        {
            D[j][i]  = ( F[j][i] - F0 )*14/54;
            Cd[j][i] = ( D[j][i]*2 )/( rhoA*U[i]*U[i]*S );
        }
    }
    
    //show2(U, "U");
    show2(Re, "Re");
    for( int i=0; i<3; i++ )
    {
        //show2(D[i], "D");
        show2(Cd[i], "Cd");
    }
    
    return 0;
}

void show2(long double pld[], char *msg)
{
    cout << msg << endl;
    for( int i=0; i<5; i++ )
    {
        cout << pld[i] << endl;
    }
    cout << endl;
}