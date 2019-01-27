#include<windows.h>

int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
		 PSTR pCmdLine , int nCmdShow ) {
	MessageBox(NULL , GetCommandLine() ,
			TEXT("Kitty") , MB_ICONINFORMATION);
	return 0;
}