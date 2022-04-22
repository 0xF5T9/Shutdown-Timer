#include <iostream>	
#include <Windows.h>
#include <string>
#include "../Sources/Headers/Header.h"

using namespace std;

/*	Tạo object từ classes (Create object from classes)	*/
Windows WindowsMainObj;	
Timer TimerMainObj;	

int main() {
	//	Initializing the program parameters..
	int luaChon;
	bool q = false;
	SetConsoleOutputCP(65001);			// Hỗ trợ utf-8 (Support utf-8)
	WindowsMainObj.SetWindowSize(60,15);				// Set kích thước cửa sổ (Set window size)
	WindowsMainObj.SetScreenBufferSize(60, 15);			// Set buffer size cửa sổ (Set window buffer size)
	WindowsMainObj.DisableResizeWindow();				// Vô hiệu thay đổi kích thước cửa sổ (Disable window resize)
	WindowsMainObj.DisableSelection();				// Vô hiệu select (Disable console selection)
	WindowsMainObj.ShowScrollbar(0);				// Ẩn thanh kéo (Hide console scroll bar)
	SetConsoleTitle(L"Bộ Hẹn Giờ Tắt Máy");

	//	Start the program..
	TimerMainObj.loadAnimation();
	TimerMainObj.showMenu();
	while (q == false) {
		luaChon = TimerMainObj.getInput();
		q = TimerMainObj.processOption(luaChon);
	}
	//	Ending the program..
	return 1;
}





