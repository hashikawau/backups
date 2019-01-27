#include <windows.h>
#include "dynamics2.h"

/*
int WindowInitX  = 0;
int WindowInitY  = 0;
int WindowWidth  = 600;
int WindowHeight = 400;
int sleeptime = 50;
static int dot_x = 0;
static int dot_y = 0;
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG  msg;
    WNDCLASSEX wc;
    LPSTR lpszClassName = "app01.cpp";
    LPSTR lpszTitle     = "Title";
    
    ZeroMemory( hWnd, sizeof(WNDCLASSEX) );
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
    
    while( GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HDC         hdc;
    PAINTSTRUCT ps;
    
    
    switch(msg)
    {
        case WM_CREATE:
            
            hdc = GetDC( hWnd );
            ReleaseDC( hWnd, hdc );
            
            //init();
        
            SetTimer( hWnd, 1, sleeptime, NULL );
            return 0;    
            
        case WM_TIMER:
        
            Sleep(sleeptime);
            
            //InvalidateRect( hWnd, NULL, true );
            return 0;    
        /*
        case WM_PAINT:
        
            hdc = BeginPaint( hWnd, &ps );
            
            for( int i=0; i< iPosMatrix.getRow(); i++ )
            {
                Ellipse( hdc,
                         iPosMatrix(i,0) -2,
                         iPosMatrix(i,1) -2,
                         iPosMatrix(i,0) +2,
                         iPosMatrix(i,1) +2
                       );
            }
            
            MoveToEx( hdc,
                      iPosMatrix(0,0),
                      iPosMatrix(0,1),
                      NULL
                    );
                    
            for( int i=1; i< iPosMatrix.getRow(); i++ )
            {
                LineTo( hdc,
                        iPosMatrix(i,0),
                        iPosMatrix(i,1)
                      );
            }
            
            EndPaint( hWnd, &ps );
            
            return 0;
            */
        case WM_DESTROY:
            KillTimer( hWnd, 1 );
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc( hWnd, msg, wParam, lParam );
}