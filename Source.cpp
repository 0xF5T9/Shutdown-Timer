#include <iostream>		//	Input Outut Stream - C++ Console library
#include <Windows.h>	// Windows - Windows library
#include <string>		// String - C++ basic library test

using namespace std;

/*			Các hàm từ Windows.h - Windows API				 */
void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void SetScreenBufferSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}
void DisableResizeWindow()
{
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void ShowScrollbar(BOOL Show)
{
	HWND hWnd = GetConsoleWindow();
	ShowScrollBar(hWnd, SB_BOTH, Show);
}
void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}
/*-----------------------------------------------------------*/

/*			Hàm tự tạo				*/
void loadAnimation() {
	SetColor(0, 14);
	for (int i = 0; i < 100; i++) {
		cout << "Đang tải (" << i << "%)";
		if (i < 100) i *= 1.4;
		system("cls");
	}
}
void dotAnimation() {
	for (int i = 0; i < 3; i++) {
		Sleep(500);
		cout << ".";
	}
}

void showMenu() {
	SetColor(0, 11);
	cout << "Menu\n";
	cout << "-----\n";
	SetColor(0, 14);
	cout << "\n";
	cout << "1. Hẹn giờ tắt máy trong 1 tiếng\n";
	cout << "2. Hẹn giờ tắt máy trong 2 tiếng\n";
	cout << "3. Hẹn giờ tắt máy trong 4 tiếng\n";
	cout << "4. Hẹn giờ tắt máy (nhập số tiếng)\n";
	cout << "5. Huỷ lịch trình tắt máy hiện tại\n";
	cout << "6. Thoát chương trình\n";
	cout << endl;
}
int getInput() {
	int i;
	bool hopLe = false;
	while (hopLe == false) {
		cout << "Nhập lựa chọn: ";
		cin >> i;
		if (i > 0 && i < 7) {
			hopLe = true;
		}
		cin.clear();
		cin.ignore(10000, '\n');
		system("cls");
		showMenu();
	}
	return i;
}

bool processOption(int i) {
	bool q;
	q = false;
	switch (i) {
	case 1:
		system("shutdown -a");
		system("shutdown -s -t 3600");
		system("cls");
		showMenu();
		SetColor(0, 10);
		cout << "Máy tính sẽ được tắt trong vòng 1 tiếng.\n";
		SetColor(0, 11);
		dotAnimation();
		SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 2:
		system("shutdown -a");
		system("shutdown -s -t 7200");
		system("cls");
		showMenu();
		SetColor(0, 10);
		cout << "Máy tính sẽ được tắt trong vòng 2 tiếng.\n";
		SetColor(0, 11);
		dotAnimation();
		SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 3:
		system("shutdown -a");
		system("shutdown -s -t 14400");
		system("cls");
		showMenu();
		SetColor(0, 10);
		cout << "Máy tính sẽ được tắt trong vòng 4 tiếng.\n";
		SetColor(0, 11);
		dotAnimation();
		SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 4: {
		int h;
		int ph;
		system("shutdown -a");
		system("cls");
		showMenu();
		cout << "Nhập số tiếng: ";
		cin >> h;
		while (h < 1 || h > 24) {
			cin.clear();
			cin.ignore(10000, '\n');
			system("cls");
			showMenu();
			SetColor(0, 12);
			cout << "Tối thiểu 1 tiếng hoặc tối đa 24 tiếng.\n";
			SetColor(0, 14);
			cout << "Nhập số tiếng: ";
			cin >> h;
		}
		ph = h * 3600;
		string ph2 = to_string(ph);
		system(("shutdown -s -t " + ph2).c_str());
		system("cls");
		showMenu();
		SetColor(0, 10);
		cout << "Máy tính sẽ được tắt trong vòng " << h << " tiếng.\n";
		SetColor(0, 11);
		dotAnimation();
		SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	}
	case 5:
		system("shutdown -a");
		system("cls");
		showMenu();
		SetColor(0, 10);
		cout << "Đã huỷ lịch trình tắt máy hiện tại.\n";
		SetColor(0, 11);
		dotAnimation();
		SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 6:
		q = true;
		return q;
		break;
	default:
		break;
	}
}
/*----------------------------------*/

int main() {
	//	Intialize 
	int luaChon;
	bool q = false;
	SetConsoleOutputCP(65001);		// Set codepage UTF-8 - hỗ trợ tiếng việt
	SetWindowSize(60,15);			// Set kích thước cửa sổ
	SetScreenBufferSize(60, 15);	// Set buffer size cửa sổ
	DisableResizeWindow();			// Vô hiệu thay đổi kích thước cửa sổ
	DisableSelection();				// Vô hiệu select
	ShowScrollbar(0);				// Ẩn thanh kéo
	SetConsoleTitle(L"Bộ Hẹn Giờ Tắt Máy");

	//	Start
	loadAnimation();
	showMenu();
	while (q == false) {
		luaChon = getInput();
		q = processOption(luaChon);
	}
	// End
	return 1;
}