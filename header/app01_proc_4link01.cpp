#include <windows.h>
#include "tensor2.h"

int sleeptime = 30;
int numCalc = 16;
double xy_ratio = 1e2;

int x_orig = 150;
int y_orig = 200;
int passtime = 0;
Tensor2<double> pointMatrix(3,5);
Tensor2<double> pointMatrix2(3,5);
Tensor2<int> drawPos(3,2);

void init();
void actn(Tensor2<double>& pMatrix);
void drawp(HDC &hdc, Tensor2<double>& pMatrix);
void actn2();

/*
extern int sleeptime;
extern int numCalc;
extern double xy_ratio;

extern int x_orig;
extern int y_orig;
extern int passtime;

extern Tensor2<double> pointMatrix;
extern Tensor2<double> pointMatrix2;
extern Tensor2<int> drawPos;

void init();
void actn(Tensor2<double>& pMatrix);
void drawp(HDC &hdc, Tensor2<double>& pMatrix);
void actn2();
*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    static HDC pointp;
    PAINTSTRUCT ps;
    static int isDrawing;
    
    switch(msg)
    {
        case WM_CREATE:
            
            isDrawing = 0;
            
            SetTimer( hWnd, 1, sleeptime, NULL );
            
            return 0;    
            
        case WM_TIMER:
        
            Sleep(sleeptime);
            
            if( isDrawing )
            {
                InvalidateRect( hWnd, NULL, true );
            }
            
            return 0;
            
        case WM_LBUTTONDOWN:
            
            hdc = GetDC(hWnd);
            
            Ellipse(hdc, 0,0,100,100);
            SetPixel(hdc, 50, 50, 0xFF);
            
            ReleaseDC(hWnd, hdc);
            
            return 0;
        
        case WM_PAINT:
            
            hdc = BeginPaint( hWnd, &ps );
            
            if( isDrawing )
            {
                for(int i=0; i< numCalc; i++ )
                {
                    actn(pointMatrix); //======================
                    actn(pointMatrix2); //======================
                }
                
                drawp(hdc,pointMatrix);
                drawp(hdc,pointMatrix2);
                
                storTensor2.clear();
            }
            
            EndPaint( hWnd, &ps );
            
            return 0;
            
            
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_SPACE:
                    if( !isDrawing )
                    {
                        init();//================
                        
                        isDrawing = 1;
                    }
                    else
                    {
                        isDrawing = 0;
                    }
                    
                    break;
                    
                case VK_RETURN:
                    KillTimer( hWnd, 1 );
                    PostQuitMessage(0);
                    
                    break;
                    
                default:
                    break;
            }
            
            return 0;
            
        case WM_DESTROY:
        
            KillTimer( hWnd, 1 );
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}


void init()
{
    passtime = 0;
    
    pointMatrix(0,0) = 0;         // x
    pointMatrix(0,1) = 1;         // y
    pointMatrix(0,2) = 1;         // radius
    pointMatrix(0,3) = M_PI_2;         // theta
    pointMatrix(0,4) = 0.001;      // dtheta
    
    pointMatrix(1,0) = 1;
    pointMatrix(1,1) = 1;
    pointMatrix(1,2) = 1;
    pointMatrix(1,3) = 0;
    pointMatrix(1,4) = 0;
    
    pointMatrix(2,0) = 1;
    pointMatrix(2,1) = 0;
    pointMatrix(2,2) = 1;
    pointMatrix(2,3) = -M_PI_2;
    pointMatrix(2,4) = 0;
    
    pointMatrix2(0,0) = 0;         // x
    pointMatrix2(0,1) = 1;         // y
    pointMatrix2(0,2) = 1;         // radius
    pointMatrix2(0,3) = 0;         // theta
    pointMatrix2(0,4) = 0.001;      // dtheta
    
    pointMatrix2(1,0) = 1;
    pointMatrix2(1,1) = 1;
    pointMatrix2(1,2) = 1;
    pointMatrix2(1,3) = 0;
    pointMatrix2(1,4) = 0;
    
    pointMatrix2(2,0) = 1;
    pointMatrix2(2,1) = 0;
    pointMatrix2(2,2) = 2;
    pointMatrix2(2,3) = M_PI;
    pointMatrix2(2,4) = 0;
}

void actn(Tensor2<double>& pMatrix)
{
    Tensor2<double> equationMatrix(3,2);
    for( int i=0; i< pMatrix.getRow(); i++ )
    {
        equationMatrix(i,0) = -pMatrix(i,2) *sin(pMatrix(i,3));
        equationMatrix(i,1) =  pMatrix(i,2) *cos(pMatrix(i,3));
    }
    equationMatrix &= -equationMatrix(0,0,1,2);
    //equationMatrix(3,0) += 1;
    equationMatrix = ~(equationMatrix(1,0,3,2).trans());
    
    if(equationMatrix(1,1))
    {
        pMatrix(1,4,2,1) = pMatrix(0,4) *equationMatrix(0,2,2,1);
    }
    else
    {
        pMatrix(1,4) = pMatrix(0,4) *equationMatrix(0,2)
                      -pMatrix(2,4) *equationMatrix(0,1);
        
    }
    pMatrix(0,3,3,1) += pMatrix(0,4,3,1);
    pMatrix %= 2*M_PI;
    
    Tensor2<double> temp(1,2,tens2::stable);
    temp.zeros();
    for( int i=0; i< pointMatrix.getRow(); i++ )
    {
        pMatrix(i,0) = pMatrix(i,2) * cos(pMatrix(i,3));
        pMatrix(i,1) = pMatrix(i,2) * sin(pMatrix(i,3));
        pMatrix(i,0,1,2) += temp;
        temp = pMatrix(i,0,1,2);
    }
    
    
}

void drawp(HDC &hdc, Tensor2<double>& pMatrix)
{
    drawPos(0,0,3,1) = xy_ratio * pMatrix(0,0,3,1) +x_orig;
    drawPos(0,1,3,1) = xy_ratio *-pMatrix(0,1,3,1) +y_orig;
            
    Ellipse( hdc,
             x_orig -2,
             y_orig -2,
             x_orig +2,
             y_orig +2
           );
    
    for( int i=0; i< drawPos.getRow(); i++ )
    {
        Ellipse( hdc,
                 drawPos(i,0) -2,
                 drawPos(i,1) -2,
                 drawPos(i,0) +2,
                 drawPos(i,1) +2
               );
    }
    
    MoveToEx( hdc,
              x_orig,
              y_orig,
              NULL
            );
            
    for( int i=0; i< drawPos.getRow(); i++ )
    {
        LineTo( hdc,
                drawPos(i,0),
                drawPos(i,1)
              );
    }
            
}

void actn2()
{
    Tensor2<double> equationMatrix(3,2);
    for( int i=0; i< pointMatrix.getRow(); i++ )
    {
        equationMatrix(i,0) = -pointMatrix(i,2) *sin(pointMatrix(i,3));
        equationMatrix(i,1) =  pointMatrix(i,2) *cos(pointMatrix(i,3));
    }
    equationMatrix &= -equationMatrix(0,0,1,2);
    //equationMatrix(3,0) += 1;
    equationMatrix = ~(equationMatrix(1,0,3,2).trans());
    
    if(equationMatrix(1,1))
    {
        pointMatrix(1,4,2,1) = pointMatrix(0,4) *equationMatrix(0,2,2,1);
    }
    else
    {
        pointMatrix(1,4) = pointMatrix(0,4) *equationMatrix(0,2)
                          -pointMatrix(2,4) *equationMatrix(0,1);
    }
    pointMatrix(0,3,3,1) += pointMatrix(0,4,3,1);
    pointMatrix %= 2*M_PI;
    
    Tensor2<double> temp(1,2,tens2::stable);
    temp.zeros();
    for( int i=0; i< pointMatrix.getRow(); i++ )
    {
        pointMatrix(i,0) = pointMatrix(i,2) * cos(pointMatrix(i,3));
        pointMatrix(i,1) = pointMatrix(i,2) * sin(pointMatrix(i,3));
        pointMatrix(i,0,1,2) += temp;
        temp = pointMatrix(i,0,1,2);
    }
    
    
}
