#include <windows.h>
#include "dynamics.h"

/*
int WindowInitX  = 0;
int WindowInitY  = 0;
int WindowWidth  = 600;
int WindowHeight = 400;
int sleeptime = 50;
static int dot_x = 0;
static int dot_y = 0;
static int time  = 0;
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

    static POINT po1[5];
    static CONST DWORD dw[] = { 3, 2 };
    static HDC hdc_work;
    static HBITMAP hb_work;

    switch(msg)
    {
        case WM_CREATE:
            po1[0].x = 10;
            po1[0].y = 10;
            po1[1].x = 100;
            po1[1].y = 10;
            po1[2].x = 100;
            po1[2].y = 100;

            po1[3].x = 200;
            po1[3].y = 10;
            po1[4].x = 200;
            po1[4].y = 200;

            hdc = GetDC( hWnd );
            hb_work = (HBITMAP)LoadImage( NULL, "dot.bmp", IMAGE_BITMAP,
                                          0, 0, LR_LOADFROMFILE |
                                          LR_CREATEDIBSECTION);
            hdc_work = CreateCompatibleDC( hdc );
            SelectObject( hdc_work, hb_work );

            ReleaseDC( hWnd, hdc );

            SetTimer( hWnd, 1, sleeptime, NULL );
            return 0;

        case WM_TIMER:

            Action();

            Sleep(sleeptime);

            InvalidateRect( hWnd, NULL, true );
            return 0;

        case WM_PAINT:

            hdc = BeginPaint( hWnd, &ps );

            PolyPolyline( hdc, po1, dw, 2 );
            Rectangle( hdc, 10, 10, 100, 100 );
            RoundRect(hdc , 10 , 10 , 200 , 200 , 50 , 50);
            Ellipse( hdc, 10, 10, 100, 100 );

            BitBlt( hdc, dot_x, dot_y, 32, 32, hdc_work, 0, 0, SRCCOPY );

            EndPaint( hWnd, &ps );

            return 0;

        case WM_DESTROY:
            KillTimer( hWnd, 1 );
            ReleaseDC( hWnd, hdc_work );
            DeleteObject( hb_work );
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}
