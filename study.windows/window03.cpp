#define UNICODE
#include <windows.h>

const int GCL_HBRBACKGROUND = -10;
const int GCL_HICON = -14;

void message(int num)
{
    wchar_t str[256];
    wsprintfW(str, L"%d", num);
    MessageBox(NULL, str, L"Message", MB_OK | MB_ICONINFORMATION);
}
void message(wchar_t* str)
{
    MessageBoxW(NULL, str, L"Message", MB_OK | MB_ICONINFORMATION);
}
LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp);

WNDCLASSW wndclass;

class Component
{
private:
protected:
    HWND hwnd;
    wchar_t szClassName[sizeof(int)*8+1];
    wchar_t szTitle[256];
    int x;
    int y;
    int cx;
    int cy;
public:
    Component()
    {
        wsprintf(szClassName, L"%d", this);

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


};


class Canvas :public Component
{
protected:
    HWND hwndParent;
public:
    Canvas()
    {
        szTitle[0] = '\0';
        SetClassLong(this->hwnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(BLACK_BRUSH));
        SetClassLong(hwnd, GCL_HICON, NULL);

    }

    void createWindow(HWND hwndParent)
    {
        this->hwndParent = hwndParent;
        this->x = 100;
        this->y = 0;
        this->cx = 400;
        this->cy = 400;

        hwnd = CreateWindow(szClassName,
                            NULL,
                            WS_CHILD,
                            this->x,
                            this->y,
                            this->cx,
                            this->cy,
                            this->hwndParent,
                            NULL,//(HMENU)(int)this,
                            GetModuleHandle(0),
                            NULL
        );


        ShowWindow(this->hwnd, SW_NORMAL);
   // InvalidateRect(this->hwnd, NULL, true);
     //   UpdateWindow(this->hwnd);

    }


};

LRESULT CALLBACK WndProc(HWND hwnd , UINT msg , WPARAM wp , LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap;
	static HDC hBuffer;

	switch (msg) {
	case WM_DESTROY:
		DeleteDC(hBuffer);
		DeleteObject(hBitmap);

		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
    //SetWindowLong (hwnd, 0, 0) ;

		return 0;
        case WM_SIZE:
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps);
        MoveToEx(hdc, 0, 0, NULL);
        LineTo(hdc, 100, 100);
            EndPaint(hwnd, &ps);
            return 0;
	}
	return DefWindowProc(hwnd , msg , wp , lp);
}

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow ) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
			TEXT("KITTY") , TEXT("Kitty on your lap") ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			NULL , NULL ,
			hInstance , NULL
	);

    CreateWindow(
		TEXT("BUTTON") , TEXT("Kitty") ,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
		0 , 0 , 100 , 50 ,
		hwnd , NULL , GetModuleHandle(0) , NULL
	);

	if (hwnd == NULL) return -1;

    Canvas cv;
    cv.createWindow(hwnd);

    //InvalidateRect(hwnd, NULL, false);

	while(GetMessage(&msg , NULL , 0 , 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}






