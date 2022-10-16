#pragma once
#include <Windows.h>
#include <Uxtheme.h>
#include <Dwmapi.h>

class ExternSol
{
private:

	bool DEBUG;

public:

	ExternSol(bool DEBUG = 0) : DEBUG(DEBUG)
	{
		if (this->DEBUG)
			MessageBoxW(NULL, L"Initializing constructor", L"cSolution", MB_OK);
	}
	~ExternSol()
	{
		if (this->DEBUG)
			MessageBoxW(NULL, L"Initializing destructor", L"cSolution", MB_OK);
	}

public:

	void FindBorderThickness(HWND hWnd, RECT& rBorder)
	{
		SetRectEmpty(&rBorder);
		if (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_THICKFRAME)
		{
			AdjustWindowRectEx(&rBorder, GetWindowLongPtrW(hWnd, GWL_STYLE) & ~WS_CAPTION, FALSE, NULL);
			rBorder.left *= -1;
			rBorder.top *= -1;
		}
		else if (GetWindowLongPtrW(hWnd, GWL_STYLE) & WS_BORDER)
		{
			SetRect(&rBorder, 1, 1, 1, 1);
		}

		MARGINS margins = { 0 };
		DwmExtendFrameIntoClientArea(hWnd, &margins);
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	}

	BOOL SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
	{
		TOKEN_PRIVILEGES tp;
		LUID luid;

		if (!LookupPrivilegeValueW(NULL, lpszPrivilege, &luid))
		{
			return FALSE;
		}

		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = bEnablePrivilege ? SE_PRIVILEGE_ENABLED : 0;

		if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
		{
			return FALSE;
		}

		if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
		{
			return FALSE;
		}
		return TRUE;
	}
};