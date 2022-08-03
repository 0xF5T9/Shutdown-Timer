#pragma once
#define NOMINMAX

#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <limits>
#include "timer.h"

short GetRand(short minimum, short maximum)
{	
	// Formula: rand() % (max_number + 1 - minimum_number) + minimum_number
	short ret = rand() % (maximum + 1 - minimum) + minimum;
	return ret;
}

void ClearCinBuffer()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void DotAnimation(unsigned short dot_number ,unsigned int milliseconds, short flush)
{
	for (int i = 0; i < dot_number; i++)
	{
		std::cout << ".";
		Sleep(milliseconds);
	}
	
	if (flush == 1) std::cout << "\n";
	else if (flush == 2) std::cout << std::endl;
}

void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

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

void DisableCtrButton(bool Close, bool Min, bool Max)
{
	HWND hWnd = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hWnd, false);

	if (Close == 1)
	{
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	if (Min == 1)
	{
		DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
	}
	if (Max == 1)
	{
		DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
	}
}

Timer* InitializeApplication()
{
	SetConsoleTitle(L"Initializng ...");
	Timer* RetObject = new Timer();
	return RetObject;
}

void Terminate(Timer* Timer_Ptr)
{
	delete Timer_Ptr;
}