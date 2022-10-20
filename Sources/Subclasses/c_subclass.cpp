#include "../Headers/c_resource.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <map>
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
			for (auto& x : HoverMap)
			{
				if ((HWND)x.first == hWnd)
				{
					SendMessageW(x.first, STM_SETIMAGE, IMAGE_ICON, (LPARAM)x.second.second);
					break;
				}
			}

			isHovering = 0;
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			for (auto& x : HoverMap)
			{
				if ((HWND)x.first == hWnd)
				{
					if (!isHovering)
					{
						TRACKMOUSEEVENT tme;
						tme.cbSize = sizeof(TRACKMOUSEEVENT);
						tme.dwFlags = TME_LEAVE;
						tme.hwndTrack = hWnd;
						TrackMouseEvent(&tme);

						SendMessageW(x.first, STM_SETIMAGE, IMAGE_ICON, (LPARAM)x.second.first);
						isHovering = 1;
					}
					break;
				}
			}

			return 0;
		}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}