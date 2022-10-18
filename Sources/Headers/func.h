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

/// PROGRAM PROCEDURES'S FORWARD DECLARATION
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SSButtonHover(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

namespace cExtra 
{
	void GetDesktopResolution(int& horizontal, int& vertical)
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

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

	bool CALLBACK SetFont(HWND child_hwnd, LPARAM hFont)
	{
		SendMessageW(child_hwnd, WM_SETFONT, hFont, TRUE);
		return true;
	}

	HFONT CreateHFONT(std::wstring fName, int fSize)
	{
		HFONT ret_hFONT = CreateFontW(fSize, 0, 0, 0x1,
			FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (LPCWSTR)fName.c_str());

		return ret_hFONT;
	}

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
}

namespace cWin32
{
	bool InitExtra(HWND hWnd, RECT& rc)
	{
		// eSol->FindBorderThickness(hWnd, rc);
		return true;
	}

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

		hIcon_Close = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON2), IMAGE_ICON, 50, 50, NULL);
		hIcon_Close_H = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON3), IMAGE_ICON, 50, 50, NULL);
		hIcon_Minimize = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON4), IMAGE_ICON, 50, 50, NULL);
		hIcon_Minimize_H = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON5), IMAGE_ICON, 50, 50, NULL);
		hIcon_Confirm = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON6), IMAGE_ICON, 100, 100, NULL);
		hIcon_Github = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON7), IMAGE_ICON, 80, 33, NULL);
		hIcon_Github_H = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON8), IMAGE_ICON, 80, 33, NULL);

		return true;
	}

	bool InitControl(HWND hWnd, bool skip = 0)
	{
		if (skip)
			return false;
		
		SSCtrl_Close = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 450, 0, 50, 50, hWnd, (HMENU)BUTTON_CLOSE, NULL, NULL);
		SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close);
		SetWindowSubclass(SSCtrl_Close, &SSButtonHover, 1, NULL);

		SSCtrl_Minimize = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 400, 0, 50, 50, hWnd, (HMENU)BUTTON_MINIMIZE, NULL, NULL);
		SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
		SetWindowSubclass(SSCtrl_Minimize, &SSButtonHover, 1, NULL);

		SSCtrl_Title1 = CreateWindowW(L"STATIC", MITitle_1.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 70, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text1 = CreateWindowW(L"STATIC", MI_1.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 117, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_1 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);

		EditCtrl_1 = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);
		if (!sType) ShowWindow(EditCtrl_1, SW_HIDE);
		EditCtrl_1e = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text2 = CreateWindowW(L"STATIC", MI_2.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 152, 420, 30, hWnd, NULL, NULL, NULL);
		
		CBCtrl_2 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 150, 110, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text3 = CreateWindowW(L"STATIC", MI_3.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 187, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_3 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 185, 110, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_SetTimer = CreateWindowW(L"BUTTON", L"",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CENTER | BS_ICON, 280, 114, 180, 102, hWnd, (HMENU)BUTTON_CONFIRM, NULL, NULL);
		SendMessageW(ButtonCtrl_SetTimer, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Confirm);
		
		SSCtrl_Title2 = CreateWindowW(L"STATIC", MITitle_2.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 230, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text4 = CreateWindowW(L"STATIC", MI_4.c_str(),
		    WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 277, 420, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_FMOFF = CreateWindowW(L"BUTTON", L"OFF",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 
			147, 274, 55, 30, hWnd, (HMENU)BUTTON_FMODEOFF, NULL, NULL);

		ButtonCtrl_FMON = CreateWindowW(L"BUTTON", L"ON",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			207, 274, 55, 30, hWnd, (HMENU)BUTTON_FMODEON, NULL, NULL);

		if (cFastMode)
			SendMessageW(ButtonCtrl_FMON, BM_SETCHECK, BST_CHECKED, NULL);
		else SendMessageW(ButtonCtrl_FMOFF, BM_SETCHECK, BST_CHECKED, NULL);

		SSCtrl_Text5 = CreateWindowW(L"STATIC", MI_5.c_str(),
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 312, 420, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_EMOFF = CreateWindowW(L"BUTTON", L"OFF",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
			147, 309, 55, 30, hWnd, (HMENU)BUTTON_EMODEOFF, NULL, NULL);

		ButtonCtrl_EMON = CreateWindowW(L"BUTTON", L"ON",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			207, 309, 55, 30, hWnd, (HMENU)BUTTON_EMODEON, NULL, NULL);

		if (cExtraMode)
		{
			SendMessageW(ButtonCtrl_EMON, BM_SETCHECK, BST_CHECKED, NULL);
			ShowWindow(EditCtrl_1, SW_HIDE);
			ShowWindow(CBCtrl_1, SW_HIDE);
			sType = 0;
			EnableWindow(CBCtrl_3, 0);
		}
		else
		{
			SendMessageW(ButtonCtrl_EMOFF, BM_SETCHECK, BST_CHECKED, NULL);
			ShowWindow(EditCtrl_1e, SW_HIDE);
		}

		ButtonCtrl_CancelTimer = CreateWindowW(L"BUTTON", MI_6.c_str(),
			WS_VISIBLE | WS_CHILD | BS_CENTER, 40+6+50-5-1, 344, 165-3+1, 33, hWnd, (HMENU)BUTTON_CANCEL, NULL, NULL);

		ButtonCtrl_ChangeLanguage = CreateWindowW(L"BUTTON", MI_7.c_str(),
			WS_VISIBLE | WS_CHILD | BS_CENTER, 40+6, 344, 50-5, 33, hWnd, (HMENU)BUTTON_CHANGELANGUAGE, NULL, NULL);

		SSCtrl_Github = CreateWindowW(L"STATIC", L"",
			WS_VISIBLE | WS_CHILD | SS_NOTIFY | SS_ICON | SS_CENTERIMAGE, 500-80-40, 344, 80, 33+5, hWnd, (HMENU)BUTTON_GITHUB, NULL, NULL);
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
			if (cLang == L"EN")
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
			else if (cLang == L"VI")
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

	bool EndCreate(HWND hWnd, bool skip = 0)
	{
		if (skip)
			return false;

		EnumChildWindows(hWnd, (WNDENUMPROC)cExtra::SetFont, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 22));
		cExtra::SetFont(SSCtrl_Title1, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 25));
		cExtra::SetFont(SSCtrl_Title2, (LPARAM)cExtra::CreateHFONT(L"Tahoma", 25));

		HANDLE hToken;
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
		if (!eSol->SetPrivilege(hToken, SE_SHUTDOWN_NAME, TRUE))
		{
			MessageBoxW(hWnd, L"Error occurred!\n(Lack of permissions)", L"", MB_OK);
			DestroyWindow(G_hWnd);
		}
		CloseHandle(hToken);

		return true;
	}

	void SetLang(std::wstring language, bool isInit = 0)
	{
		if (language != L"EN" && language != L"VI")
		{
			if (G_hWnd)
				DestroyWindow(G_hWnd);
			exit(1);
		}

		if (isInit)
		{
			if (language == L"EN")
			{
				AppTitle = L"Shutdown Timer";
				MBLimit_1 = L"Enter minimum 1 hour or maximum 24 hours";
				MBLimit_2 = L"Enter minimum 1 minute or maximum 1440 minutes";
				MBAlreadyScheduled = L"The PC already have schedule set\nCancel current schedule?\n(Old schedule will be overwritten)";
				MBResult_1 = L"The PC will be shutdown after ";
				MBResult_2 = L" hour(s)";
				MBResult_2a = L" minute(s)";
				MITitle_1 = L" Timers:";
				MITitle_2 = L" Options:";
				MI_1 = L"→   Time:";
				MI_2 = L"→   Mode:";
				MI_3 = L"→   Unit:";
				MI_4 = L" Fast Mode:";
				MI_5 = L" Extra Mode:";
				MI_6 = L"Abort Schedules";
				MI_7 = L"EN";
			}
			else if (language == L"VI")
			{
				AppTitle = L"Bộ hẹn giờ";
				MBLimit_1 = L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng";
				MBLimit_2 = L"Nhập tối thiểu 1 phút hoặc tối đa 1440 phút";
				MBAlreadyScheduled = L"Máy tính đã có lịch tắt máy\nHuỷ lịch tắt máy hiện tại?\n(Sẽ ghi đè bằng lịch hẹn mới)";
				MBResult_1 = L"Máy tính sẽ được tắt sau ";
				MBResult_2 = L" tiếng";
				MBResult_2a = L" phút";
				MITitle_1 = L" Bộ hẹn giờ:";
				MITitle_2 = L" Cài đặt:";
				MI_1 = L"→ Thời gian:";
				MI_2 = L"→  Chế độ:";
				MI_3 = L"→   Kiểu:";
				MI_4 = L" Fast Mode:";
				MI_5 = L" Extra Mode:";
				MI_6 = L"Huỷ lệnh hiện tại";
				MI_7 = L"VI";
			}
		}
		else
		{
			if (language == L"EN")
			{
				AppTitle = L"Shutdown Timer";
				MBLimit_1 = L"Enter minimum 1 hour or maximum 24 hours";
				MBLimit_2 = L"Enter minimum 1 minute or maximum 1440 minutes";
				MBAlreadyScheduled = L"The PC already have schedule set\nCancel current schedule?\n(Old schedule will be overwritten)";
				MBResult_1 = L"The PC will be shutdown after ";
				MBResult_2 = L" hour(s)";
				MBResult_2a = L" minute(s)";
				MITitle_1 = L" Timers:";
				MITitle_2 = L" Options:";
				MI_1 = L"→   Time:";
				MI_2 = L"→   Mode:";
				MI_3 = L"→   Unit:";
				MI_4 = L" Fast Mode:";
				MI_5 = L" Extra Mode:";
				MI_6 = L"Abort Schedules";
				SetWindowTextW(G_hWnd, AppTitle.c_str());
				SetWindowTextW(SSCtrl_Title1, MITitle_1.c_str());
				SetWindowTextW(SSCtrl_Title2, MITitle_2.c_str());
				SetWindowTextW(SSCtrl_Text1, MI_1.c_str());
				SetWindowTextW(SSCtrl_Text2, MI_2.c_str());
				SetWindowTextW(SSCtrl_Text3, MI_3.c_str());
				SetWindowTextW(SSCtrl_Text4, MI_4.c_str());
				SetWindowTextW(SSCtrl_Text5, MI_5.c_str());
				SetWindowTextW(ButtonCtrl_CancelTimer, MI_6.c_str());
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
				if (!sType) SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
				else SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
			}
			else if (language == L"VI")
			{
				AppTitle = L"Bộ hẹn giờ";
				MBLimit_1 = L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng";
				MBLimit_2 = L"Nhập tối thiểu 1 phút hoặc tối đa 1440 phút";
				MBAlreadyScheduled = L"Máy tính đã có lịch tắt máy\nHuỷ lịch tắt máy hiện tại?\n(Sẽ ghi đè bằng lịch hẹn mới)";
				MBResult_1 = L"Máy tính sẽ được tắt sau ";
				MBResult_2 = L" tiếng";
				MBResult_2a = L" phút";
				MITitle_1 = L" Bộ hẹn giờ:";
				MITitle_2 = L" Cài đặt:";
				MI_1 = L"→ Thời gian:";
				MI_2 = L"→  Chế độ:";
				MI_3 = L"→   Kiểu:";
				MI_4 = L" Fast Mode:";
				MI_5 = L" Extra Mode:";
				MI_6 = L"Huỷ lệnh hiện tại";
				SetWindowTextW(G_hWnd, AppTitle.c_str());
				SetWindowTextW(SSCtrl_Title1, MITitle_1.c_str());
				SetWindowTextW(SSCtrl_Title2, MITitle_2.c_str());
				SetWindowTextW(SSCtrl_Text1, MI_1.c_str());
				SetWindowTextW(SSCtrl_Text2, MI_2.c_str());
				SetWindowTextW(SSCtrl_Text3, MI_3.c_str());
				SetWindowTextW(SSCtrl_Text4, MI_4.c_str());
				SetWindowTextW(SSCtrl_Text5, MI_5.c_str());
				SetWindowTextW(ButtonCtrl_CancelTimer, MI_6.c_str());
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
				if (!sType) SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
				else SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
			}
		}
	}

	void RefreshApp()
	{
		UpdateWindow(G_hWnd);
		RECT tRect;
		GetClientRect(G_hWnd, &tRect);
		RedrawWindow(G_hWnd, &tRect, NULL, RDW_INVALIDATE);
	}

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
					if (name == L"FastMode" || name == L"FastMode ") { if (value == L"1" || value == L"true" || value == L"on" || value == L"yes") cFastMode = true; else cFastMode = false; }
					else if (name == L"ExtraMode" || name == L"ExtraMode ") { if (value == L"1" || value == L"true" || value == L"on" || value == L"yes") cExtraMode = true; else cExtraMode = false; }
					else if (name == L"Language" || name == L"Language ") 
					{ 
						if (value == L"EN" || value == L"en" || value == L"ENGLISH" || value == L"english") cLang = L"EN";
						else if (value == L"VI" || value == L"vi" || value == L"VN" || value == L"vn") cLang = L"VI";
						else cLang = L"EN";
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
					if (cExtraMode) apExtraMode += L"1"; else apExtraMode += L"0";
					if (cLang == L"EN") apLang += L"en"; else if (cLang == L"VI") apLang += L"vi";
					

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

					if (cFastMode) apFastMode += L"1"; else apFastMode += L"0";
					apExtraMode += mVal;
					if (cLang == L"EN") apLang += L"en"; else if (cLang == L"VI") apLang += L"vi";

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

					if (cFastMode) apFastMode += L"1"; else apFastMode += L"0";
					if (cExtraMode) apExtraMode += L"1"; else apExtraMode += L"0";
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