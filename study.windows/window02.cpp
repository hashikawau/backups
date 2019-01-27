#define UNICODE
#include <windows.h>
void message(wchar_t* str)
{
    MessageBoxW(NULL, str, L"Message", MB_OK | MB_ICONINFORMATION);
}

class Graphics
{
protected:
public:
    //Component *ptComponent;
    HWND hwnd;
    HDC hdcWnd;
    HDC hdc;
    PAINTSTRUCT ps;

public:
    Graphics(HWND hwnd)
    {
        //hdc = BeginPaint(hwnd, &ps);
        //SelectObject(hdc, CreateFont(0,0,0,0,0,0,0,0,DEFAULT_CHARSET, 0,0,0,FIXED_PITCH, NULL));
        this->hwnd = hwnd;
        hdcWnd = GetDC(hwnd);
        hdc = hdcWnd;
    }

    Graphics(HWND hwnd, HDC hdc)
    {
        this->hwnd = hwnd;
        hdcWnd = hdc;
        this->hdc = hdcWnd;
    }

    ~Graphics()
    {
        //DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
        //EndPaint(hdc, &ps);
        ReleaseDC(hwnd, hdcWnd);
    }

    void drawText(int x, int y, TCHAR *str)
    {
        TextOut(hdc, x, y, str, lstrlen(str));
    }


    void drawPixel(int x, int y)
    {
        SetPixel(hdc, x, y, 0x00);
    }

    void drawLine(int x1, int y1, int x2, int y2)
    {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
    }

    operator HDC()
    {
        return hdc;
    }
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Bitmap :public Graphics
{
protected:
public:
    HBITMAP hBitmap;
    HDC hdcMem;
    int width;
    int hight;
public:
    Bitmap(HWND hwnd, int width, int hight) :Graphics(hwnd)
    {
        this->width = width;
        this->hight = hight;
        hBitmap = CreateCompatibleBitmap(hdcWnd, width, hight);
        hdcMem = CreateCompatibleDC(hdcWnd);
        SelectObject(hdcMem, hBitmap);
		PatBlt(hdcMem , 0 , 0 , this->width , this->hight , WHITENESS);
        this->hdc = hdcMem;
    }

    ~Bitmap()
    {
        DeleteDC(hdcMem);
        DeleteObject(hBitmap);
    }


    void bitblt()
    {
        BitBlt(hdcWnd, 0, 0, this->width, this->hight, hdc, 0, 0, SRCCOPY);
    }
};


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("KeyView2") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     hwnd = CreateWindow (szAppName, TEXT ("Keyboard Message Viewer #2"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          300, 300,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    HDC i1, i2, i3, i4,i5,i6,i7;
    wchar_t str[256];

    switch(msg)
    {
        case WM_CREATE:
            return 0;

        case WM_PAINT:
        {
            //ValidateRect(hwnd, NULL);
            hdc = BeginPaint(hwnd, &ps);


            Graphics g(hwnd);

            i1 = g.hdc;
            i2 = g.hdcWnd;

            Bitmap bt(hwnd,300,300);
                i3 = g.hdc;
                i4 = g.hdcWnd;
                i5 = bt.hdc;
                i6 = bt.hdcWnd;
                i7 = bt.hdcMem;

            bt.drawLine(0,0,100,100);
            //BitBlt(hdc, 0, 0, 300, 300, bt.hdcMem, 0, 0, SRCCOPY);
            bt.bitblt();
            EndPaint(hwnd, &ps);

            wsprintfW(str, L"%8lx\n%8lx\n%8lx\n%8lx\n%8lx\n%8lx\n%8lx", i1,i2,i3,i4,i5,i6,i7);
            message(str);

            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}



