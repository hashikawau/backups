/********************************************************************************/
/*                                                                              */
/*  �ԁ[�ɂ���SDK�v���O�����@7��                                              */
/*      �`�}�E�X���g���`                                                */
/********************************************************************************/
#include <windows.h>
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wP, LPARAM lP)
{
	HDC	hdc;
	char str[40];
	switch(msg){
		case WM_LBUTTONDBLCLK://���_�u���N���b�N
			hdc = GetDC(hwnd);
			wsprintf(str,"%s","���_�u���N���b�N");
			TextOut(hdc,16,16,str,strlen(str));
			ReleaseDC(hwnd,hdc);
			break;
		case WM_LBUTTONDOWN:	break;//���N���b�N
		case WM_LBUTTONUP:		break;//���A�b�v
		case WM_RBUTTONDBLCLK:	break;//�E�_�u���N���b�N
		case WM_RBUTTONDOWN://�E�N���b�N
			hdc = GetDC(hwnd);
			wsprintf(str,"%s","�E�N���b�N�@�@�@�@");
			TextOut(hdc,16,16,str,strlen(str));
			ReleaseDC(hwnd,hdc);
			break;
		case WM_RBUTTONUP:		break;//�E�A�b�v
		case WM_MOUSEMOVE://�}�E�X����������
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
	wcl.style = CS_DBLCLKS;//�_�u���N���b�N�̎󂯎�苖��

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
