#pragma once
/*	Các Hàm tự tạo	*/
void loadAnimation();
void dotAnimation();
void showMenu();
int getInput();
bool processOption(int i);

/*	Các Hàm của Windows.h	*/
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void DisableSelection();
void SetColor(int backgound_color, int text_color);
