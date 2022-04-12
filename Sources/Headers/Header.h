#pragma once

/*	Class: Windows - Các hàm prototype của Windows.h	*/
class Windows {
public:
	void SetWindowSize(SHORT width, SHORT height);
	void SetScreenBufferSize(SHORT width, SHORT height);
	void DisableResizeWindow();
	void ShowScrollbar(BOOL Show);
	void DisableSelection();
	void SetColor(int backgound_color, int text_color);
};

/*	Class: Timer - Các hàm prototype của Timer	*/
class Timer {
public:
	void loadAnimation();
	void dotAnimation();
	void showMenu();
	int getInput();
	bool processOption(int i);
};
