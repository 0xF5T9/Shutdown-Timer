#pragma once
#include <iostream>
#include "winapi.h"
#include "animation.h"
#include "menu.h"

/*	Define create object functions	*/
winapi* CreateObjectWinAPI() {
	winapi* CreateObject = new winapi();
	return CreateObject;
}

animation* CreateObjectAnimation(winapi* _WinAPI) {
	animation* CreateObject = new animation(_WinAPI);
	return CreateObject;
}

menu* CreateObjectMenu(winapi* _WinAPI, animation* _Animation) {
	menu* CreateObject = new menu(_WinAPI, _Animation);
	return CreateObject;
}

/*	Define free object memory functions	*/
void FreeMemory(winapi* _Ptr) {
	//	std::cout << "[Debug#Func->FreeMemory]: Object memory deallocated (winapi)" << std::endl;
	delete _Ptr;
}

void FreeMemory(animation* _Ptr) {
	//	std::cout << "[Debug#Func->FreeMemory]: Object memory deallocated (animation)" << std::endl;
	delete _Ptr;
}

void FreeMemory(menu* _Ptr) {
	//	std::cout << "[Debug#Func->FreeMemory]: Object memory deallocated (menu)" << std::endl;
	delete _Ptr;
}