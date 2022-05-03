#include <iostream>
#include <string>
#include <Windows.h>
#include "../Sources/Headers/winapi.h"
#include "../Sources/Headers/menu.h"
#include "../Sources/Headers/animation.h"
#include "../Sources/Headers/func.h"

int main() {

	/*	Initialize program parameters	*/
	winapi* WinAPI = CreateObjectWinAPI();
	animation* Animation = CreateObjectAnimation(WinAPI);
	menu* Menu = CreateObjectMenu(WinAPI, Animation);
	SetConsoleOutputCP(65001);						//	Set code page utf-8
	WinAPI->SetWindowSize(60,15);					//	Set window size
	WinAPI->SetScreenBufferSize(60, 15);			//	Set window buffer size
	WinAPI->DisableResizeWindow();					//	Disable window resize
	WinAPI->DisableSelection();						//	Disable console selection
	WinAPI->ShowScrollbar(0);						//	Hide console scroll bar
	SetConsoleTitle(L"Bộ Hẹn Giờ Tắt Máy");			//	Set Console Title

	/*	Start the program	*/
	Animation->LoadAnimation();
	Menu->ShowMenu();
	while (true) {
		bool EXITPROGRAM = Menu->ProcessOption(Menu->SelectOption());
		if (EXITPROGRAM == true) break;
	}

	/*	End the program	*/
	FreeMemory(WinAPI);
	FreeMemory(Animation);
	FreeMemory(Menu);
	return 0;
}





