#pragma once

#include "c_resource.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <Windows.h>
#include <Windowsx.h>
#include <Uxtheme.h>
#include <commctrl.h>
#include <Dwmapi.h>
#include <mmsystem.h>
#include "solution.h"
#include "global.h"

/// FORWARD DECLARATIONS:
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SSButtonHover(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

/// FUNCTIONS:
namespace cExtra 
{
	// Get desktop resolution
	void GetDesktopResolution(int& horizontal, int& vertical)
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

	// Show window sizes via message boxes (Debug)
	bool cShowSizeInfo(HWND hWnd)
	{
		RECT tRect;
		int cWidth = 0, wWidth = 0;
		int cHeight = 0, wHeight = 0;

		if (!GetClientRect(hWnd, &tRect))
			return false;
		cWidth = tRect.right - tRect.left;
		cHeight = tRect.bottom - tRect.top;

		if (!GetWindowRect(hWnd, &tRect))
			return false;
		wWidth = tRect.right - tRect.left;
		wHeight = tRect.bottom - tRect.top;

		MessageBoxW(NULL,
			(((std::wstring)L"Client Width: " + std::to_wstring(cWidth) + L" Client Height: " + std::to_wstring(cHeight)
				+ L"\nWindow Width: " + std::to_wstring(wWidth) + L" Window Height: " + std::to_wstring(wHeight)).c_str()), L"", MB_OK);
		return true;
	}

	// Set HWND's font (CALLBACK function for EnumChildWindows)
	bool CALLBACK SetFont(HWND child_hwnd, LPARAM hFont)
	{
		SendMessageW(child_hwnd, WM_SETFONT, hFont, TRUE);
		return true;
	}

	// Create HFONTs
	HFONT CreateHFONT(std::wstring fName, int fSize)
	{
		HFONT ret_hFONT = CreateFontW(fSize, 0, 0, 0x1,
			FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)fName.c_str());

		return ret_hFONT;
	}

	// Execute command (Debug)
	void ExecCmd(std::string sCmdLine)
	{
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcessA("C:\\Windows\\System32\\cmd.exe",    // The path
			(LPSTR)sCmdLine.c_str(),                        // Command line
			NULL,               // Process handle not inheritable
			NULL,               // Thread handle not inheritable
			FALSE,              // Set handle inheritance to FALSE
			CREATE_NO_WINDOW,   // "CREATE_NO_WINDOW" flag prevent command prompt from showing up
			NULL,               // Use parent's environment block
			NULL,               // Use parent's starting directory 
			&si,                // Pointer to STARTUPINFO structure
			&pi                 // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
		);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	// Get machine name
	std::wstring GetMachineName()
	{
		WCHAR tBuffer[MAX_COMPUTERNAME_LENGTH + 1];
		memset(tBuffer, 0, sizeof(tBuffer));
		DWORD machineNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		GetComputerNameW(tBuffer, &machineNameSize);

		std::wstring lwstr = tBuffer;
		return lwstr;
	}
}

namespace cWin32
{
	bool InitExtraBegin(bool skip = 0)
	{
		if (skip)
			return false;

		return true;
	}

	// Initialize media handles
	bool InitMedia(bool skip = 0)
	{
		if (skip)
			return false;

		/*
		hIcon_Close = (HICON)LoadImageW(NULL, L"close.ico", IMAGE_ICON, 50, 50, LR_LOADFROMFILE);
		hIcon_Close_H = (HICON)LoadImageW(NULL, L"close_h.ico", IMAGE_ICON, 50, 50, LR_LOADFROMFILE);
		hIcon_Minimize = (HICON)LoadImageW(NULL, L"minimize.ico", IMAGE_ICON, 50, 50, LR_LOADFROMFILE);
		hIcon_Minimize_H = (HICON)LoadImageW(NULL, L"minimize_h.ico", IMAGE_ICON, 50, 50, LR_LOADFROMFILE);
		hIcon_Confirm = (HICON)LoadImageW(NULL, L"tick.ico", IMAGE_ICON, 100, 100, LR_LOADFROMFILE);
		hIcon_Github = (HICON)LoadImageW(NULL, L"github.ico", IMAGE_ICON, 80, 33, LR_LOADFROMFILE);
		hIcon_Github_H = (HICON)LoadImageW(NULL, L"github_h.ico", IMAGE_ICON, 80, 33, LR_LOADFROMFILE);
		*/

		hIcon_Close = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON2), IMAGE_ICON, 45, 45, NULL);
		hIcon_Close_H = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON3), IMAGE_ICON, 37, 37, NULL);
		hIcon_Minimize = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON4), IMAGE_ICON, 45, 45, NULL);
		hIcon_Minimize_H = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON5), IMAGE_ICON, 37, 37, NULL);
		hIcon_Confirm = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON6), IMAGE_ICON, 100, 100, NULL);
		hIcon_Github = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON7), IMAGE_ICON, 80, 33, NULL);
		hIcon_Github_H = (HICON)LoadImageW(MAIN_HINSTANCE, MAKEINTRESOURCEW(IDI_ICON8), IMAGE_ICON, 80, 33, NULL);

		return true;
	}
	
	// Initialize control handles
	bool InitControl(HWND hWnd, bool skip = 0)
	{
		if (skip)
			return false;
		
		SSCtrl_Close = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 442, 0, 58, 37, hWnd, (HMENU)BUTTON_CLOSE, NULL, NULL);
		SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close);
		SetWindowSubclass(SSCtrl_Close, &SSButtonHover, 1, NULL);

		SSCtrl_Minimize = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 384, 0, 58, 37, hWnd, (HMENU)BUTTON_MINIMIZE, NULL, NULL);
		SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
		SetWindowSubclass(SSCtrl_Minimize, &SSButtonHover, 1, NULL);

		SSCtrl_Title1 = CreateWindowW(L"STATIC", STR_MI_Title1.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 64, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text1 = CreateWindowW(L"STATIC", STR_MI_1.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 111, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_1 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 109, 110, 30, hWnd, NULL, NULL, NULL);

		EditCtrl_1 = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 109, 110, 30, hWnd, NULL, NULL, NULL);
		if (!AP_UNIT) ShowWindow(EditCtrl_1, SW_HIDE);
		EditCtrl_1e = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 109, 110, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text2 = CreateWindowW(L"STATIC", STR_MI_2.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 146, 420, 30, hWnd, NULL, NULL, NULL);
		
		CBCtrl_2 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 144, 110, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text3 = CreateWindowW(L"STATIC", STR_MI_3.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 181, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_3 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 179, 110, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_SetTimer = CreateWindowW(L"BUTTON", L"",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CENTER | BS_ICON, 280, 108, 180, 102, hWnd, (HMENU)BUTTON_CONFIRM, NULL, NULL);
		SendMessageW(ButtonCtrl_SetTimer, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Confirm);
		
		SSCtrl_Title2 = CreateWindowW(L"STATIC", STR_MI_Title2.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 224, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text4 = CreateWindowW(L"STATIC", STR_MI_4.c_str(),
		    WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 271, 420, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_FMOFF = CreateWindowW(L"BUTTON", L"OFF",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 
			147, 268, 55, 30, hWnd, (HMENU)BUTTON_FMODEOFF, NULL, NULL);

		ButtonCtrl_FMON = CreateWindowW(L"BUTTON", L"ON",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			207, 268, 55, 30, hWnd, (HMENU)BUTTON_FMODEON, NULL, NULL);

		if (AP_FASTMODE)
			SendMessageW(ButtonCtrl_FMON, BM_SETCHECK, BST_CHECKED, NULL);
		else SendMessageW(ButtonCtrl_FMOFF, BM_SETCHECK, BST_CHECKED, NULL);

		SSCtrl_Text5 = CreateWindowW(L"STATIC", STR_MI_5.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 306, 420, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_EMOFF = CreateWindowW(L"BUTTON", L"OFF",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
			147, 303, 55, 30, hWnd, (HMENU)BUTTON_EMODEOFF, NULL, NULL);

		ButtonCtrl_EMON = CreateWindowW(L"BUTTON", L"ON",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			207, 303, 55, 30, hWnd, (HMENU)BUTTON_EMODEON, NULL, NULL);

		if (AP_EXTRAMODE)
		{
			SendMessageW(ButtonCtrl_EMON, BM_SETCHECK, BST_CHECKED, NULL);
			ShowWindow(EditCtrl_1, SW_HIDE);
			ShowWindow(CBCtrl_1, SW_HIDE);
			AP_UNIT = 0;
			EnableWindow(CBCtrl_3, 0);
		}
		else
		{
			SendMessageW(ButtonCtrl_EMOFF, BM_SETCHECK, BST_CHECKED, NULL);
			ShowWindow(EditCtrl_1e, SW_HIDE);
		}

		ButtonCtrl_CancelTimer = CreateWindowW(L"BUTTON", STR_MI_6.c_str(),
			WS_VISIBLE | WS_CHILD | BS_CENTER, 90, 338, 163, 33, hWnd, (HMENU)BUTTON_CANCEL, NULL, NULL);

		ButtonCtrl_ChangeLanguage = CreateWindowW(L"BUTTON", STR_MI_7.c_str(),
			WS_VISIBLE | WS_CHILD | BS_CENTER, 40+6, 338, 45, 33, hWnd, (HMENU)BUTTON_CHANGELANGUAGE, NULL, NULL);

		SSCtrl_Github = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 380, 338, 80, 38, hWnd, (HMENU)BUTTON_GITHUB, NULL, NULL);
		SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github);
		SetWindowSubclass(SSCtrl_Github, &SSButtonHover, 1, NULL);

		{
			{
				WCHAR sdlOptions[6][3] =
				{
					TEXT("1"), TEXT("2"), TEXT("4"), TEXT("8"), TEXT("12"), TEXT("24")
				};
				WCHAR tBuffer[3];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 6; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_1, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				SendMessageW(CBCtrl_1, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			{
				WCHAR sdlOptions[2][9] =
				{
					TEXT("Shutdown"), TEXT("Restart")
				};
				WCHAR tBuffer[9];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 2; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_2, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				SendMessageW(CBCtrl_2, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			if (APP_LANGUAGE == L"EN")
			{
				WCHAR sdlOptions[2][7] =
				{
					TEXT("Hour"), TEXT("Minute")
				};
				WCHAR tBuffer[7];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 2; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_3, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
			else if (APP_LANGUAGE == L"VI")
			{
				WCHAR sdlOptions[2][7] =
				{
					TEXT("Giờ"), TEXT("Phút")
				};
				WCHAR tBuffer[7];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 2; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_3, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
			}
		}

		return true;
	}

	bool InitExtraEnd(HWND hWnd, bool skip = 0)
	{
		if (skip)
			return false;

		// Set control fonts
		EnumChildWindows(hWnd, (WNDENUMPROC)cExtra::SetFont, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 22));	// Default font
		cExtra::SetFont(SSCtrl_Title1, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 25));				
		cExtra::SetFont(SSCtrl_Title2, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 25));

		// Grant privilege "SE_SHUTDOWN_NAME" for the application
		HANDLE hToken;
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
		if (!eSol->SetPrivilege(hToken, SE_SHUTDOWN_NAME, TRUE))
		{
			MessageBoxW(hWnd, L"Error occurred!\n(Lack of permissions)", L"", MB_OK);
			DestroyWindow(MAIN_HWND);
		}
		CloseHandle(hToken);

		return true;
	}

	// Set application language
	void SetLanguage(std::wstring language, bool isInit = 0)
	{
		if (language != L"EN" && language != L"VI")
		{
			if (MAIN_HWND)
				DestroyWindow(MAIN_HWND);
			exit(1);
		}

		if (isInit)
		{
			if (language == L"EN")
			{
				STR_AppTitle = L"Shutdown Timer";
				STR_MB_Limit1 = L"Enter minimum 1 hour or maximum 24 hours";
				STR_MB_Limit2 = L"Enter minimum 1 minute or maximum 1440 minutes";
				STR_MB_AlreadyScheduled = L"The PC already have schedule set\nCancel current schedule?\n(Old schedule will be overwritten)";
				STR_MB_Result1 = L"The PC will be shutdown after ";
				STR_MB_Result2 = L" hour(s)";
				STR_MB_Result2A = L" minute(s)";
				STR_MI_Title1 = L" Timers:";
				STR_MI_Title2 = L" Options:";
				STR_MI_1 = L"→   Time:";
				STR_MI_2 = L"→   Mode:";
				STR_MI_3 = L"→   Unit:";
				STR_MI_4 = L" Fast Mode:";
				STR_MI_5 = L" Extra Mode:";
				STR_MI_6 = L"Abort Schedules";
				STR_MI_7 = L"EN";
			}
			else if (language == L"VI")
			{
				STR_AppTitle = L"Bộ hẹn giờ";
				STR_MB_Limit1 = L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng";
				STR_MB_Limit2 = L"Nhập tối thiểu 1 phút hoặc tối đa 1440 phút";
				STR_MB_AlreadyScheduled = L"Máy tính đã có lịch tắt máy\nHuỷ lịch tắt máy hiện tại?\n(Sẽ ghi đè bằng lịch hẹn mới)";
				STR_MB_Result1 = L"Máy tính sẽ được tắt sau ";
				STR_MB_Result2 = L" tiếng";
				STR_MB_Result2A = L" phút";
				STR_MI_Title1 = L" Bộ hẹn giờ:";
				STR_MI_Title2 = L" Cài đặt:";
				STR_MI_1 = L"→ Thời gian:";
				STR_MI_2 = L"→  Chế độ:";
				STR_MI_3 = L"→   Kiểu:";
				STR_MI_4 = L" Fast Mode:";
				STR_MI_5 = L" Extra Mode:";
				STR_MI_6 = L"Huỷ lệnh hiện tại";
				STR_MI_7 = L"VI";
			}
		}
		else
		{
			if (language == L"EN")
			{
				STR_AppTitle = L"Shutdown Timer";
				STR_MB_Limit1 = L"Enter minimum 1 hour or maximum 24 hours";
				STR_MB_Limit2 = L"Enter minimum 1 minute or maximum 1440 minutes";
				STR_MB_AlreadyScheduled = L"The PC already have schedule set\nCancel current schedule?\n(Old schedule will be overwritten)";
				STR_MB_Result1 = L"The PC will be shutdown after ";
				STR_MB_Result2 = L" hour(s)";
				STR_MB_Result2A = L" minute(s)";
				STR_MI_Title1 = L" Timers:";
				STR_MI_Title2 = L" Options:";
				STR_MI_1 = L"→   Time:";
				STR_MI_2 = L"→   Mode:";
				STR_MI_3 = L"→   Unit:";
				STR_MI_4 = L" Fast Mode:";
				STR_MI_5 = L" Extra Mode:";
				STR_MI_6 = L"Abort Schedules";
				SetWindowTextW(MAIN_HWND, STR_AppTitle.c_str());
				SetWindowTextW(SSCtrl_Title1, STR_MI_Title1.c_str());
				SetWindowTextW(SSCtrl_Title2, STR_MI_Title2.c_str());
				SetWindowTextW(SSCtrl_Text1, STR_MI_1.c_str());
				SetWindowTextW(SSCtrl_Text2, STR_MI_2.c_str());
				SetWindowTextW(SSCtrl_Text3, STR_MI_3.c_str());
				SetWindowTextW(SSCtrl_Text4, STR_MI_4.c_str());
				SetWindowTextW(SSCtrl_Text5, STR_MI_5.c_str());
				SetWindowTextW(ButtonCtrl_CancelTimer, STR_MI_6.c_str());
				SendMessageW(CBCtrl_3, CB_DELETESTRING, 0, NULL);
				SendMessageW(CBCtrl_3, CB_DELETESTRING, 0, NULL);
				WCHAR sdlOptions[2][7] =
				{
					TEXT("Hour"), TEXT("Minute")
				};
				WCHAR tBuffer[7];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 2; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_3, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				if (!AP_UNIT) SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
				else SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
			}
			else if (language == L"VI")
			{
				STR_AppTitle = L"Bộ hẹn giờ";
				STR_MB_Limit1 = L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng";
				STR_MB_Limit2 = L"Nhập tối thiểu 1 phút hoặc tối đa 1440 phút";
				STR_MB_AlreadyScheduled = L"Máy tính đã có lịch tắt máy\nHuỷ lịch tắt máy hiện tại?\n(Sẽ ghi đè bằng lịch hẹn mới)";
				STR_MB_Result1 = L"Máy tính sẽ được tắt sau ";
				STR_MB_Result2 = L" tiếng";
				STR_MB_Result2A = L" phút";
				STR_MI_Title1 = L" Bộ hẹn giờ:";
				STR_MI_Title2 = L" Cài đặt:";
				STR_MI_1 = L"→ Thời gian:";
				STR_MI_2 = L"→  Chế độ:";
				STR_MI_3 = L"→   Kiểu:";
				STR_MI_4 = L" Fast Mode:";
				STR_MI_5 = L" Extra Mode:";
				STR_MI_6 = L"Huỷ lệnh hiện tại";
				SetWindowTextW(MAIN_HWND, STR_AppTitle.c_str());
				SetWindowTextW(SSCtrl_Title1, STR_MI_Title1.c_str());
				SetWindowTextW(SSCtrl_Title2, STR_MI_Title2.c_str());
				SetWindowTextW(SSCtrl_Text1, STR_MI_1.c_str());
				SetWindowTextW(SSCtrl_Text2, STR_MI_2.c_str());
				SetWindowTextW(SSCtrl_Text3, STR_MI_3.c_str());
				SetWindowTextW(SSCtrl_Text4, STR_MI_4.c_str());
				SetWindowTextW(SSCtrl_Text5, STR_MI_5.c_str());
				SetWindowTextW(ButtonCtrl_CancelTimer, STR_MI_6.c_str());
				SendMessageW(CBCtrl_3, CB_DELETESTRING, 0, NULL);
				SendMessageW(CBCtrl_3, CB_DELETESTRING, 0, NULL);
				WCHAR sdlOptions[2][7] =
				{
					TEXT("Giờ"), TEXT("Phút")
				};
				WCHAR tBuffer[7];
				memset(&tBuffer, 0, sizeof(tBuffer));
				for (int i = 0; i < 2; i++)
				{
					wcscpy_s(tBuffer, sizeof(tBuffer) / sizeof(WCHAR), (WCHAR*)sdlOptions[i]);
					SendMessageW(CBCtrl_3, CB_ADDSTRING, 0, (LPARAM)tBuffer);
				}
				if (!AP_UNIT) SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
				else SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
			}
		}
	}

	// Refresh application draws
	void RefreshApp()
	{
		UpdateWindow(MAIN_HWND);
		RECT tRect;
		GetClientRect(MAIN_HWND, &tRect);
		RedrawWindow(MAIN_HWND, &tRect, NULL, RDW_INVALIDATE);
	}

	// Load application parameters from config file
	void LoadConfig()
	{
		short Attempts = 0;
		bool FirstWarning = 1;
		while (true)
		{
			std::wifstream cFile(L"settings.cfg");
			if (cFile.is_open()) // Check if the file is exists
			{
				std::locale utf8_loc(std::locale(), new std::codecvt_utf8<wchar_t>);
				cFile.imbue(utf8_loc); // Set locale before making any conversion

				std::wstring line;
				while (std::getline(cFile, line))
				{
					// line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); | Remove all whitespaces on line
					if (line[0] == '#' || line.empty()) continue; // Ignore lines start with '#' or empty lines

					auto delimiterPos = line.find(L"=");
					auto name = line.substr(0, delimiterPos);
					auto value = line.substr(delimiterPos + 1);
					if (value[0] == ' ') value = line.substr(delimiterPos + 2);

					// Scan and read data from file
					if (name == L"FastMode" || name == L"FastMode ") { if (value == L"1" || value == L"true" || value == L"on" || value == L"yes") AP_FASTMODE = true; else AP_FASTMODE = false; }
					else if (name == L"ExtraMode" || name == L"ExtraMode ") { if (value == L"1" || value == L"true" || value == L"on" || value == L"yes") AP_EXTRAMODE = true; else AP_EXTRAMODE = false; }
					else if (name == L"Language" || name == L"Language ") 
					{ 
						if (value == L"EN" || value == L"en" || value == L"ENGLISH" || value == L"english") APP_LANGUAGE = L"EN";
						else if (value == L"VI" || value == L"vi" || value == L"VN" || value == L"vn") APP_LANGUAGE = L"VI";
						else APP_LANGUAGE = L"EN";
					}
				}
				cFile.close(); // Close file
				break;
			}
			else {
				if (FirstWarning == 1) { MessageBoxW(NULL, L"Default settings file not found, generating one ..", L"", MB_OK | MB_ICONINFORMATION); FirstWarning = 0; }
				std::wofstream oFile(L"settings.cfg");
				std::locale utf8_loc(std::locale(), new std::codecvt_utf8<wchar_t>);
				oFile.imbue(utf8_loc); // Set locale before making any conversion
				oFile << L"# Available settings: FastMode, ExtraMode\n# Available languages: en, vi\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = 0\nExtraMode = 0\nLanguage = en"; // Write default config file
				oFile.close(); // Close file
				if (Attempts == 3) { MessageBoxW(NULL, L"Error occurred!\n(Lack of read/write permission)\n- Try to run the application as administrator", L"", MB_OK | MB_ICONERROR); exit(1); }
				Attempts++;
			}
		}
	}

	// Update config file
	void UpdateConfig(std::wstring mID, std::wstring mVal)
	{
		std::wstring APPEND;
		std::wstring apFastMode = L"";
		std::wstring apExtraMode = L"";
		std::wstring apLang = L"";

		if (mID == L"FASTMODE")
		{
			short Attempts = 0;
			while (true)
			{
				std::wofstream oFile(L"settings.cfg");
				if (oFile.is_open()) // Check if the file is exists
				{
					std::locale utf8_loc(std::locale(), new std::codecvt_utf8<wchar_t>);
					oFile.imbue(utf8_loc); // Set locale before making any conversion

					apFastMode += mVal;
					if (AP_EXTRAMODE) apExtraMode += L"1"; else apExtraMode += L"0";
					if (APP_LANGUAGE == L"EN") apLang += L"en"; else if (APP_LANGUAGE == L"VI") apLang += L"vi";
					

					APPEND = L"# Available settings: FastMode, ExtraMode\n# Available languages: en, vi\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = ";
					APPEND += apFastMode;
					APPEND += L"\nExtraMode = ";
					APPEND += apExtraMode;
					APPEND += L"\nLanguage = ";
					APPEND += apLang;


					oFile << APPEND;
					oFile.close(); // Close file
					break;
				}
				else
				{
					if (Attempts == 3) { MessageBoxW(NULL, L"Error occurred!\n(Lack of read/write permission)\n- Try to run the application as administrator", L"", MB_OK | MB_ICONERROR); exit(1); }
					Attempts++;
				}
			}
			return;
		}
		else if (mID == L"EXTRAMODE")
		{
			short Attempts = 0;
			while (true)
			{
				std::wofstream oFile(L"settings.cfg");
				if (oFile.is_open()) // Check if the file is exists
				{
					std::locale utf8_loc(std::locale(), new std::codecvt_utf8<wchar_t>);
					oFile.imbue(utf8_loc); // Set locale before making any conversion

					if (AP_FASTMODE) apFastMode += L"1"; else apFastMode += L"0";
					apExtraMode += mVal;
					if (APP_LANGUAGE == L"EN") apLang += L"en"; else if (APP_LANGUAGE == L"VI") apLang += L"vi";

					APPEND = L"# Available settings: FastMode, ExtraMode\n# Available languages: en, vi\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = ";
					APPEND += apFastMode;
					APPEND += L"\nExtraMode = ";
					APPEND += apExtraMode;
					APPEND += L"\nLanguage = ";
					APPEND += apLang;


					oFile << APPEND;
					oFile.close(); // Close file
					break;
				}
				else
				{
					if (Attempts == 3) { MessageBoxW(NULL, L"Error occurred!\n(Lack of read/write permission)\n- Try to run the application as administrator", L"", MB_OK | MB_ICONERROR); exit(1); }
					Attempts++;
				}
			}
			return;
		}
		else if (mID == L"LANGUAGE")
		{
			short Attempts = 0;
			while (true)
			{
				std::wofstream oFile(L"settings.cfg");
				if (oFile.is_open()) // Check if the file is exists
				{
					std::locale utf8_loc(std::locale(), new std::codecvt_utf8<wchar_t>);
					oFile.imbue(utf8_loc); // Set locale before making any conversion

					if (AP_FASTMODE) apFastMode += L"1"; else apFastMode += L"0";
					if (AP_EXTRAMODE) apExtraMode += L"1"; else apExtraMode += L"0";
					apLang += mVal;

					APPEND = L"# Available settings: FastMode, ExtraMode\n# Available languages: en, vi\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = ";
					APPEND += apFastMode;
					APPEND += L"\nExtraMode = ";
					APPEND += apExtraMode;
					APPEND += L"\nLanguage = ";
					APPEND += apLang;


					oFile << APPEND;
					oFile.close(); // Close file
					break;
				}
				else
				{
					if (Attempts == 3) { MessageBoxW(NULL, L"Error occurred!\n(Lack of read/write permission)\n- Try to run the application as administrator", L"", MB_OK | MB_ICONERROR); exit(1); }
					Attempts++;
				}
			}
			return;
		}
	}
}