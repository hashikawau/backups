#include <windows.h>
#include "tensor2.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WindowInitX  = 500;
int WindowInitY  = 0;
int WindowWidth  = 500;
int WindowHeight = 400;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG  msg;
    WNDCLASSEX wc;
    LPSTR lpszClassName = "app01.cpp";
    LPSTR lpszTitle     = "Title";
    
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    
    wc.hInstance     = hInstance;
    wc.lpszClassName = lpszClassName;
    wc.lpfnWndProc   = WndProc;
    wc.style         = 0;
    
    wc.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
    wc.hIconSm       = LoadIcon( NULL, IDI_WINLOGO );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    
    wc.lpszMenuName  = NULL;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    
    if( !RegisterClassEx(&wc) ) return 0;
    
    
    hWnd = CreateWindow(lpszClassName,
                        lpszTitle,
                        WS_OVERLAPPEDWINDOW,
                        WindowInitX,
                        WindowInitY,
                        WindowWidth,
                        WindowHeight,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );
    
    while( 1 )
    {
        BOOL ret = GetMessage( &msg, NULL, 0, 0 );  // メッセージを取得する
        if( ret == 0 || ret == -1 )
        {
            // アプリケーションを終了させるメッセージが来ていたら、
            // あるいは GetMessage() が失敗したら( -1 が返されたら ）、ループを抜ける
            break;
        }
        else
        {
            // メッセージを処理する
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }
    
    return msg.wParam;
}
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    PAINTSTRUCT ps;
    
    switch(msg)
    {
        case WM_CREATE:
            
            init();//================
                    
            SetTimer( hWnd, 1, sleeptime, NULL );
            
            return 0;    
            
        case WM_TIMER:
        
            Sleep(sleeptime);
            
            clearStorage(); // ==============
            for(int i=0; i< numCalc; i++ )
            {
                actn(pointMatrix); //======================
                actn(pointMatrix2); //======================
            }
            passtime++; //======================
            
            InvalidateRect( hWnd, NULL, true );
            return 0;    
        
        case WM_PAINT:
            
            hdc = BeginPaint( hWnd, &ps );
            
            drawp(hdc,pointMatrix);
            drawp(hdc,pointMatrix2);
            Ellipse( hdc,
                     0,
                     0,
                     0 +(int)storTensor2%100,
                     0 +(int)storTensor2%100
            );
            
            EndPaint( hWnd, &ps );
            
            return 0;
            
            
        case WM_KEYDOWN:
            if( wParam == VK_RETURN )
            {
                KillTimer( hWnd, 1 );
                PostQuitMessage(0);
                return 0;
            }
            
            break;
            
        case WM_DESTROY:
            KillTimer( hWnd, 1 );
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}


void init()
{
    pointMatrix(0,0) = 0;         // x
    pointMatrix(0,1) = 1;         // y
    pointMatrix(0,2) = 1;         // radius
    pointMatrix(0,3) = 0;         // theta
    pointMatrix(0,4) = 0.001;      // dtheta
    
    pointMatrix(1,0) = 1;
    pointMatrix(1,1) = 1;
    pointMatrix(1,2) = 1;
    pointMatrix(1,3) = 0;
    pointMatrix(1,4) = 0;
    
    pointMatrix(2,0) = 1;
    pointMatrix(2,1) = 0;
    pointMatrix(2,2) = 1;
    pointMatrix(2,3) = M_PI;
    pointMatrix(2,4) = 0;
    
    pointMatrix2(0,0) = 0;         // x
    pointMatrix2(0,1) = 1;         // y
    pointMatrix2(0,2) = 1;         // radius
    pointMatrix2(0,3) = 0;         // theta
    pointMatrix2(0,4) = 0.001;      // dtheta
    
    pointMatrix2(1,0) = 1;
    pointMatrix2(1,1) = 1;
    pointMatrix2(1,2) = 3;
    pointMatrix2(1,3) = 0;
    pointMatrix2(1,4) = 0;
    
    pointMatrix2(2,0) = 1;
    pointMatrix2(2,1) = 0;
    pointMatrix2(2,2) = 1;
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
*/
