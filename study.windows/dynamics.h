#include <math.h>

int WindowInitX  = 0;
int WindowInitY  = 0;
int WindowWidth  = 800;
int WindowHeight = 600;
int sleeptime    = 60;
static int dot_x = 0;
static int dot_y = 0;
static int time  = 0; 

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
    dot_x = 30*time;
    dot_y = (time-0)*(time-10)*(time-20)/5 + 100;
    time++;
    time %= 30;
}