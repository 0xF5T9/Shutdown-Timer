#include <iostream>		//	Input Outut Stream - C++ Console library
#include <Windows.h>		//	Windows - Windows library
#include <string>		//	String - C++ Basic library
#include "../Sources/Headers/Header.h"	//	Prototype & Classes Header

using namespace std;
Windows WindowsObj;	//	Tạo object để sử dụng các constructor từ class Windows
Timer TimerObj;	//	Tạo object để sử dụng các constructor từ class Timer

int main() {
	//	Initializing the program parameters..
	int luaChon;
	bool q = false;
	SetConsoleOutputCP(65001);			// Set codepage UTF-8 - hỗ trợ tiếng việt
	WindowsObj.SetWindowSize(60,15);				// Set kích thước cửa sổ
	WindowsObj.SetScreenBufferSize(60, 15);			// Set buffer size cửa sổ
	WindowsObj.DisableResizeWindow();				// Vô hiệu thay đổi kích thước cửa sổ
	WindowsObj.DisableSelection();				// Vô hiệu select
	WindowsObj.ShowScrollbar(0);				// Ẩn thanh kéo
	SetConsoleTitle(L"Bộ Hẹn Giờ Tắt Máy");

	//	Start the program..
	TimerObj.loadAnimation();
	TimerObj.showMenu();
	while (q == false) {
		luaChon = TimerObj.getInput();
		q = TimerObj.processOption(luaChon);
	}
	//	Ending the program..
	return 1;
}





