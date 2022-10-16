#include <Windows.h>
#include "Sources/Headers/solution.h"

/// GLOBAL SCOPE

// PROGRAM PARAMETERS
bool sMode = 0;
bool sType = 0;
bool cFastMode = 0;
bool cExtraMode = 0;

// EXTERN OBJECTS:
ExternSol* eSol = new ExternSol();

// HINSTANCES & HWNDS:
HINSTANCE hInst;
HWND G_hWnd;
HWND SSCtrl_Close, SSCtrl_Minimize;
HWND SSCtrl_Title1, SSCtrl_Title2;
HWND SSCtrl_Text1, CBCtrl_1, EditCtrl_1, EditCtrl_1e, ButtonCtrl_SetTimer, ButtonCtrl_CancelTimer;
HWND SSCtrl_Text2, CBCtrl_2;
HWND SSCtrl_Text3, CBCtrl_3;
HWND SSCtrl_Text4, ButtonCtrl_FMOFF, ButtonCtrl_FMON;
HWND SSCtrl_Text5, ButtonCtrl_EMOFF, ButtonCtrl_EMON;

// HICON & BITMAP MEDIAS:
HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H, hIcon_Confirm;

// RECTS:
RECT rTitle = { 0, 0, 500, 50 };

// BRUSHES & FONTS:
HBRUSH hBrush_STATIC1, hBrush_STATIC2;
COLORREF CLR_PriDark = RGB(22, 22, 25), CLR_SecDark = RGB(217, 218, 222);
HBRUSH hBrush_PriDark = CreateSolidBrush(RGB(22, 22, 25)), hBrush_SecDark = CreateSolidBrush(RGB(217, 218, 222)), hBrush_BorderGrey = CreateSolidBrush(RGB(112, 112, 112));