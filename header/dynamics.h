#include <windows.h>
#include <math.h>
#include "header.h"

int WindowInitX  = 0;
int WindowInitY  = 0;
int WindowWidth  = 800;
int WindowHeight = 600;
int sleeptime    = 10;
static int dot_x = 0;
static int dot_y = 0;
static int currtime  = 0;

int pos_x[4] = { 300, 300, 350, 350 };
int pos_y[4] = { 300, 350, 350, 300 };

int r[4]   = { 0, 50,  50,  50  };
int deg[4] = { 0, 9000, 9000, 9000 };
double dt[4] = { 0, 1, 0, 0 };

class dynamics
{
    double Px, Py, Pz;
    double Vx, Vy, Vz;
    double Ax, Ay, Az;
    double Xx, Xy, Xz;
public:
    dynamics()
    {
        
    }
//    setPosition()
};

void Action()
{
    dot_x = 30*currtime;
    dot_y = (currtime-0)*(currtime-10)*(currtime-20)/5 + 100;
    currtime++;
    currtime %= 30;
}

void init()
{
}
void rotation()
{
    double theta0[4];
    double theta[4];
    double dtheta[4];
    dtheta[1] = dt[1]*M_PI/180;
    theta[0] = theta0[0] = 0;
    for( int i=1; i< 4; i++ )
    {
        theta0[i] = deg[i]*M_PI/18000;
        theta[i] = 0;
        for( int j=1; j<=i; j++ )
        {
            theta[i] += theta0[j];
        }
    }
    
    Tensor2<> tens(2,3);
    tens.set(0,0) = -r[3]*sin(theta[3]);
    tens.set(1,0) =  r[3]*cos(theta[3]);
    tens.set(0,1) = -r[3]*sin(theta[3])-r[2]*sin(theta[2]);
    tens.set(1,1) =  r[3]*cos(theta[3])+r[2]*cos(theta[2]);
    tens.set(0,2) =  r[3]*sin(theta[3])+r[2]*sin(theta[2])+r[1]*sin(theta[1]);
    tens.set(1,2) = -r[3]*cos(theta[3])-r[2]*cos(theta[2])-r[1]*cos(theta[1]);
    //cout << "befor\n" << tens << endl;
    tens.solution();
    //cout << "after\n" << tens << endl;
    dtheta[3] = tens.set(0,0)*dtheta[1];
    dtheta[2] = tens.set(1,0)*dtheta[1];
    
    
    for( int i=1; i<4; i++ )
    {
        theta0[i] += dtheta[i];
        theta[i] = 0;
        for( int j=1; j<=i; j++ )
        {
            theta[i] += theta0[j];
        }
        pos_x[i] = r[i]*cos(theta[i]) + pos_x[i-1];
        pos_y[i] = r[i]*sin(theta[i]) + pos_y[i-1];
    }
    
    for( int i=1; i< 4; i++ )
    {
        deg[i] = (int)(theta0[i]*18000/M_PI);
        deg[i] %= 36000;
    }
    dt[2] = dtheta[2]*180/M_PI;
    dt[3] = dtheta[3]*180/M_PI;
}
