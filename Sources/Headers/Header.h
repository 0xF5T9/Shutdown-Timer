#pragma once

class Windows {
private:

public:
	Windows() {
		//	Constructor
	}
	~Windows() {
		//	Destructor
	}
	/*	Khai báo hàm mẫu(Declare function prototypes)	*/
	void SetWindowSize(SHORT width, SHORT height);
	void SetScreenBufferSize(SHORT width, SHORT height);
	void DisableResizeWindow();
	void ShowScrollbar(BOOL Show);
	void DisableSelection();
	void SetColor(int backgound_color, int text_color);
};

/*	Class: Timer - Các hàm prototype của Timer	*/
class Timer {
private:

public:
	Timer() {
		//	Constructor
	}
	~Timer() {
		//	Destructor
	}
	/*	Khai báo hàm mẫu(Declare function prototypes)	*/
	void loadAnimation();
	void dotAnimation();
	void showMenu();
	int getInput();
	bool processOption(int i);
};
