﻿/*
*   Project: Shutdown Timer v3.0.0
*        Win32 UI Introduction
*/

#include ".\Headers\framework.h" // Basic framework dependencies for an Windows Application (Generated by Visual Studio)
#include ".\Headers\func.h"      // My custom header "func.h"

/*---------------------------------------------------------------------------------*/
// #define definitions                                                             //
#define MAX_LOADSTRING 100  // Max chars allowed for: Windows Title & WindowClass  //
/*                                                                                 //
*   Define a custom window style                                                   //
*   This is the same as WS_OVERLAPPEDWINDOW but without the WS_MAXIMIZEBOX         //
*/                                                                                 //
#define WS_OVERLAPPEDWINDOW2 (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX)  //
/*---------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------*/
// Global Variables                                                                       //
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text                     //
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name             //
HINSTANCE hInst;                                // Main Instance                          //
                                                                                          //
// Custom Program Parameters                                                              //
static const unsigned short cMode = 3;                                                    //
                                                                                          //
// Custom HWND Handles                                                                    //
HWND cTextField1;                                                                         //
HWND cButton1;                                                                            //
                                                                                          //
HWND cTextField2;                                                                         //
HWND cButton2;                                                                            //
                                                                                          //
HWND cTextField3;                                                                         //
HWND cButton3;                                                                            //
                                                                                          //
HWND cTextField4_1;                                                                       //
HWND cTextField4_2;                                                                       //
HWND cButton4;                                                                            //
WCHAR cTextField4_saved[3];                                                               //
                                                                                          //
HWND cTextField5;                                                                         //
HWND cButton5;                                                                            //  
                                                                                          //
// Custom brushes & fonts                                                                 //
HBRUSH cBrush_null = CreateSolidBrush(RGB(NULL, NULL, NULL)); // Default null color       //
HBRUSH cBrush_gray = CreateSolidBrush(RGB(240, 240, 240));    // Default gray color       //
HFONT cFont_MSShellDlg = CreateFont(20, 0, 0, 0,              // Main Font                //
    FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,                                       //
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,                                  //
    DEFAULT_PITCH | FF_DONTCARE, TEXT("MS Shell Dlg"));                                   //
HFONT cFont_Consolas = CreateFont(20, 0, 0, 0,                                            //
    FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,                                       //
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,                                  //
    DEFAULT_PITCH | FF_DONTCARE, TEXT("Consolas"));                                       //
/*----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
// Forward declarations of functions included in this code module:      //
ATOM                MyRegisterClass(HINSTANCE hInstance);               //
BOOL                InitInstance(HINSTANCE, int);                       //
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);                //
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);                  //
INT_PTR CALLBACK    Default(HWND, UINT, WPARAM, LPARAM);                //
/*----------------------------------------------------------------------*/


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = cBrush_null; //Original: wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(szWindowClass, L"Shutdown Timer v3.0.0", WS_OVERLAPPEDWINDOW2,
      CW_USEDEFAULT, 0, 315, 250, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
        case WM_CREATE:
        {
            {
                cTextField1 = CreateWindowW(L"STATIC", L"Tắt máy tính sau 1 tiếng",
                    WS_VISIBLE | WS_CHILD,
                    30, 20, 180, 20, hWnd, NULL, NULL, NULL);
                //SendMessage(cTextField1, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cButton1 = CreateWindowW(L"BUTTON", L"Chọn",
                    WS_VISIBLE | WS_CHILD,
                    205, 18, 60, 25, hWnd,
                    (HMENU)1, NULL, NULL);
                //SendMessage(cButton1, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cTextField2 = CreateWindowW(L"STATIC", L"Tắt máy tính sau 2 tiếng",
                    WS_VISIBLE | WS_CHILD,
                    30, 50, 180, 20, hWnd, NULL, NULL, NULL);
                //SendMessage(cTextField2, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cButton2 = CreateWindowW(L"BUTTON", L"Chọn",
                    WS_VISIBLE | WS_CHILD,
                    205, 48, 60, 25, hWnd,
                    (HMENU)2, NULL, NULL);
                //SendMessage(cButton2, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cTextField3 = CreateWindowW(L"STATIC", L"Tắt máy tính sau 4 tiếng",
                    WS_VISIBLE | WS_CHILD,
                    30, 80, 180, 20, hWnd, NULL, NULL, NULL);
                //SendMessage(cTextField3, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cButton3 = CreateWindowW(L"BUTTON", L"Chọn",
                    WS_VISIBLE | WS_CHILD,
                    205, 78, 60, 25, hWnd,
                    (HMENU)3, NULL, NULL);
                //SendMessage(cButton3, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cTextField4_1 = CreateWindowW(L"STATIC", L"Nhập số tiếng",
                    WS_VISIBLE | WS_CHILD,
                    50, 110, 180, 20, hWnd, NULL, NULL, NULL);
                //SendMessage(cTextField4_1, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cTextField4_2 = CreateWindowW(L"EDIT", L"",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    155, 108, 25, 24, hWnd,
                    NULL, NULL, NULL);
                //SendMessage(cTextField4_2, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cButton4 = CreateWindowW(L"BUTTON", L"Chọn",
                    WS_VISIBLE | WS_CHILD,
                    205, 108, 60, 25, hWnd,
                    (HMENU)4, NULL, NULL);
                //SendMessage(cButton4, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cTextField5 = CreateWindowW(L"STATIC", L"Huỷ lịch tắt máy",
                    WS_VISIBLE | WS_CHILD,
                    50, 140, 180, 20, hWnd, NULL, NULL, NULL);
                //SendMessage(cTextField5, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                cButton5 = CreateWindowW(L"BUTTON", L"Chọn",
                    WS_VISIBLE | WS_CHILD,
                    205, 138, 60, 25, hWnd,
                    (HMENU)5, NULL, NULL);
                //SendMessage(cButton5, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);

                EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)cFont_MSShellDlg); // Set default font for the application
                // SendMessage(cButton5, WM_SETFONT, (LPARAM)cFont_Consolas, TRUE); // Set font manually for a handle
            }
            break;
        }

        case WM_ERASEBKGND:
        {
            {
                HDC hdc = (HDC)wParam;

                {
                    RECT MainBackGround = { 0, 0, 299, 191 };
                    FillRect(hdc, &MainBackGround, cBrush_gray);
                }
            }
            break;
        }

        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            {
                switch (wmId)
                {
                    case 1:
                    {
                        {
                            if (cMode == 1)
                            {
                                WinExec("shutdown -a", 0);
                                WinExec("shutdown -s -t 3600", 0);
                            }
                            else if (cMode == 2)
                            {
                                system("shutdown -a");
                                system("shutdown -s -t 3600");
                            }
                            else if (cMode == 3)
                            {
                                ExecCmd("/c shutdown -a");
                                Sleep(10);
                                ExecCmd("/c shutdown -s -t 3600");
                            }
                            ::MessageBox(hWnd, L"Máy tính sẽ được tắt sau 1 tiếng", L"Shutdown Timer v3.0.0", MB_OK);
                        }
                        break;
                    }
                    case 2:
                    {
                        {
                            if (cMode == 1)
                            {
                                WinExec("shutdown -a", 0);
                                WinExec("shutdown -s -t 7200", 0);
                            }
                            else if (cMode == 2)
                            {
                                system("shutdown -a");
                                system("shutdown -s -t 7200");
                            }
                            else if (cMode == 3)
                            {
                                ExecCmd("/c shutdown -a");
                                Sleep(10);
                                ExecCmd("/c shutdown -s -t 7200");
                            }
                            ::MessageBox(hWnd, L"Máy tính sẽ được tắt sau 2 tiếng", L"Shutdown Timer v3.0.0", MB_OK);
                        }
                        break;
                    }
                
                    case 3:
                    {
                        {
                            if (cMode == 1)
                            {
                                WinExec("shutdown -a", 0);
                                WinExec("shutdown -s -t 14400", 0);
                            }
                            else if (cMode == 2)
                            {
                                system("shutdown -a");
                                system("shutdown -s -t 14400");
                            }
                            else if (cMode == 3)
                            {
                                ExecCmd("/c shutdown -a");
                                Sleep(10);
                                ExecCmd("/c shutdown -s -t 14400");
                            }
                            ::MessageBox(hWnd, L"Máy tính sẽ được tắt sau 4 tiếng", L"Shutdown Timer v3.0.0", MB_OK);
                        }
                        break;
                    }
                
                    case 4:
                    {
                        {
                            int t_ret = GetWindowTextW(cTextField4_2, &cTextField4_saved[0], 3);
                            if (t_ret == 0) ::MessageBox(hWnd, L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng", L"", MB_OK);
                            else
                            {
                                std::wstring wstr_1 = cTextField4_saved;
                                int t_int = 0;
                                if (wstr_1[0] > 47 && wstr_1[0] < 58) { t_int = std::stoi(cTextField4_saved); }
                                if (t_int > 0 && t_int < 25)
                                {
                                    std::string sCmdLine = "shutdown -s -t " + std::to_string((t_int * 3600));
                                    if (cMode == 1)
                                    {

                                        WinExec("shutdown -a", 0);
                                        WinExec((LPCSTR)sCmdLine.c_str(), 0);
                                    }
                                    else if (cMode == 2)
                                    {
                                        system("shutdown -a");
                                        system(sCmdLine.c_str());
                                    }
                                    else if (cMode == 3)
                                    {
                                        ExecCmd("/c shutdown -a");
                                        Sleep(10);
                                        sCmdLine = "/c shutdown -s -t " + std::to_string((t_int * 3600));
                                        ExecCmd(sCmdLine);
                                        //ExecCmd("/c shutdown -s -t 14400");
                                    }
                                    std::wstring w_str_2 = L"Máy tính sẽ được tắt sau " + std::to_wstring(t_int) + L" tiếng";
                                    ::MessageBox(hWnd, w_str_2.c_str(), L"Shutdown Timer v3.0.0", MB_OK);
                                }
                                else ::MessageBox(hWnd, L"Nhập tối thiểu 1 tiếng hoặc tối đa 24 tiếng", L"", MB_OK);
                            }
                            DestroyWindow(cTextField4_2);
                            cTextField4_2 = CreateWindowW(L"EDIT", L"",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                155, 108, 25, 24, hWnd,
                                NULL, NULL, NULL);
                            SendMessage(cTextField4_2, WM_SETFONT, (LPARAM)cFont_MSShellDlg, TRUE);
                        }
                        break;
                    }
                
                    case 5:
                    {
                        {
                            if (cMode == 1)
                            {
                                WinExec("shutdown -a", 0);
                            }
                            else if (cMode == 2)
                            {
                                system("shutdown -a");
                            }
                            else if (cMode == 3)
                            {
                                ExecCmd("/c shutdown -a");
                            }
                            ::MessageBox(hWnd, L"Tất cả lịch tắt máy đã được huỷ", L"Shutdown Timer v3.0.0", MB_OK);
                        }
                        break;
                    }
                
                    case IDM_ABOUT:
                    {
                        {
                            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        }
                        break;
                    }
                    
                    case IDM_EXIT:
                    {
                        {
                            DestroyWindow(hWnd);
                        }
                        break;
                    }

                    default:
                    {
                        return DefWindowProc(hWnd, message, wParam, lParam);
                    }
                }
            }
            break;
        }

        case WM_PAINT:
        {
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                // TODO: Add any drawing code that uses hdc here...

                EndPaint(hWnd, &ps);
            }
            break;
        }

        case WM_DESTROY:
        {
            {
                PostQuitMessage(0);
            }
            break;
        }

        case WM_CTLCOLORSTATIC:
        {
            {
                HDC hdcStatic = (HDC)wParam;
                SetTextColor(hdcStatic, RGB(NULL, NULL, NULL)); // text color
                SetBkColor(hdcStatic, RGB(240, 240, 240));  // text background color
                return (LRESULT)GetStockObject(NULL_BRUSH);
            }
            break;
        }

        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Message handler for default box (Testing, unused)
INT_PTR CALLBACK Default(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
