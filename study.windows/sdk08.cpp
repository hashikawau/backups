/********************************************************************************/
/*                                                                              */
/*  �ԁ[�ɂ���SDK�v���O�����@8��                                              */
/*      �`�R���g���[���̎g�p(�{�^��)�`                                          */
/********************************************************************************/
#include <windows.h>

#define	ID_BTN	1000
HWND	button;

const int GWL_HINSTANCE = -6;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wP, LPARAM lP)
{
	switch(msg){
		case WM_CREATE:
			button=CreateWindowEx(0,
					"BUTTON",
					"�ڂ���",
					WS_CHILD,
					48, 48,128, 32,
					hwnd,
					(HMENU)ID_BTN,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
					NULL);
			ShowWindow(button,SW_SHOW);
			break;
		case WM_COMMAND:
			switch ( LOWORD ( wP ) )
			{
				case ID_BTN:
					MessageBox(hwnd,"�{�^����������","BUTTON",MB_OK);
					break;
			}
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
	wcl.style = 0;

	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;

	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

	if(!RegisterClassEx(&wcl)) return 0;

	hwnd = CreateWindow(szWinName,
	"�ԁ[�ɂ���SDK�v���O����",
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
