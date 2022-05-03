#include <iostream>
#include <Windows.h>
#include "../Sources/Headers/animation.h"
#include "../Sources/Headers/winapi.h"


/*	Define 'animation' class functions	*/
void animation::LoadAnimation() {
	WinAPI->SetColor(0, 14);
	for (double i = 0; i < 100; i++) {
		int y = (int)round(i);
		std::cout << "Đang tải (" << y << "%)";
		if (i < 100) i *= 1.4;
		system("cls");
	}
}

void animation::DotAnimation(int _miliseconds) {
	for (int i = 0; i < 3; i++) {
		Sleep(_miliseconds);
		std::cout << ".";
	}
}