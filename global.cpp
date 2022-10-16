#include <iostream>
#include <string>
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
HWND SSCtrl_Github;

// HICON & BITMAP MEDIAS:
HICON hIcon_Close, hIcon_Close_H, hIcon_Minimize, hIcon_Minimize_H, hIcon_Confirm;
HICON hIcon_Github, hIcon_Github_H;

// RECTS:
RECT rTitle = { 0, 0, 500, 50 };

// BRUSHES & FONTS:
HBRUSH hBrush_STATIC1, hBrush_STATIC2;
COLORREF CLR_PriDark = RGB(22, 22, 25), CLR_SecDark = RGB(217, 218, 222);
HBRUSH hBrush_PriDark = CreateSolidBrush(RGB(22, 22, 25)), hBrush_SecDark = CreateSolidBrush(RGB(217, 218, 222)), hBrush_BorderGrey = CreateSolidBrush(RGB(112, 112, 112));


/// To be implemented (Change language function)
/*
std::wstring AppTitle = L"Bộ hẹn giờ";
std::wstring MBLimit_1 = L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng";
std::wstring MBLimit_2 = L"Nhập tối thiểu 1 phút hoặc tối đa 1440 phút";
std::wstring MBAlreadyScheduled = L"Máy tính đã có lịch tắt máy\nHuỷ lịch tắt máy hiện tại?\n(Sẽ ghi đè bằng lịch hẹn mới)";
std::wstring MBResult_1 = L"Máy tính sẽ được tắt sau ";
std::wstring MBResult_2 = L" tiếng";
std::wstring MBResult_2a = L" phút";
std::wstring MITitle_1 = L" Bộ hẹn giờ:";
std::wstring MITitle_2 = L" Cài đặt:";
std::wstring MI_1 = L"→ Thời gian:";
std::wstring MI_2 = L"→  Chế độ:";
std::wstring MI_3 = L"→   Kiểu:";
std::wstring MI_4 = L" Fast Mode:";
std::wstring MI_5 = L" Extra Mode:";
std::wstring MI_6 = L"Huỷ tất cả lịch tắt máy";
WCHAR UNIT_1[5] = L"Giờ";
WCHAR UNIT_2[5] = L"Phút";
*/