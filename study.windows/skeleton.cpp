#include <windows.h>

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
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
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
    
    static HDC hdc_work;
    static HBITMAP hb_work;
    static int time;
    static int dot_x;
    static int dot_y;
    
    switch(msg)
    {
        case WM_CREATE:
            hdc = GetDC( hWnd );
            hb_work = (HBITMAP)LoadImage( NULL, "dot.bmp", IMAGE_BITMAP,
                                          0, 0, LR_LOADFROMFILE |
                                          LR_CREATEDIBSECTION);
            hdc_work = CreateCompatibleDC( hdc );
            SelectObject( hdc_work, hb_work );
            
            ReleaseDC( hWnd, hdc );
            
            time = 0;
            dot_x = 0;
            dot_y = 0;
        
            SetTimer( hWnd, 1, 40, NULL );
            return 0;    
            
        case WM_TIMER:
        
            time += 1;
            dot_x = 15*time + 20;
            dot_y = (time-10)*(time-10) + 50;
        
            Sleep(10);
            
            InvalidateRect( hWnd, NULL, true );
            return 0;    
        
        case WM_PAINT:
        
            hdc = BeginPaint( hWnd, &ps );
            
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