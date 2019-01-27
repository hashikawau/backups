
#define UNICODE
#include <windows.h>
#include <tchar.h>
#include "list.h"

#ifndef __winex2
#define __winex2
#ifdef UNICODE
#define _ttoi _wtoi
#endif

void jistouni(wchar_t *str)
{
    int i =0;
    while(str[i])
    {
        str[i] = str[i] -0x525e;//529f
        i++;
    }
}
void message(char* str)
{
    MessageBoxA(NULL, str, "Message", MB_OK | MB_ICONINFORMATION);
}
void message(wchar_t* str)
{
    MessageBoxW(NULL, str, L"Message", MB_OK | MB_ICONINFORMATION);
}
void message(int num)
{
    wchar_t str[256];
    wsprintfW(str, L"%lx", num);
    MessageBox(NULL, str, L"Message", MB_OK | MB_ICONINFORMATION);
}

WNDCLASS wndclass;
MSG msg;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcChild(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class PaintStruct :public PAINTSTRUCT
{
public:
    
};


#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL                   0x020A
#endif  //ifndef WM_MOUSEWHEEL
class Mouse
{
protected:
    short mouseX;
    short mouseY;
    short action;
    short state;
    
public:
    int getMouseX()
    {
        POINT po;
        GetCursorPos(&po);
        
        //mouseX = po.x
        return po.x;
    }
    int getMouseY()
    {
        POINT po;
        GetCursorPos(&po);
        
        //mouseY = po.y;
        return po.y;
    }
    void setMousePos(int x, int y)
    {
        SetCursorPos(x, y);
    }
    
    void mouseInfo(int x, int y, int action, int state)
    {
        mouseX = x;
        mouseY = y;
        this->action = action;
        this->state = state;
    }
    
    virtual void mouseMove(){}
    virtual void mousePressed(){}
    virtual void mouseReleased(){}
    virtual void mouseDblclk(){}
    virtual void mouseWheel(){}
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Graphics
{
protected:
    //Component *ptComponent;
    HWND hwnd;
    HDC hdcWnd;
    HDC hdc;
    PaintStruct ps;
    
public:
    Graphics(HWND hwnd)
    {
        //hdc = BeginPaint(hwnd, &ps);
        //SelectObject(hdc, CreateFont(0,0,0,0,0,0,0,0,DEFAULT_CHARSET, 0,0,0,FIXED_PITCH, NULL));
        this->hwnd = hwnd;
        hdcWnd = GetDC(hwnd);
        hdc = hdcWnd;
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
    
    void drawText(int x, int y, String &str)
    {
        TextOut(hdc, x, y, str, str.length());
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
        SelectObject(hdcMem, hBitmap);
        hdc = hdcMem;
    }
    
    ~Bitmap()
    {
        DeleteDC(hdcMem);
        DeleteObject(hBitmap);
    }
    
    void bitblt(HDC hdcDest)
    {
        BitBlt(hdcDest, 0, 0, this->width, this->hight, hdc, 0, 0, SRCCOPY);
    }
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Component: public Mouse
{
private:
protected:
    HWND hwnd;
    TCHAR szClassName[sizeof(int)*8+1];
    TCHAR szTitle[256];
    int x;
    int y;
    int cx;
    int cy;
public:
    Component()
    {
        wsprintf(szClassName, TEXT("%d"), (int)(this));
        
        wndclass.style         = CS_DBLCLKS;
        wndclass.lpfnWndProc   = WndProc;
        wndclass.cbClsExtra    = 0;
        wndclass.cbWndExtra    = 0;
        wndclass.hInstance     = GetModuleHandle(0);
        wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName  = NULL;
        wndclass.lpszClassName = szClassName;
        
        RegisterClass(&wndclass);
    
        x= y= cx= cy= CW_USEDEFAULT;
    }
    
    void sethwnd(HWND hwnd)
    {
        this->hwnd = hwnd;
    }
    
    void setSize(int width, int hight)
    {
        cx = width;
        cy = hight;
    }
    
    void setPos(int newx, int newy)
    {
        x = newx;
        y = newy;
    }
    
    void repaint()
    {
        repaint(true);
    }
    void repaint(bool b)
    {
        InvalidateRect(hwnd, NULL, b);
    }
    
    virtual void createWindow(HWND hwndParent){}
    virtual void createWindow(int, int, int, int){}
    void createWindow(int width =CW_USEDEFAULT, int hight =CW_USEDEFAULT)
    {
        createWindow(CW_USEDEFAULT, CW_USEDEFAULT, width, hight);
    }
    void add(Component *comp)
    {
        comp->createWindow(this->hwnd);
    }
    
    
    virtual void create(){}
    virtual void move(int newx, int newy)
    {
        x = newx;
        y = newy;
        repaint();
    }
    virtual void size(int neww, int newh)
    {
        cx = neww;
        cy = newh;
        repaint();
    }
    /*
    virtual void addComponent(Component &comp)
    {
        
    }
    */
    virtual void paint(Graphics &g){}
    virtual void show(){}
    virtual void show2(int){}
    
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Window :public Component
{
public:
    Window(TCHAR str[] =TEXT("Window"))
    {
        wsprintf(szTitle, str);
        
    
    }
    
    void createWindow(int x, int y, int cx, int cy)
    {
        this->x = x;
        this->y = y;
        this->cx = cx;
        this->cy = cy;
        
        hwnd = CreateWindow(szClassName,
                            szTitle,
                            WS_OVERLAPPEDWINDOW,
                            this->x,
                            this->y,
                            this->cx,
                            this->cy,
                            NULL,
                            NULL,
                            GetModuleHandle(0),
                            NULL
        );
        message((int)this->hwnd);
        
        ShowWindow(hwnd, SW_NORMAL);
        UpdateWindow(hwnd);
        
    }
    void createWindow(int width =CW_USEDEFAULT, int hight =CW_USEDEFAULT)
    {
        createWindow(CW_USEDEFAULT, CW_USEDEFAULT, width, hight);
    }
};

/*
class Canvas :public Component
{
protected:
    HWND hwndParent;
public:
    Canvas()
    {
        szTitle[0] = '\0';
        SetClassLong(hwnd, GCL_HBRBACKGROUND, 0x999999);
        SetClassLong(hwnd, GCL_HICON, NULL);
        
    }
    
    void createWindow(HWND hwndParent)
    {
        this->hwndParent = hwndParent;
        this->x = 0;
        this->y = 0;
        this->cx = 100;
        this->cy = 100;
        
        //message((int)this->hwndParent);
        hwnd = CreateWindow(szClassName,
                            NULL,
                            WS_CHILD || WS_BORDER || WS_VISIBLE,
                            this->x,
                            this->y,
                            this->cx,
                            this->cy,
                            this->hwndParent,
                            NULL,//(HMENU)(int)this,
                            GetModuleHandle(0),
                            NULL
        );
        //message((int)this->hwndParent);
        //message((int)this->hwnd);
        
        
        //ShowWindow(hwnd, SW_NORMAL);
        //UpdateWindow(hwnd);
        
    }
    
};
*/

class List :public Component
{

};

DWORD WINAPI ThreadFunc(LPVOID lpvoid);
class Thread
{
private:
    int iSuspendCount;
    
protected:
    HANDLE hThread;
    static CRITICAL_SECTION cs;
    
public:
    Thread()
    {
        InitializeCriticalSection(&cs);
        iSuspendCount = -1;
    }
    
    void start()
    {
        hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)this, 0, NULL);
        iSuspendCount = 0;
    }
    
    void sleep(int millis)
    {
        Sleep(millis);
    }
    
    void wait()
    {
        if(!iSuspendCount)      //Thread is running
        {
            SuspendThread(hThread);
            iSuspendCount++;
        }
    }
    
    void notify()
    {
        if(iSuspendCount >0)    //Thread is waiting
        {
            ResumeThread(hThread);
            iSuspendCount--;
        }
    }
    
    void lock()
    {
        EnterCriticalSection(&cs);
    }
    void unlock()
    {
        LeaveCriticalSection(&cs);
    }
    
    virtual void run(){}
};
CRITICAL_SECTION Thread::cs;
DWORD WINAPI ThreadFunc(LPVOID lpvoid)
{
    Thread *ptThread;
    ptThread = (Thread*)lpvoid;
    ptThread->run();
    
    return 0;
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    TCHAR szClassName[sizeof(int)*8+1];
    Component* ptComponent;
    
    GetClassName(hwnd, szClassName, sizeof(int)*8+1);
    ptComponent = (Component*)_ttoi(szClassName);
    
    switch(msg)
    {
        case WM_CREATE:
            ptComponent->sethwnd(hwnd);
            ptComponent->create();
            return 0;
            
        case WM_MOVE:
            ptComponent->move(LOWORD(lParam), HIWORD(lParam));
            return 0;
            
        case WM_SIZE:
            ptComponent->size(LOWORD(lParam), HIWORD(lParam));
            return 0;
            
        //case WM_SETFOCUS:
        //    SetCapture(hwnd);
        //    return 0;
            
        //case WM_KILLFOCUS:
        //    ReleaseCapture();
        //    return 0;
        case WM_INPUTLANGCHANGE:
            message(wParam);
            return 0;
            
            
            
        case WM_KEYDOWN:
            if(wParam == VK_LEFT)
            {
                ptComponent->show();
            }
            else
            {
            }
            return 0;
            
            
            
        case WM_DEADCHAR:
        case WM_CHAR:
            ptComponent->show2(wParam);
            return 0;
            
        case WM_PAINT:
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);
            ValidateRect(hwnd, NULL);
            Graphics g(hwnd);
            ptComponent->paint(g);
            EndPaint(hwnd, &ps);
            return 0;
            
        case WM_ERASEBKGND:
            return DefWindowProc(hwnd, msg, wParam, lParam);
            
            //---------------------------------------------------------
            
        //case WM_MOUSEFIRST:
        
        case WM_MOUSEMOVE:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), 0, wParam);
            ptComponent->mouseMove();
            return 0;
            
            //---------------------------------------------------------
            
        case WM_LBUTTONDOWN:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_LBUTTON, wParam);
            ptComponent->mousePressed();
            SetCapture(hwnd);
            return 0;
        case WM_RBUTTONDOWN:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_RBUTTON, wParam);
            ptComponent->mousePressed();
            SetCapture(hwnd);
            return 0;
        case WM_MBUTTONDOWN:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_MBUTTON, wParam);
            ptComponent->mousePressed();
            SetCapture(hwnd);
            return 0;
            
            //---------------------------------------------------------
            
        case WM_LBUTTONUP:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_LBUTTON, wParam);
            ptComponent->mouseReleased();
            ReleaseCapture();
            return 0;
        case WM_RBUTTONUP:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_RBUTTON, wParam);
            ptComponent->mouseReleased();
            ReleaseCapture();
            return 0;
        case WM_MBUTTONUP:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_MBUTTON, wParam);
            ptComponent->mouseReleased();
            ReleaseCapture();
            return 0;
            
            //---------------------------------------------------------
            
        case WM_LBUTTONDBLCLK:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_LBUTTON, wParam);
            ptComponent->mouseDblclk();
            return 0;
        case WM_RBUTTONDBLCLK:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_RBUTTON, wParam);
            ptComponent->mouseDblclk();
            return 0;
        case WM_MBUTTONDBLCLK:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam), MK_MBUTTON, wParam);
            ptComponent->mouseDblclk();
            return 0;
            
            //---------------------------------------------------------
            
        case WM_MOUSEWHEEL:
            ptComponent->mouseInfo(LOWORD(lParam), HIWORD(lParam),
                                   HIWORD(wParam), LOWORD(wParam));
            ptComponent->mouseWheel();
            return 0;
        //case WM_MOUSELAST:
        
        
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}


LRESULT CALLBACK WndProcChild(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            message(L"alkfja;if");
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
#endif //__winex2


