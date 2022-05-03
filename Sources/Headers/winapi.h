#pragma once
#include <Windows.h>

class winapi {
private:

public:
	winapi() {	//	Constructor
		//	std::cout << "[Debug#winapi->winapi()]: Constructor called" << std::endl;
	}
	winapi(const winapi& _copy) {	// Copy Constructor
		//	std::cout << "[Debug#winapi->winapi(const winapi& _copy)]: Copy Constructor called" << std::endl;
	}
	~winapi() {	//	Destructor
		//	std::cout << "[Debug#winapi->~winapi()]: Destructor called" << std::endl;
	}
	/*	Class Function Prototypes	*/
	void SetWindowSize(SHORT width, SHORT height);
	void SetScreenBufferSize(SHORT width, SHORT height);
	void DisableResizeWindow();
	void ShowScrollbar(BOOL Show);
	void DisableSelection();
	void SetColor(int backgound_color, int text_color);
};

