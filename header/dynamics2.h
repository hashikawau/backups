#include <iostream.h>
#include <windows.h>
#include <math.h>
#include "tens2_header.h"

int WindowInitX  = 0;
int WindowInitY  = 0;
int WindowWidth  = 800;
int WindowHeight = 600;
int sleeptime    = 10;
static int dot_x = 0;
static int dot_y = 0;
//Tensor2<int> iPosMatrix(1,2,ORIGIN,DYNAMIC);



void init(void)
{
    static Tensor2<int> iPosMatrix(2,2,ORIGIN,DYNAMIC);
    iPosMatrix(0,0) = 300;
    iPosMatrix(0,1) = 300;
    
    return;
}

