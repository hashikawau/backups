/********************************************************************************/
/*                                                                              */
/*  ぶーにゃんのSDKプログラム　7章                                              */
/*      ～マウスを使う～                                                */
/********************************************************************************/
#include <windows.h>
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wP, LPARAM lP)
{
	HDC	hdc;
	char str[40];
	switch(msg){
		case WM_LBUTTONDBLCLK://左ダブルクリック
			hdc = GetDC(hwnd);
			wsprintf(str,"%s","左ダブルクリック");
			TextOut(hdc,16,16,str,strlen(str));
			ReleaseDC(hwnd,hdc);
			break;
		case WM_LBUTTONDOWN:	break;//左クリック
		case WM_LBUTTONUP:		break;//左アップ
		case WM_RBUTTONDBLCLK:	break;//右ダブルクリック
		case WM_RBUTTONDOWN://右クリック
			hdc = GetDC(hwnd);
			wsprintf(str,"%s","右クリック　　　　");
			TextOut(hdc,16,16,str,strlen(str));
			ReleaseDC(hwnd,hdc);
			break;
		case WM_RBUTTONUP:		break;//右アップ
		case WM_MOUSEMOVE://マウスが動いた時
			hdc = GetDC(hwnd);
			wsprintf(str,"X:%03d Y:%03d",LOWORD(lP),HIWORD(lP));
			TextOut(hdc,16,48,str,strlen(str));
			ReleaseDC(hwnd,hdc);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
		return DefWindowProc(hwnd, msg, wP, lP);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst,
LPSTR lpszArgs, int nWinMode)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wcl;
	char szWinName[] = "new_win";

	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = WinProc;
	wcl.style = CS_DBLCLKS;//ダブルクリックの受け取り許可

	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;

	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

	if(!RegisterClassEx(&wcl)) return 0;

	hwnd = CreateWindow(szWinName,
	"ぶーにゃんのSDKプログラム",
	WS_OVERLAPPEDWINDOW,
	100, 100,
	240, 160,
	HWND_DESKTOP,
	NULL,
	hThisInst,
	NULL
	);

	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
