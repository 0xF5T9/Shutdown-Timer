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

void StartAnimation(HWND hWnd, bool& nState, bool& cState)
{
	nState = !cState;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void Paint_Hover(HWND& hWnd, HWND& cHWND, HDC hdc, bool state)
{
	RECT rc;
	WCHAR TextBuffer[32];
	GetClientRect(hWnd, &rc);
	GetWindowTextW(hWnd, TextBuffer, 32);
	SetTextColor(hdc, CLR_PriDark);
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont_Default = CreateFontW(22, 0, 0, 0x1,
		FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Tahoma");
	HBRUSH hBrush_Frame = CreateSolidBrush(RGB(173, 173, 173));
	HBRUSH hBrush_Background = CreateSolidBrush(RGB(225, 225, 225));
	HBRUSH hBrush_Frame_H = CreateSolidBrush(RGB(0, 120, 215));
	HBRUSH hBrush_Background_H = CreateSolidBrush(RGB(229, 241, 251));
	SelectObject(hdc, hFont_Default);

	/*
	if (hWnd == Target_HWND) /// CUSTOM MODIFY BRUSHES
	{
		if (hBrush_Frame_H) DeleteObject(hBrush_Frame_H);
		if (hBrush_Background_H) DeleteObject(hBrush_Background_H);
		hBrush_Frame_H = CreateSolidBrush(RGB(215, 0, 162));
		hBrush_Background_H = CreateSolidBrush(RGB(251, 230, 245));
	}
	*/

	if (state)
	{
		FillRect(hdc, &rc, hBrush_Background);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame);
	}
	else if (!state && hWnd == cHWND)
	{
		FillRect(hdc, &rc, hBrush_Background_H);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame_H);
	}
	else
	{
		FillRect(hdc, &rc, hBrush_Background);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame);
	}

	DeleteObject(hFont_Default);
	DeleteObject(hBrush_Frame);
	DeleteObject(hBrush_Frame_H);
	DeleteObject(hBrush_Background);
	DeleteObject(hBrush_Background_H);
}

void Paint_LBDown(HWND& hWnd, HWND& cHWND, HDC hdc, bool state)
{
	RECT rc;
	WCHAR TextBuffer[32];
	GetClientRect(hWnd, &rc);
	GetWindowTextW(hWnd, TextBuffer, 32);
	SetTextColor(hdc, CLR_PriDark);
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont_Default = CreateFontW(22, 0, 0, 0x1,
		FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Tahoma");
	HBRUSH hBrush_Frame = CreateSolidBrush(RGB(173, 173, 173));
	HBRUSH hBrush_Background = CreateSolidBrush(RGB(225, 225, 225));
	HBRUSH hBrush_Frame_H = CreateSolidBrush(RGB(0, 120, 215));
	HBRUSH hBrush_Frame_D = CreateSolidBrush(RGB(0, 84, 153));
	HBRUSH hBrush_Background_H = CreateSolidBrush(RGB(229, 241, 251));
	HBRUSH hBrush_Background_D = CreateSolidBrush(RGB(204, 228, 247));
	SelectObject(hdc, hFont_Default);

	/*
	if (hWnd == Target_HWND) /// CUSTOM MODIFY BRUSHES
	{
		if (hBrush_Frame_H) DeleteObject(hBrush_Frame_H);
		if (hBrush_Frame_D) DeleteObject(hBrush_Frame_D);
		if (hBrush_Background_H) DeleteObject(hBrush_Background_H);
		if (hBrush_Background_D) DeleteObject(hBrush_Background_D);
		hBrush_Frame_H = CreateSolidBrush(RGB(215, 0, 162));
		hBrush_Frame_D = CreateSolidBrush(RGB(153, 0, 111));
		hBrush_Background_H = CreateSolidBrush(RGB(251, 230, 245));
		hBrush_Background_D = CreateSolidBrush(RGB(247, 204, 235));
	}
	*/

	if (state)
	{
		FillRect(hdc, &rc, hBrush_Background_H);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame_H);
	}
	else if (!state && hWnd == cHWND)
	{
		FillRect(hdc, &rc, hBrush_Background_D);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame_D);
	}
	else
	{
		FillRect(hdc, &rc, hBrush_Background);
		DrawTextW(hdc, TextBuffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FrameRect(hdc, &rc, hBrush_Frame);
	}

	DeleteObject(hFont_Default);
	DeleteObject(hBrush_Frame);
	DeleteObject(hBrush_Frame_H);
	DeleteObject(hBrush_Frame_D);
	DeleteObject(hBrush_Background);
	DeleteObject(hBrush_Background_H);
	DeleteObject(hBrush_Background_D);
}

void OnPaint_Hover(HWND hWnd, HWND& cHWND, bool& nState_H, bool& cState_H)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	if (hdc)
	{
		if (!BufferedPaintRenderAnimation(hWnd, hdc))
		{
			BP_ANIMATIONPARAMS animParams;
			ZeroMemory(&animParams, sizeof(animParams));
			animParams.cbSize = sizeof(BP_ANIMATIONPARAMS);
			animParams.style = BPAS_LINEAR;

			animParams.dwDuration = (cState_H != nState_H ? 300 : 0);

			RECT rc;
			GetClientRect(hWnd, &rc);

			HDC hdcFrom, hdcTo;
			HANIMATIONBUFFER hbpAnimation = BeginBufferedAnimation(hWnd, hdc, &rc,
				BPBF_COMPATIBLEBITMAP, NULL, &animParams, &hdcFrom, &hdcTo);

			if (hbpAnimation)
			{
				if (hdcFrom)
				{
					Paint_Hover(hWnd, cHWND, hdcFrom, cState_H);
				}
				if (hdcTo)
				{
					Paint_Hover(hWnd, cHWND, hdcTo, nState_H);
				}

				cState_H = nState_H;
				EndBufferedAnimation(hbpAnimation, TRUE);
			}
			else
			{
				Paint_Hover(hWnd, cHWND, hdc, cState_H);
			}
		}

		EndPaint(hWnd, &ps);
	}
}

void OnPaint_LBDown(HWND hWnd, HWND& cHWND, bool& nState_LB, bool& cState_LB)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	if (hdc)
	{
		if (!BufferedPaintRenderAnimation(hWnd, hdc))
		{
			BP_ANIMATIONPARAMS animParams;
			ZeroMemory(&animParams, sizeof(animParams));
			animParams.cbSize = sizeof(BP_ANIMATIONPARAMS);
			animParams.style = BPAS_LINEAR;

			animParams.dwDuration = (cState_LB != nState_LB ? 150 : 0);

			RECT rc;
			GetClientRect(hWnd, &rc);

			HDC hdcFrom, hdcTo;
			HANIMATIONBUFFER hbpAnimation = BeginBufferedAnimation(hWnd, hdc, &rc,
				BPBF_COMPATIBLEBITMAP, NULL, &animParams, &hdcFrom, &hdcTo);

			if (hbpAnimation)
			{
				if (hdcFrom)
				{
					Paint_LBDown(hWnd, cHWND, hdcFrom, cState_LB);
				}
				if (hdcTo)
				{
					Paint_LBDown(hWnd, cHWND, hdcTo, nState_LB);
				}

				cState_LB = nState_LB;
				EndBufferedAnimation(hbpAnimation, TRUE);
			}
			else
			{
				Paint_Hover(hWnd, cHWND, hdc, cState_LB);
			}
		}

		EndPaint(hWnd, &ps);
	}
}

LRESULT CALLBACK ButtonHover_OD(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	static bool cState_H = 1;
	static bool nState_H = 1;
	static bool cState_LB = 1;
	static bool nState_LB = 1;
	static bool isHovering = 0;
	static bool isButtonDown = 0;
	static HWND cHWND;

	switch (uMsg)
	{
	case WM_NCDESTROY:
	{
		RemoveWindowSubclass(hWnd, &ButtonHover_OD, uIdSubclass);
		break;
	}

	case WM_PAINT:
	{
		if (!isButtonDown)OnPaint_Hover(hWnd, cHWND, nState_H, cState_H);
		if (isButtonDown) OnPaint_LBDown(hWnd, cHWND, nState_LB, cState_LB);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		nState_LB = 1;
		cState_LB = 1;
		isButtonDown = 1;
		StartAnimation(hWnd, nState_LB, cState_LB);

		SendMessageW(MAIN_HWND, WM_COMMAND, (WPARAM)GetDlgCtrlID(hWnd), NULL);
		return 0;
	}

	case WM_LBUTTONUP:
	{
		if (isButtonDown)
		{
			cState_LB = 0;
			nState_LB = 1;
			cState_H = 0;
			nState_H = 1;
			BufferedPaintStopAllAnimations(hWnd);
			StartAnimation(hWnd, nState_LB, cState_LB);
		}


		return 0;
	}

	case WM_MOUSEHOVER:
	{
		return 0;
	}

	case WM_MOUSELEAVE:
	{
		isButtonDown = 0;
		isHovering = 0;
		StartAnimation(hWnd, nState_H, cState_H);

		return 0;
	}

	case WM_MOUSEMOVE:
	{
		if (!isHovering)
		{
			cHWND = hWnd;
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);
			StartAnimation(hWnd, nState_H, cState_H);
			isHovering = 1;
		}

		return 0;
	}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}