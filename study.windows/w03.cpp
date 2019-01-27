#include <windows.h>
    
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

INT WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPreInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow )
{
    int i = 9;
//    char *j = atoi(i);
//    MessageBox( NULL, "j", "dialog", MB_OK );
    
    WNDCLASS wc;
    MSG msg;
    
    ZeroMemory( &wc, sizeof(WNDCLASS) );
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "Windows";
    
    if( !RegisterClass(&wc) ) return FALSE;
    
    HWND hWnd = CreateWindow( wc.lpszClassName,
                              "tytle",
                              WS_OVERLAPPEDWINDOW ^
                                WS_THICKFRAME ^
                                WS_MAXIMIZEBOX,
                              CW_USEDEFAULT,
                              CW_USEDEFAULT,
                              320+GetSystemMetrics(SM_CXDLGFRAME)*2,
                              240+GetSystemMetrics(SM_CYDLGFRAME)*2+
                                GetSystemMetrics(SM_CYCAPTION),
                              NULL,
                              NULL,
                              hInstance,
                              NULL);
    
    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );
    
    while( GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    HDC hdc;
    static HDC hdc_work;
    static HBITMAP hb_work;
    PAINTSTRUCT ps;
    
    static int dot_x = 0;
    static int dot_y = 0;
    
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
            
            dot_x = 50;
            dot_y = 50;
            
            SetTimer( hWnd, 1, 10, NULL );
            return 0;
            
        case WM_TIMER:
            //dot_x += 1;
            //dot_y += 1;
            if( GetKeyState('I') & 0x8000 )
            {
                dot_y -= 1;
            }
            if( GetKeyState('K') & 0x8000 )
            {
                dot_y += 1;
            }
            if( GetKeyState('L') & 0x8000 )
            {
                dot_x += 1;
            }
            if( GetKeyState('J') & 0x8000 )
            {
                dot_x -= 1;
            }
            
            Sleep(10);
            
            InvalidateRect( hWnd, NULL, false );
            return 0;
            
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
    TextOut( hdc, 10, 10, "ttt", 10 );
            BitBlt( hdc, dot_x, dot_y, 32, 32, hdc_work, 0, 0, SRCCOPY );
            BitBlt( hdc, dot_x+100, dot_y+100, 32, 32, hdc_work, 0, 0, SRCCOPY );
            EndPaint( hWnd, &ps );
            return 0;
            
        case WM_DESTROY:
            KillTimer( hWnd, 1 );
            ReleaseDC( hWnd, hdc_work );
            DeleteObject( hb_work );
            PostQuitMessage(0);
            return 0;
        
        default:
            return DefWindowProc( hWnd, msg, wParam, lParam );
    }
    
    return (0);
}