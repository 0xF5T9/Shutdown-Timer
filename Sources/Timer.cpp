#include <iostream>		
#include <Windows.h>		
#include <string>		
#include "../Sources/Headers/Header.h"

/*	Tạo object từ classes (Create object from classes)	*/
Windows WindowsObjTimer;	

/*	Định nghĩa các hàm class 'Timer' (Define 'Timer' class functions)	*/
void Timer::loadAnimation() {
	WindowsObjTimer.SetColor(0, 14);
	for (double i = 0; i < 100; i++) {
		int y = (int)round(i);
		std::cout << "Đang tải (" << y << "%)";
		if (i < 100) i *= 1.4;
		system("cls");
	}
}
void Timer::dotAnimation() {
	for (int i = 0; i < 3; i++) {
		Sleep(500);
		std::cout << ".";
	}
}

void Timer::showMenu() {
	WindowsObjTimer.SetColor(0, 11);
	std::cout << "Menu\n";
	std::cout << "-----\n";
	WindowsObjTimer.SetColor(0, 14);
	std::cout << "\n";
	std::cout << "1. Hẹn giờ tắt máy trong 1 tiếng\n";
	std::cout << "2. Hẹn giờ tắt máy trong 2 tiếng\n";
	std::cout << "3. Hẹn giờ tắt máy trong 4 tiếng\n";
	std::cout << "4. Hẹn giờ tắt máy (nhập số tiếng)\n";
	std::cout << "5. Huỷ lịch trình tắt máy hiện tại\n";
	std::cout << "6. Thoát chương trình\n";
	std::cout << std::endl;
}
int Timer::getInput() {
	int i;
	bool hopLe = false;
	while (hopLe == false) {
		std::cout << "Nhập lựa chọn: ";
		std::cin >> i;
		if (i > 0 && i < 7) {
			hopLe = true;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		system("cls");
		showMenu();
	}
	return i;
}

bool Timer::processOption(int i) {
	bool q;
	q = false;
	switch (i) {
	case 1:
		system("shutdown -a");
		system("shutdown -s -t 3600");
		system("cls");
		showMenu();
		WindowsObjTimer.SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 1 tiếng.\n";
		WindowsObjTimer.SetColor(0, 11);
		dotAnimation();
		WindowsObjTimer.SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 2:
		system("shutdown -a");
		system("shutdown -s -t 7200");
		system("cls");
		showMenu();
		WindowsObjTimer.SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 2 tiếng.\n";
		WindowsObjTimer.SetColor(0, 11);
		dotAnimation();
		WindowsObjTimer.SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 3:
		system("shutdown -a");
		system("shutdown -s -t 14400");
		system("cls");
		showMenu();
		WindowsObjTimer.SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 4 tiếng.\n";
		WindowsObjTimer.SetColor(0, 11);
		dotAnimation();
		WindowsObjTimer.SetColor(0, 14);
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
		std::cout << "Nhập số tiếng: ";
		std::cin >> h;
		while (h < 1 || h > 24) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			system("cls");
			showMenu();
			WindowsObjTimer.SetColor(0, 12);
			std::cout << "Tối thiểu 1 tiếng hoặc tối đa 24 tiếng.\n";
			WindowsObjTimer.SetColor(0, 14);
			std::cout << "Nhập số tiếng: ";
			std::cin >> h;
		}
		ph = h * 3600;
		std::string ph2 = std::to_string(ph);
		system(("shutdown -s -t " + ph2).c_str());
		system("cls");
		showMenu();
		WindowsObjTimer.SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng " << h << " tiếng.\n";
		WindowsObjTimer.SetColor(0, 11);
		dotAnimation();
		WindowsObjTimer.SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	}
	case 5:
		system("shutdown -a");
		system("cls");
		showMenu();
		WindowsObjTimer.SetColor(0, 10);
		std::cout << "Đã huỷ lịch trình tắt máy hiện tại.\n";
		WindowsObjTimer.SetColor(0, 11);
		dotAnimation();
		WindowsObjTimer.SetColor(0, 14);
		system("cls");
		showMenu();
		return q;
		break;
	case 6:
		q = true;
		return q;
		break;
	default:
		return q;
		break;
	}
}