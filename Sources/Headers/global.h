#pragma once

/// GLOBAL SCOPE (EXTERNALS)

// APPLICATION PARAMETERS:
extern int APPLICATION_WIDTH, APPLICATION_HEIGHT;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;
extern bool AP_SHUTDOWN_MODE;
extern bool AP_UNIT;
extern bool AP_FASTMODE;
extern bool AP_EXTRAMODE;
extern std::wstring APP_LANGUAGE;

// EXTERNAL OBJECTS:
extern ExternSol* eSol;

// HINSTANCES & HWNDS:
extern HINSTANCE MAIN_HINSTANCE;
extern HWND MAIN_HWND;
extern HWND SSCtrl_Close, SSCtrl_Minimize, SSCtrl_Github;
extern HWND SSCtrl_Title1, SSCtrl_Title2;
extern HWND SSCtrl_Text1, CBCtrl_1, EditCtrl_1, EditCtrl_1e;
extern HWND SSCtrl_Text2, CBCtrl_2;
extern HWND SSCtrl_Text3, CBCtrl_3;
extern HWND ButtonCtrl_SetTimer, ButtonCtrl_CancelTimer, ButtonCtrl_ChangeLanguage;
extern HWND SSCtrl_Text4, ButtonCtrl_FMOFF, ButtonCtrl_FMON;
extern HWND SSCtrl_Text5, ButtonCtrl_EMOFF, ButtonCtrl_EMON;

// HICON & HBITMAP MEDIAS:
extern HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H;
extern HICON hIcon_Github, hIcon_Github_H;
extern HICON hIcon_Confirm;

// RECTS:
extern RECT RECT_Title;

// BRUSHES & FONTS:
extern HBRUSH hBrush_CTLCOLORSTATIC, hBrush_CTLCOLORBTN;
extern COLORREF CLR_PriDark, CLR_SecDark;
extern HBRUSH hBrush_PriDark, hBrush_SecDark, hBrush_BorderGrey;

// STRINGS:
extern std::wstring STR_AppTitle, STR_MB_Limit1, STR_MB_Limit2, STR_MB_AlreadyScheduled, STR_MB_Result1, STR_MB_Result2, STR_MB_Result2A;
extern std::wstring STR_MI_Title1, STR_MI_Title2, STR_MI_1, STR_MI_2, STR_MI_3, STR_MI_4, STR_MI_5, STR_MI_6, STR_MI_7;

// MAPS:
extern std::map<HWND, std::pair<HICON, HICON>> HoverMap;