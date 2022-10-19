#include "../Headers/c_resource.h"
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
#include "../Headers/solution.h"
#include "../Headers/global.h"

/// Static Button Hover Event:
LRESULT CALLBACK SSButtonHover(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	static bool isHovering = 0;

	switch (uMsg)
	{
		case WM_NCDESTROY:
		{
			RemoveWindowSubclass(hWnd, &SSButtonHover, uIdSubclass);
			break;
		}

		case WM_MOUSEHOVER:
		{
			return 0;
		}

		case WM_MOUSELEAVE:
		{
			if (isHovering)
			{
				if (hWnd == SSCtrl_Close)
				{
					SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close);
				}
				else if (hWnd == SSCtrl_Minimize)
				{
					SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
				}
				else if (hWnd == SSCtrl_Github)
				{
					SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github);
				}
			}

			isHovering = 0;
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;

			if (hWnd == SSCtrl_Close)
			{
				TrackMouseEvent(&tme);
				if (!isHovering)
				{
					SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close_H);
					isHovering = 1;
				}
			}
			else if (hWnd == SSCtrl_Minimize)
			{
				TrackMouseEvent(&tme);
				if (!isHovering)
				{
					SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize_H);
					isHovering = 1;
				}
			}
			else if (hWnd == SSCtrl_Github)
			{
				TrackMouseEvent(&tme);
				if (!isHovering)
				{
					SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github_H);
					isHovering = 1;
				}
			}

			return 0;
		}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}