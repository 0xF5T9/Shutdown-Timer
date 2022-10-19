#include <iostream>
#include <string>
#include <Windows.h>
#include "Sources/Headers/solution.h"

/// GLOBAL SCOPE

// PROGRAM PARAMETERS
int APPLICATION_WIDTH = 502, APPLICATION_HEIGHT = 403;
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;
bool sMode = 0;
bool sType = 0;
bool cFastMode = 0;
bool cExtraMode = 0;
std::wstring cLang = L"EN";

// EXTERN OBJECTS:
ExternSol* eSol = new ExternSol();

// HINSTANCES & HWNDS:
HINSTANCE hInst;
HWND G_hWnd;
HWND SSCtrl_Close, SSCtrl_Minimize;
HWND SSCtrl_Title1, SSCtrl_Title2;
HWND SSCtrl_Text1, CBCtrl_1, EditCtrl_1, EditCtrl_1e, ButtonCtrl_SetTimer, ButtonCtrl_CancelTimer, ButtonCtrl_ChangeLanguage;
HWND SSCtrl_Text2, CBCtrl_2;
HWND SSCtrl_Text3, CBCtrl_3;
HWND SSCtrl_Text4, ButtonCtrl_FMOFF, ButtonCtrl_FMON;
HWND SSCtrl_Text5, ButtonCtrl_EMOFF, ButtonCtrl_EMON;
HWND SSCtrl_Github;

// HICON & BITMAP MEDIAS:
HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H, hIcon_Confirm;
HICON hIcon_Github, hIcon_Github_H;

// RECTS:
RECT rTitle = { 0, 0, 500, 37 };

// BRUSHES & FONTS:
HBRUSH hBrush_STATIC1, hBrush_STATIC2;
COLORREF CLR_PriDark = RGB(22, 22, 25), CLR_SecDark = RGB(217, 218, 222);
HBRUSH hBrush_PriDark = CreateSolidBrush(RGB(22, 22, 25)), hBrush_SecDark = CreateSolidBrush(RGB(217, 218, 222)), hBrush_BorderGrey = CreateSolidBrush(RGB(112, 112, 112));


/// To be implemented (Change language function)
std::wstring AppTitle, MBLimit_1, MBLimit_2, MB, MBAlreadyScheduled, MBResult_1, MBResult_2, MBResult_2a, MITitle_1, MITitle_2, MI_1, MI_2, MI_3, MI_4, MI_5, MI_6, MI_7;