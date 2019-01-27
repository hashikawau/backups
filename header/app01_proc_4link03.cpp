#include <windows.h>
#include "tensor2.h"

int sleeptime = 30;
int numCalc = 11;
int numRotate = 1;
double xy_ratio = 5e1;
double radius;
double x_center;
double y_center;
int numPoint;

int x_orig = 150;
int y_orig = 200;
int passtime = 0;

Tensor2<double> pointMatrix(2,5);
Tensor2<double> inipointMatrix(2,5);
Tensor2<int> drawPos(2,2);

void init();
double setRad( double x_coor, double y_coor );
void actn(Tensor2<double>& pMatrix, double dr, double theta);
void actn2(Tensor2<double>& pMatrix);
void drawp(HDC &hdc, Tensor2<double>& pMatrix);
//===============================
class Point;
class Rod;
Point* points = NULL;
Rod* rods = NULL;
//==================================
struct info
{
    enum movement
    {
        fixed  = 0x01,
        
        link   = 0x00,
        slider = 0x10
    };
};
//====================================
class Point
{
    double X;
    double Y;
    int move;
    double slideA;
    Storage<Rod*> storRod;
    
public:
    Point()
    {
    }
    
    double x_coor(){ return X; }
    double y_coor(){ return Y; }
    int isfixed() { return move & info::fixed;  }
    int islink()  { return move & info::link;   }
    int isslider(){ return move & info::slider; }
    void connect(Rod* prod){ storRod = prod; }
    
    void operator()(double px=0, double py=0, int information=0)
    {
        X = px;
        Y = py;
        move |= information;
    }
    void operator()(int information=0)
    {
        move |= information;
    }
};
//==========================================
class Rod
{
    Point* pPoint[2];
    double R;
    double A;
    
public:
    Rod(){}
    
    void operator()(Point& point1, Point& point2)
    {
        pPoint[0] = &point1;
        pPoint[1] = &point2;
        pPoint[0]->connect(this);
        pPoint[1]->connect(this);
        
        double x_coor = pPoint[0]->x_coor() - pPoint[1]->x_coor();
        double y_coor = pPoint[0]->y_coor() - pPoint[1]->y_coor();
        R = sqrt( x_coor*x_coor + y_coor*y_coor );
        A = setRad(x_coor, y_coor);
    }
};
//============================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    PAINTSTRUCT ps;
    static int isDrawing = 0;
    
    switch(msg)
    {
        case WM_CREATE:
            
            init();
            
            return 0;    
            
        
        case WM_TIMER:
        
            Sleep(sleeptime);
            
            double theta1;
            double radius1;
            
            for( int i=0; i< 10; i++ )
            {
                theta1 = setRad( pointMatrix(numPoint,0)-x_center,
                                 pointMatrix(numPoint,1)-y_center );
                                 
                radius1 = sqrt( (pointMatrix(numPoint,0)-x_center)
                               *(pointMatrix(numPoint,0)-x_center)
                              + (pointMatrix(numPoint,1)-y_center)
                               *(pointMatrix(numPoint,1)-y_center) );
                                 
                actn(pointMatrix, 0.01, theta1+M_PI_2);
                actn(pointMatrix, (radius-radius1)/2, theta1);
                
                for(int j=0; j< 5; j++ )
                {
                theta1 = setRad( pointMatrix(numPoint,0)-x_center,
                                 pointMatrix(numPoint,1)-y_center );
                radius1 = sqrt( (pointMatrix(numPoint,0)-x_center)
                               *(pointMatrix(numPoint,0)-x_center)
                              + (pointMatrix(numPoint,1)-y_center)
                               *(pointMatrix(numPoint,1)-y_center) );
                actn(pointMatrix, (radius-radius1)/2, theta1);
                }
            }
            
            InvalidateRect( hWnd, NULL, true );
            
            return 0;
        
        
        case WM_PAINT:
            
            hdc = BeginPaint( hWnd, &ps );
            
            drawp(hdc,pointMatrix);
            
            storTensor2.clear();
        
            EndPaint( hWnd, &ps );
            
            return 0;
        
            
        case WM_LBUTTONDOWN:
            
            init();
            
            InvalidateRect( hWnd, NULL, true );
            
            return 0;
            
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_RIGHT:
                    for(int i=0; i< 50; i++)
                    {
                        actn(pointMatrix, 0.001, 0);
                    }
                    InvalidateRect( hWnd, NULL, true );
                    break;
                case VK_LEFT:
                    for(int i=0; i< 50; i++)
                    {
                        actn(pointMatrix, 0.001, M_PI);
                    }
                    InvalidateRect( hWnd, NULL, true );
                    break;
                case VK_UP:
                    for(int i=0; i< 50; i++)
                    {
                        actn(pointMatrix, 0.001, M_PI_2);
                    }
                    InvalidateRect( hWnd, NULL, true );
                    break;
                case VK_DOWN:
                    for(int i=0; i< 50; i++)
                    {
                        actn(pointMatrix, 0.001, -M_PI_2);
                    }
                    InvalidateRect( hWnd, NULL, true );
                    break;
                    
                case VK_SPACE:
                    if( isDrawing )
                    {
                        KillTimer( hWnd, 1 );
                        isDrawing = 0;
                    }
                    else
                    {
                        SetTimer( hWnd, 1, sleeptime, NULL );
                        isDrawing = 1;
                        radius = sqrt( (pointMatrix(numPoint,0)-x_center)
                                      *(pointMatrix(numPoint,0)-x_center)
                                      +(pointMatrix(numPoint,1)-y_center)
                                      *(pointMatrix(numPoint,1)-y_center) );
                    }
                    
                    break;
                    
                case VK_RETURN:
                    
                    if( isDrawing )
                    {
                        KillTimer( hWnd, 1 );
                    }
                    if(points)
                    {
                        delete [] points;
                        points = NULL;
                    }
                    if(rods)
                    {
                        delete [] rods;
                        rods = NULL;
                    }
                    PostQuitMessage(0);
                    
                    break;
                    
                default:
                    break;
            }
            
            return 0;
            
        case WM_DESTROY:
            
            if( isDrawing )
            {
                KillTimer( hWnd, 1 );
            }
            if(points)
            {
                delete [] points;
                points = NULL;
            }
            if(rods)
            {
                delete [] rods;
                rods = NULL;
            }
            PostQuitMessage(0);
            
            return 0;
    }
    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}


void init()
{
    if(points)
    {
        delete [] points;
        points = NULL;
    }
    if(rods)
    {
        delete [] rods;
        rods = NULL;
    }
    
    numPoint = pointMatrix.getRow()-1;
    
    points = new Point[numPoint];
    rods = new Rod[numPoint];
    points[0](0,0,info::fixed);
    points[1](1,1,info::fixed);
    points[2](2,2,info::fixed);
    
    x_center = 0.9;
    y_center = 0;
    passtime = 0;
    double x_coor, y_coor;
    
    pointMatrix(0,0) = 2.4;         // x
    pointMatrix(0,1) = 0;         // y
    x_coor = pointMatrix(0,0);
    y_coor = pointMatrix(0,1);
    pointMatrix(0,2) = sqrt( x_coor*x_coor + y_coor*y_coor );     // radius
    pointMatrix(0,3) = setRad(x_coor, y_coor);                    // theta
    pointMatrix(0,4) = 0;      // dtheta
    
    
    pointMatrix(1,0) = 1.2;
    pointMatrix(1,1) = 0.4;
    x_coor = pointMatrix(1,0) - pointMatrix(0,0);
    y_coor = pointMatrix(1,1) - pointMatrix(0,1);
    pointMatrix(1,2) = sqrt( x_coor*x_coor + y_coor*y_coor );
    pointMatrix(1,3) = setRad(x_coor, y_coor);
    pointMatrix(1,4) = 0;
    /*
    pointMatrix(2,0) = 2;
    pointMatrix(2,1) = 0;
    x_coor = pointMatrix(2,0) - pointMatrix(1,0);
    y_coor = pointMatrix(2,1) - pointMatrix(1,1);
    pointMatrix(2,2) = sqrt( x_coor*x_coor + y_coor*y_coor );
    pointMatrix(2,3) = setRad(x_coor, y_coor);
    pointMatrix(2,4) = 0;
    
    pointMatrix(3,0) = 1.2;
    pointMatrix(3,1) = 1.6;
    x_coor = pointMatrix(3,0) - pointMatrix(2,0);
    y_coor = pointMatrix(3,1) - pointMatrix(2,1);
    pointMatrix(3,2) = sqrt( x_coor*x_coor + y_coor*y_coor );
    pointMatrix(3,3) = setRad(x_coor, y_coor);
    pointMatrix(3,4) = 0;
    */
}

double setRad( double x_coor, double y_coor )
{
    if(!x_coor)
    {
        if(y_coor >= 0)
        {
            return M_PI_2;
        }
        else
        {
            return -M_PI_2;
        }
    }
    
    double dRad;
    double gradient = y_coor /x_coor;
    
    if(gradient < -1)
    {
        dRad = -( M_PI_2 + atan(x_coor/y_coor) );
    }
    else
    if(gradient > 1)
    {
        dRad = ( M_PI_2 - atan(x_coor/y_coor) );
    }
    else
    {
        dRad = atan(gradient);
    }
    
    if(x_coor < 0)
    {
        dRad += M_PI;
    }
    
    return iszero(dRad+2*M_PI);
}

void actn(Tensor2<double>& pMatrix, double dr, double theta)
{
    Tensor2<double> dthetaMatrix(pMatrix.getRow(),2);
    
    dthetaMatrix(pMatrix.getRow() -1, 0)
        = dr * cos(theta-pMatrix(pMatrix.getRow() -1,3));
    
    dthetaMatrix(pMatrix.getRow() -1, 1)
        = dr * sin(theta-pMatrix(pMatrix.getRow() -1,3));
    
    for( int i= pMatrix.getRow() -2; i>= 0; i-- )
    {
        dthetaMatrix(i,0)
            = dthetaMatrix(i+1,0) * cos( pMatrix(i+1,3) -pMatrix(i,3) );
        dthetaMatrix(i, 1)
            = dthetaMatrix(i+1,0) * sin( pMatrix(i+1,3) -pMatrix(i,3) );
    }
    
    for( int i=0; i< pMatrix.getRow(); i++ )
    {
        pMatrix(i,3) += pMatrix(i,2) * dthetaMatrix(i, 1);
    }
    
    pMatrix(0,3,pMatrix.getRow(),1) %= 2*M_PI;
    
    Tensor2<double> temp(1,2,tens2::stable);
    temp.zeros();
    for( int i=0; i< pMatrix.getRow(); i++ )
    {
        pMatrix(i,0) = pMatrix(i,2) * cos(pMatrix(i,3));
        pMatrix(i,1) = pMatrix(i,2) * sin(pMatrix(i,3));
        pMatrix(i,0,1,2) += temp;
        temp = pMatrix(i,0,1,2);
    }
}

void actn2(Tensor2<double>& pMatrix)
{
    //===================================
    double ini_x_coor = pMatrix(2,0);
    double ini_y_coor = pMatrix(2,1);
    //==================================
    
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
    if(!equationMatrix(1,2))
    {
        pMatrix(1,4) = pMatrix(0,4) *equationMatrix(0,2)
                      -pMatrix(2,4) *equationMatrix(0,1);
        
    }
    else
    {
        pMatrix(0,4) *= -1;
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
    
    //=========================================
    if(pointMatrix(0,4)>0)
    {
        passtime++;
        if(passtime==(int)(numRotate*2*M_PI/pointMatrix(0,4)))
        {
            init();
        }
    }
    else
    {
        passtime--;
        if(passtime==(int)(numRotate*2*M_PI/pointMatrix(0,4)))
        {
            init();
            pointMatrix(0,4) *= -1;
        }
    }
    //=========================================
    
}

void drawp(HDC &hdc, Tensor2<double>& pMatrix)
{
    drawPos(0,0,drawPos.getRow(),1)
        = xy_ratio * pMatrix(0,0,drawPos.getRow(),1) +x_orig;
    drawPos(0,1,drawPos.getRow(),1)
        = xy_ratio *-pMatrix(0,1,drawPos.getRow(),1) +y_orig;
            
    Ellipse( hdc,
             xy_ratio * (-pointMatrix(0,2)) +x_orig,
             xy_ratio * (-pointMatrix(0,2)) +y_orig,
             xy_ratio * (+pointMatrix(0,2)) +x_orig,
             xy_ratio * (+pointMatrix(0,2)) +y_orig
           );
           
    Ellipse( hdc,
             xy_ratio * (x_center -radius) +x_orig,
             xy_ratio * (y_center -radius) +y_orig,
             xy_ratio * (x_center +radius) +x_orig,
             xy_ratio * (y_center +radius) +y_orig
           );
           
    Ellipse( hdc,
             x_orig -2,
             y_orig -2,
             x_orig +2,
             y_orig +2
           );
    
    Ellipse( hdc,
             x_center -2,
             y_center -2,
             x_center +2,
             y_center +2
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
    
    LineTo( hdc,
            xy_ratio * x_center +x_orig,
            xy_ratio * y_center +y_orig
          );
          
    Ellipse( hdc,
             xy_ratio * x_center +x_orig -2,
             xy_ratio * y_center +y_orig -2,
             xy_ratio * x_center +x_orig +2,
             xy_ratio * y_center +y_orig +2
           );
        
}



