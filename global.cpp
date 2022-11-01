#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include "Sources/Headers/solution.h"

/// GLOBAL SCOPE (DEFINITIONS)

// APPLICATION PARAMETERS:
int APPLICATION_WIDTH = 502, APPLICATION_HEIGHT = 403;	// Main window width & height
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;				// OS Screen resolution (Default: 0, 0 - Will be loaded in WinAPI Entry)
bool AP_SHUTDOWN_MODE = 0;								// Shutdown mode: 0 Shutdown || 1 Restart (Default: 0)
bool AP_UNIT = 0;										// Time unit: 0 Hour || 1 Minute (Default: 0)
bool AP_FASTMODE = 0;									// Skip dialogs: 0 OFF || 1 ON (Default: 0)
bool AP_EXTRAMODE = 0;									// Allow to enter specific time as hour unit: 0 OFF || 1 ON (Default: 0)
std::wstring APP_LANGUAGE = L"EN";						// Application language: "EN" || "VI" (Default: "EN")

// EXTERNAL OBJECTS:
ExternSol* eSol = new ExternSol();						// Debug object

// HINSTANCES & HWNDS:
HINSTANCE MAIN_HINSTANCE;
HWND MAIN_HWND;
HWND SSCtrl_Close, SSCtrl_Minimize, SSCtrl_Github;
HWND SSCtrl_Title1, SSCtrl_Title2;
HWND SSCtrl_Text1, CBCtrl_1, EditCtrl_1, EditCtrl_1e;
HWND SSCtrl_Text2, CBCtrl_2;
HWND SSCtrl_Text3, CBCtrl_3;
HWND ButtonCtrl_SetTimer, ButtonCtrl_CancelTimer, ButtonCtrl_ChangeLanguage;
HWND SSCtrl_Text4, ButtonCtrl_FMOFF, ButtonCtrl_FMON;
HWND SSCtrl_Text5, ButtonCtrl_EMOFF, ButtonCtrl_EMON;

// HICON & HBITMAP MEDIAS:
HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H;
HICON hIcon_Github, hIcon_Github_H;
HICON hIcon_Confirm;

// RECTS:
RECT RECT_Title = { 0, 0, 502, 37 };

// BRUSHES & FONTS:
HBRUSH hBrush_CTLCOLORSTATIC, hBrush_CTLCOLORBTN;
COLORREF CLR_PriDark = RGB(22, 22, 25), CLR_SecDark = RGB(217, 218, 222);
COLORREF CLR_RareColor = RGB(141, 172, 160);
HBRUSH hBrush_PriDark = CreateSolidBrush(RGB(22, 22, 25)), hBrush_SecDark = CreateSolidBrush(RGB(217, 218, 222)), hBrush_FrameDark = CreateSolidBrush(RGB(58, 49, 62));

// STRINGS:
std::wstring STR_AppTitle, STR_MB_Limit1, STR_MB_Limit2, STR_MB_AlreadyScheduled, STR_MB_Result1, STR_MB_Result2, STR_MB_Result2A;
std::wstring STR_MI_Title1, STR_MI_Title2, STR_MI_1, STR_MI_2, STR_MI_3, STR_MI_4, STR_MI_5, STR_MI_6, STR_MI_7;

// MAPS:
std::map<HWND, std::pair<HICON, HICON>> HoverMap;