#pragma once
#include "winapi.h"

class animation {
private:
	winapi* WinAPI;
public:
	animation(): WinAPI(NULL) {	//	Constructor
		//	std::cout << "[Debug#animation->animation()]: Constructor called" << std::endl;
	}
	animation(winapi* _WinAPI) {	//	Constructor (Get WinAPI Object)
		this->WinAPI = _WinAPI;
		//	std::cout << "[Debug#animation->animation(winapi* _WinAPI)]: Constructor called" << std::endl;
	}
	animation(const animation& _copy): WinAPI(NULL) {	//	Copy Constructor
		//	std::cout << "[Debug#animation->animation(const animation& _copy)]: Copy Constructor called" << std::endl;
	}
	~animation() {	//	Destructor
		//	std::cout << "[Debug#animation->~animation()]: Destructor called" << std::endl;
	}
	/*	Class Function Prototypes	*/
	void LoadAnimation();
	void DotAnimation(int _miliseconds);
};