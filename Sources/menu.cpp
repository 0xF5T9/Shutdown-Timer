#include <iostream>
#include <string>
#include "../Sources/Headers/menu.h"
#include "../Sources/Headers/winapi.h"
#include "../Sources/Headers/animation.h"

/*	Define 'menu' class functions	*/
void menu::ShowMenu() const {
	WinAPI->SetColor(0, 11);
	std::cout << "Menu\n";
	std::cout << "-----\n";
	WinAPI->SetColor(0, 14);
	std::cout << "\n";
	std::cout << "1. Hẹn giờ tắt máy trong 1 tiếng\n";
	std::cout << "2. Hẹn giờ tắt máy trong 2 tiếng\n";
	std::cout << "3. Hẹn giờ tắt máy trong 4 tiếng\n";
	std::cout << "4. Hẹn giờ tắt máy (nhập số tiếng)\n";
	std::cout << "5. Huỷ lịch trình tắt máy hiện tại\n";
	std::cout << "6. Thoát chương trình\n";
	std::cout << std::endl;
}
int menu::SelectOption() {
	int iOption;
	bool ValidOption = false;
	while (ValidOption == false) {
		std::cout << "Nhập lựa chọn: ";
		std::cin >> iOption;
		if (iOption > 0 && iOption < 7) {
			ValidOption = true;
		}
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		system("cls");
		ShowMenu();
	}
	return iOption;
}

bool menu::ProcessOption(int _option) {
	bool EXITPROGRAM = false;
	switch (_option) {
	case 1:
		system("shutdown -a");
		system("shutdown -s -t 3600");
		system("cls");
		ShowMenu();
		WinAPI->SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 1 tiếng.\n";
		WinAPI->SetColor(0, 11);
		std::cout << " > "; Animation->DotAnimation(1000); std::cout << std::flush;
		WinAPI->SetColor(0, 14);
		system("cls");
		ShowMenu();
		break;
	case 2:
		system("shutdown -a");
		system("shutdown -s -t 7200");
		system("cls");
		ShowMenu();
		WinAPI->SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 2 tiếng.\n";
		WinAPI->SetColor(0, 11);
		std::cout << " > "; Animation->DotAnimation(1000); std::cout << std::flush;
		WinAPI->SetColor(0, 14);
		system("cls");
		ShowMenu();
		break;
	case 3:
		system("shutdown -a");
		system("shutdown -s -t 14400");
		system("cls");
		ShowMenu();
		WinAPI->SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng 4 tiếng.\n";
		WinAPI->SetColor(0, 11);
		std::cout << " > "; Animation->DotAnimation(1000); std::cout << std::flush;
		WinAPI->SetColor(0, 14);
		system("cls");
		ShowMenu();
		break;
	case 4: {
		int h;
		int ph;
		system("shutdown -a");
		system("cls");
		ShowMenu();
		std::cout << "Nhập số tiếng: ";
		std::cin >> h;
		while (h < 1 || h > 24) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			system("cls");
			ShowMenu();
			WinAPI->SetColor(0, 12);
			std::cout << "Tối thiểu 1 tiếng hoặc tối đa 24 tiếng.\n";
			WinAPI->SetColor(0, 14);
			std::cout << "Nhập số tiếng: ";
			std::cin >> h;
		}
		ph = h * 3600;
		std::string ph2 = std::to_string(ph);
		system(("shutdown -s -t " + ph2).c_str());
		system("cls");
		ShowMenu();
		WinAPI->SetColor(0, 10);
		std::cout << "Máy tính sẽ được tắt trong vòng " << h << " tiếng.\n";
		WinAPI->SetColor(0, 11);
		std::cout << " > "; Animation->DotAnimation(1000); std::cout << std::flush;
		WinAPI->SetColor(0, 14);
		system("cls");
		ShowMenu();
		break;
	}
	case 5:
		system("shutdown -a");
		system("cls");
		ShowMenu();
		WinAPI->SetColor(0, 10);
		std::cout << "Đã huỷ lịch trình tắt máy hiện tại.\n";
		WinAPI->SetColor(0, 11);
		std::cout << " > "; Animation->DotAnimation(1000); std::cout << std::flush;
		WinAPI->SetColor(0, 14);
		system("cls");
		ShowMenu();
		break;
	case 6:
		system("cls");
		EXITPROGRAM = true;
		break;
	default:
		break;
	}
	return EXITPROGRAM;
}