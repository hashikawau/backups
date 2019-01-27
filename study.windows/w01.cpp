#include <windows.h>
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wP, LPARAM lP)
{
	switch(msg){
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
	"kitty on your lap",
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