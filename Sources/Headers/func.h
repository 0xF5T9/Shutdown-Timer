#pragma once

#include "c_resource.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <Windowsx.h>
#include <Uxtheme.h>
#include <commctrl.h>
#include <Dwmapi.h>
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
		*/

		hIcon_Close = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON2), IMAGE_ICON, 50, 50, NULL);
		hIcon_Close_H = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON3), IMAGE_ICON, 50, 50, NULL);
		hIcon_Minimize = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON4), IMAGE_ICON, 50, 50, NULL);
		hIcon_Minimize_H = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON5), IMAGE_ICON, 50, 50, NULL);
		hIcon_Confirm = (HICON)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_ICON6), IMAGE_ICON, 100, 100, NULL);

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

		SSCtrl_Title1 = CreateWindowW(L"STATIC", L" Bộ hẹn giờ:",
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 70, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text1 = CreateWindowW(L"STATIC", L"→ Thời gian:",
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 117, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_1 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);

		EditCtrl_1 = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);
		if (!sType) ShowWindow(EditCtrl_1, SW_HIDE);
		EditCtrl_1e = CreateWindowW(L"EDIT", L"",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 155, 115, 110, 30, hWnd, NULL, NULL, NULL);
		///***

		SSCtrl_Text2 = CreateWindowW(L"STATIC", L"→  Chế độ:",
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 152, 420, 30, hWnd, NULL, NULL, NULL);
		
		CBCtrl_2 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 150, 110, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text3 = CreateWindowW(L"STATIC", L"→   Kiểu:",
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 187, 420, 30, hWnd, NULL, NULL, NULL);

		CBCtrl_3 = CreateWindowW(L"COMBOBOX", L"",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 155, 185, 110, 30, hWnd, NULL, NULL, NULL);

		ButtonCtrl_SetTimer = CreateWindowW(L"BUTTON", L"",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CENTER | BS_ICON, 280, 114, 180, 102, hWnd, (HMENU)BUTTON_CONFIRM, NULL, NULL);
		SendMessageW(ButtonCtrl_SetTimer, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Confirm);
		
		SSCtrl_Title2 = CreateWindowW(L"STATIC", L" Cài đặt:",
			WS_VISIBLE | WS_CHILD | SS_LEFT, 40, 230, 420, 30, hWnd, NULL, NULL, NULL);

		SSCtrl_Text4 = CreateWindowW(L"STATIC", L" Fast Mode:",
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

		SSCtrl_Text5 = CreateWindowW(L"STATIC", L" Extra Mode:",
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

		ButtonCtrl_CancelTimer = CreateWindowW(L"BUTTON", L"Huỷ tất cả lịch tắt máy",
			WS_VISIBLE | WS_CHILD | BS_CENTER, 49, 344, 200, 33, hWnd, (HMENU)BUTTON_CANCEL, NULL, NULL);

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
			{
				WCHAR sdlOptions[2][5] =
				{
					TEXT("Giờ"), TEXT("Phút")
				};
				WCHAR tBuffer[5];
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
			exit(0);
		}
		CloseHandle(hToken);

		return true;
	}
}