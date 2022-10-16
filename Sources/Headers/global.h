#pragma once

/// GLOBAL SCOPE (EXTERNAL)

// PROGRAM PARAMETERS
extern bool sMode;
extern bool sType;
extern bool cFastMode;
extern bool cExtraMode;

// EXTERN OBJECTS
extern ExternSol* eSol;

// HINSTANCES & HWNDS:
extern HINSTANCE hInst;
extern HWND G_hWnd;
extern HWND SSCtrl_Close, SSCtrl_Minimize;
extern HWND SSCtrl_Title1, SSCtrl_Title2;
extern HWND SSCtrl_Text1, CBCtrl_1, EditCtrl_1, EditCtrl_1e, ButtonCtrl_SetTimer, ButtonCtrl_CancelTimer;
extern HWND SSCtrl_Text2, CBCtrl_2;
extern HWND SSCtrl_Text3, CBCtrl_3;
extern HWND SSCtrl_Text4, ButtonCtrl_FMOFF, ButtonCtrl_FMON;
extern HWND SSCtrl_Text5, ButtonCtrl_EMOFF, ButtonCtrl_EMON;
extern HWND SSCtrl_Github;

// HICON & BITMAP MEDIAS:
extern HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H, hIcon_Confirm;
extern HICON hIcon_Github, hIcon_Github_H;

// RECTS:
extern RECT rTitle;

// BRUSHES & FONTS:
extern HBRUSH hBrush_STATIC1, hBrush_STATIC2;
extern COLORREF CLR_PriDark, CLR_SecDark;
extern HBRUSH hBrush_PriDark, hBrush_SecDark, hBrush_BorderGrey;