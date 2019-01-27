/********************************************************************************/
/*                                                                              */
/*  ぶーにゃんのSDKプログラム　9章                                              */
/*      ～コントロールを使う(リストボックス)～                                  */
/********************************************************************************/
#include <windows.h>
#define	ID_BTN1	1000
#define	ID_BTN2	2000
#define	ID_BTN3	3000
HWND	list;
HWND	btn[3];

const int GWL_HINSTANCE = -6;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wP, LPARAM lP)
{
	char str[40];
	int i;
	switch(msg){
		case WM_CREATE:
			list=CreateWindowEx(0,
					"LISTBOX",
					"",
					WS_CHILD|WS_BORDER|WS_VSCROLL|LBS_NOTIFY,
					24, 8,128, 96,
					hwnd,
					NULL,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
					NULL);
			ShowWindow(list,SW_SHOW);
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"いちご");
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"バナナ");
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"みかん");
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"りんご");
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"ゆず");
			SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"桃");
			btn[0]=CreateWindowEx(0,"BUTTON","追加",WS_CHILD,
					164, 8,64, 32,hwnd,(HMENU)ID_BTN1,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
			ShowWindow(btn[0],SW_SHOW);
			btn[1]=CreateWindowEx(0,"BUTTON","削除",WS_CHILD,
					164, 40,64, 32,hwnd,(HMENU)ID_BTN2,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
			ShowWindow(btn[1],SW_SHOW);
			btn[2]=CreateWindowEx(0,"BUTTON","選択",WS_CHILD,
					164, 72,64, 32,hwnd,(HMENU)ID_BTN3,
					(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),NULL);
			ShowWindow(btn[2],SW_SHOW);
			break;
		case WM_COMMAND:
			switch ( LOWORD ( wP ) )
			{
				case ID_BTN1:
					SendMessage(list, LB_ADDSTRING, 0L, (LPARAM)"追加");
					break;
				case ID_BTN2:
					SendMessage(list, LB_DELETESTRING, SendMessage(list, LB_GETCOUNT, 0L, 0L)-1, 0L);
					break;
				case ID_BTN3:
					i=SendMessage(list, LB_GETCURSEL, 0L, 0L);
					if(i!=LB_ERR){
						wsprintf(str,"%dが選択されました。",i);
						MessageBox(hwnd,str,"BUTTON",MB_OK);
					}
					else{
						MessageBox(hwnd,"項目を選択してください","BUTTON",MB_OK);
					}
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
	wcl.style = NULL;

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
