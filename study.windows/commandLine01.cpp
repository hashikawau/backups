#include<windows.h>

int WINAPI WinMain(
		HINSTANCE hInstance ,
		HINSTANCE hPrevInstance ,
		PSTR lpCmdLine ,
		int nCmdShow ) {
	MessageBox(NULL , lpCmdLine , TEXT("Kitty") , MB_ICONINFORMATION);
	return 0;
}