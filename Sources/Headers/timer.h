#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

/*--[Prototypes]--*/

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in 'Loading()' function
 * - Return random integers within given range
 */
short GetRand(short minimum = 1, short maximum = 9);

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in 'SelectOption()', 'ProcessOption()' functions
 * - Clear console input stream (Prevent infinite loop bug)
 */
void ClearCinBuffer();

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in 'ProcessOption()' function
 * - Generate dots text on console
 */
void DotAnimation(unsigned short dot_number = 3, unsigned int milliseconds = 50, short flush = 1);

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in almost everywhere in 'Timer' class
 * - Manipulate console text color
 */
void SetColor(int backgound_color, int text_color);

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in Timer class's constructor
 * - Disable console selection
 */
void DisableSelection();

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in Timer class's constructor
 * - Set console window size
 */
void SetWindowSize(SHORT width, SHORT height);

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in Timer class's constructor
 * - Set console window buffer size
 */
void SetScreenBufferSize(SHORT width, SHORT height);

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in Timer class's constructor
 * - Disable resize console
 */
void DisableResizeWindow();

/*
 * This function is:
 * - Defined in 'func.h'
 * - Used in Timer class's constructor
 * - Disable console buttons (Close, Min, Max)
 */
void DisableCtrButton(bool Close, bool Min, bool Max);

/*--[Prototypes (END)]--*/

class Timer
{
private:

	// Default program setting variables
	std::string Language = "en";
	bool FasterLoad = false;
	bool EnableConsoleSelection = false;
	bool EnableResize = false;

	// This function reading config file or generate one if the file doesn't exists
	void Config();

	// This function simulate application loading progress (FOR FUN)
	void Loading();

public:

	/* Constructors & Destructor */
	Timer() 
	{
		Config(); // Read config file or generate one if the file doesn't exists
		SetPriorityClass(GetCurrentProcess(), THREAD_PRIORITY_LOWEST); // Run the program on lowest priority for optimize performance
		SetConsoleOutputCP(65001); // Support UTF-8 unicode for the console
		if (this->Language == "en") SetConsoleTitle(L"Simple Shutdown Timer v2.0"); 
		else if (this->Language == "vi") { SetConsoleTitle(L"Bộ Hẹn Giờ v2.0"); }

		SetColor(0, 14);
		srand((unsigned int)time(0)); // Set random seed for rand()
		if (this->EnableConsoleSelection == false) DisableSelection(); // Disable console selection
		SetWindowSize(60, 15); // Set window size
		SetScreenBufferSize(60, 15); // Set window buffer size
		if (this->EnableResize == false) DisableResizeWindow(); // Disable resize console
		if (this->EnableResize == false) DisableCtrButton(0, 0, 1); // Disable Minimize & Maximize buttons
		if (this->FasterLoad == false) this->Loading(); // This skip loading animation
	}
	~Timer() {}
	
public:

	void ShowMenu();
	short SelectOption();
	bool ProcessOption(short option);

};

