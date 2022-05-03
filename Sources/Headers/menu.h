#pragma once
#include "winapi.h"
#include "animation.h"

class menu {
private:
	winapi* WinAPI;
	animation* Animation;
public:
	menu(): WinAPI(NULL), Animation(NULL) {	//	Constructor
		//	std::cout << "[Debug#menu->menu()]: Constructor called" << std::endl;
	}
	menu(winapi* _WinAPI, animation* _Animation) {	//	Constructor (w/WinAPI & Animation Object)
		this->WinAPI = _WinAPI;
		this->Animation = _Animation;
		//	std::cout << "[Debug#menu->menu(winapi* _WinAPI, animation* _Animation)]: Constructor called" << std::endl;
	}
	menu(const menu& _copy): WinAPI(NULL), Animation(NULL) {	//	Copy Constructor
		//	std::cout << "[Debug#menu->menu(const menu& _copy)]: Copy Constructor called" << std::endl;
	}
	~menu() {	//	Destructor
		//	std::cout << "[Debug#menu->~menu()]: Destructor called" << std::endl;
	}
	/*	Class Function Prototypes	*/
	void ShowMenu() const;
	int SelectOption();
	bool ProcessOption(int _option);
};