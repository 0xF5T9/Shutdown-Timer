/*
 *	Shutdown Timer (WinAPI)
 */

#include "Sources/Headers/func.h"

/// WinAPI Entry:
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// Create and register main window class:
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = NULL; // Set window class background to NULL, handling "WM_ERASEBKGND" manually (Reduce flickering)
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hInstance = hInstance;
	wc.lpszClassName = L"sdTimerApp1";
	wc.lpfnWndProc = WindowProcedure;

	MAIN_HINSTANCE = hInstance;	// Load instance to global scope

	if (!RegisterClassW(&wc))
	{
		MessageBoxW(NULL, L"Error occurred!\n(Init main failed)", L"", MB_OK | MB_ICONERROR);
		return -1;
	}

	// Create main window:
	cWin32::LoadConfig();						// Load application parameters from config file
	cWin32::SetLanguage(APP_LANGUAGE, true);	// Set application language (init mode)

	cExtra::GetDesktopResolution(SCREEN_WIDTH, SCREEN_HEIGHT);	// Get OS Screen resolution (To calculate and make the app appear in the center of the screen)
	MAIN_HWND = CreateWindowExW(WS_EX_LAYERED,
		L"sdTimerApp1", STR_AppTitle.c_str(),
		WS_POPUP |			// Popup window style, remove standard title bar
		WS_THICKFRAME |		// For window drop-shadow effects
		WS_CAPTION |		// Enable some aero animation/transition
		WS_MINIMIZEBOX |	// Enable minimize aero animation/transition
		WS_VISIBLE |		// Make the window visible
		WS_CLIPCHILDREN,	// Excludes the area occupied by child windows when drawing occurs within the parent window (Reduce flickering)
		(SCREEN_WIDTH / 2) - (APPLICATION_WIDTH/2), (SCREEN_HEIGHT / 2) - (APPLICATION_HEIGHT/2),
		APPLICATION_WIDTH, APPLICATION_HEIGHT,
		NULL, NULL, hInstance, NULL);
	SetLayeredWindowAttributes(MAIN_HWND, CLR_RareColor, NULL, LWA_COLORKEY); // WS_EX_LAYERED + LWA_COLORKEY remove the white frame that appear after call DwmExtendFrameIntoClientArea() [func.h | 518 ]

	// Message loop:
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		if (IsDialogMessageW(MAIN_HWND, &msg) == 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	return 0;
}

/// Main Window Procedure:
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			cWin32::InitExtraBegin(1);
			cWin32::InitMedia();
			cWin32::InitControl(hWnd);
			cWin32::InitExtraEnd(hWnd);

			return (LRESULT)0;
		}

		case WM_COMMAND:
		{
			// Combobox Messages:
			if (HIWORD(wp) == CBN_SELCHANGE)
			{
				int iIndex = (int)SendMessageW((HWND)lp, CB_GETCURSEL, NULL, NULL);

				if ((HWND)lp == CBCtrl_3)
				{
					if (iIndex == 0)
					{
						ShowWindow(EditCtrl_1, SW_HIDE);
						ShowWindow(CBCtrl_1, SW_SHOW);
						SetWindowTextW(EditCtrl_1, L"");
						AP_UNIT = 0;
					}
					else
					{
						ShowWindow(EditCtrl_1, SW_SHOW);
						ShowWindow(CBCtrl_1, SW_HIDE);
						SetWindowTextW(EditCtrl_1, L"");
						AP_UNIT = 1;
					}
				}
				else if ((HWND)lp == CBCtrl_2)
				{
					if (iIndex == 0)
					{
						AP_SHUTDOWN_MODE = 0;
					}
					else
					{
						AP_SHUTDOWN_MODE = 1;
					}
				}
			}

			// Other Messages:
			switch (wp)
			{
				case BUTTON_CLOSE:
				{
					cWin32::OnExitApp(hWnd);
					DestroyWindow(hWnd);
					return (LRESULT)0;
				}

				case BUTTON_MINIMIZE:
				{
					ShowWindow(hWnd, SW_SHOWMINIMIZED);
					SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
					return (LRESULT)0;
				}

				case BUTTON_CONFIRM:
				{
					if (!AP_UNIT)
					{
						WCHAR tBuffer_1[10];
						memset(&tBuffer_1, 0, sizeof(tBuffer_1));
						if (!AP_EXTRAMODE)
							GetWindowTextW(CBCtrl_1, tBuffer_1, 10);
						else GetWindowTextW(EditCtrl_1e, tBuffer_1, 10);
						int time = 0;

						if (AP_EXTRAMODE)
						{
							std::wstring lwstr = tBuffer_1;
							if (lwstr == L"")
								break;

							time = std::stoi(lwstr);
							if (time <= 0 || time > 24)
							{
								SetWindowTextW(EditCtrl_1e, L"");
								if (!AP_FASTMODE) MessageBoxW(hWnd, STR_MB_Limit1.c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							SetWindowTextW(EditCtrl_1e, L"");
						}
						else time = std::stoi(tBuffer_1);

						std::wstring machineName = cExtra::GetMachineName();
						DWORD dMode = SHUTDOWN_POWEROFF;
						if (AP_SHUTDOWN_MODE == 1)
							dMode = SHUTDOWN_RESTART;

						if (InitiateShutdownW((LPWSTR)machineName.c_str(), NULL, (time * 3600), dMode, SHTDN_REASON_MINOR_OTHER) == ERROR_SHUTDOWN_IS_SCHEDULED)
						{
							int iMB;
							if (AP_FASTMODE)
								iMB = IDYES;
							else iMB = MessageBoxW(hWnd, STR_MB_AlreadyScheduled.c_str(), L"", MB_YESNO | MB_ICONINFORMATION);
							if (iMB == IDYES)
							{
								AbortSystemShutdownW((LPWSTR)machineName.c_str());
								InitiateShutdownW((LPWSTR)machineName.c_str(), NULL, (time * 3600), dMode, SHTDN_REASON_MINOR_OTHER);
								if (!AP_FASTMODE) MessageBoxW(hWnd, (STR_MB_Result1 + std::to_wstring(time) + STR_MB_Result2).c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							else break;
						}
						if (!AP_FASTMODE) MessageBoxW(hWnd, (STR_MB_Result1 + std::to_wstring(time) + STR_MB_Result2).c_str(), L"", MB_OK | MB_ICONINFORMATION);
					}
					else
					{
						WCHAR tBuffer_1[10];
						memset(&tBuffer_1, 0, sizeof(tBuffer_1));
						GetWindowTextW(EditCtrl_1, tBuffer_1, 10);

						std::wstring lwstr = tBuffer_1;
						if (lwstr == L"")
							break;

						int time = std::stoi(lwstr);
						if (time <= 0 || time > 1440)
						{
							SetWindowTextW(EditCtrl_1, L"");
							if (!AP_FASTMODE) MessageBoxW(hWnd, STR_MB_Limit2.c_str(), L"", MB_OK | MB_ICONINFORMATION);
							break;
						}
						SetWindowTextW(EditCtrl_1, L"");

						std::wstring machineName = cExtra::GetMachineName();
						DWORD dMode = SHUTDOWN_POWEROFF;
						if (AP_SHUTDOWN_MODE == 1)
							dMode = SHUTDOWN_RESTART;

						if (InitiateShutdownW((LPWSTR)machineName.c_str(), NULL, (time * 60), dMode, SHTDN_REASON_MINOR_OTHER) == ERROR_SHUTDOWN_IS_SCHEDULED)
						{
							int iMB;
							if (AP_FASTMODE)
								iMB = IDYES;
							else iMB = MessageBoxW(hWnd, STR_MB_AlreadyScheduled.c_str(), L"", MB_YESNO | MB_ICONINFORMATION);
							if (iMB == IDYES)
							{
								AbortSystemShutdownW((LPWSTR)machineName.c_str());
								InitiateShutdownW((LPWSTR)machineName.c_str(), NULL, (time * 60), dMode, SHTDN_REASON_MINOR_OTHER);
								if (!AP_FASTMODE) MessageBoxW(hWnd, (STR_MB_Result1 + std::to_wstring(time) + STR_MB_Result2A).c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							else break;
						}
						if (!AP_FASTMODE) MessageBoxW(hWnd, (STR_MB_Result1 + std::to_wstring(time) + STR_MB_Result2A).c_str(), L"", MB_OK | MB_ICONINFORMATION);
					}

					return (LRESULT)0;
				}

				case BUTTON_CANCEL:
				{
					std::wstring lwstr = cExtra::GetMachineName();

					AbortSystemShutdownW((LPWSTR)lwstr.c_str());
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);

					return (LRESULT)0;
				}

				case BUTTON_CHANGELANGUAGE:
				{
					if (APP_LANGUAGE == L"EN")
					{
						cWin32::UpdateConfig(L"LANGUAGE", L"vi");
						cWin32::SetLanguage(L"VI");
						SetWindowTextW(ButtonCtrl_ChangeLanguage, L"VI");
						cWin32::RefreshApp();
						APP_LANGUAGE = L"VI";
					}
					else if (APP_LANGUAGE == L"VI")
					{
						cWin32::UpdateConfig(L"LANGUAGE", L"en");
						cWin32::SetLanguage(L"EN");
						SetWindowTextW(ButtonCtrl_ChangeLanguage, L"EN");
						cWin32::RefreshApp();
						APP_LANGUAGE = L"EN";
					}
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);

					return (LRESULT)0;
				}

				case BUTTON_FMODEON:
				{
					cWin32::UpdateConfig(L"FASTMODE", L"1");
					AP_FASTMODE = 1;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					return (LRESULT)0;
				}

				case BUTTON_FMODEOFF:
				{
					cWin32::UpdateConfig(L"FASTMODE", L"0");
					AP_FASTMODE = 0;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					return (LRESULT)0;
				}

				case BUTTON_EMODEON:
				{
					cWin32::UpdateConfig(L"EXTRAMODE", L"1");
					ShowWindow(EditCtrl_1, SW_HIDE);
					ShowWindow(CBCtrl_1, SW_HIDE);
					ShowWindow(EditCtrl_1e, SW_SHOW);
					EnableWindow(CBCtrl_3, 0);
					SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
					SetWindowTextW(EditCtrl_1e, L"");

					AP_UNIT = 0;
					AP_EXTRAMODE = 1;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					return (LRESULT)0;
				}

				case BUTTON_EMODEOFF:
				{
					cWin32::UpdateConfig(L"EXTRAMODE", L"0");
					ShowWindow(EditCtrl_1e, SW_HIDE);
					ShowWindow(CBCtrl_1, SW_SHOW);
					SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
					EnableWindow(CBCtrl_3, 1);
					SetWindowTextW(EditCtrl_1e, L"");

					AP_UNIT = 0;
					AP_EXTRAMODE = 0;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					return (LRESULT)0;
				}

				case BUTTON_GITHUB:
				{
					ShellExecuteW(NULL, L"open", L"https://github.com/0xF5T9/Shutdown-Timer", NULL, NULL, SW_SHOWNORMAL);
					SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github);
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					return (LRESULT)0;
				}

				default:
					break;
			}

			break;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			// Paint background color
			FillRect(hdc, &ps.rcPaint, hBrush_SecDark);

			// Paint title
			RECT rTitle_Paint = RECT_Title;
			FillRect(hdc, &rTitle_Paint, hBrush_PriDark);

			// Paint separator lines
			RECT rDraw1 = { 40, 100, 460, 102 };
			FillRect(hdc, &rDraw1, hBrush_PriDark);
			RECT rDraw2 = { 40, 260, 460, 262 };
			FillRect(hdc, &rDraw2, hBrush_PriDark);

			// Paint window frames
			RECT rFrames;
			GetClientRect(hWnd, &rFrames);
			FrameRect(hdc, &rFrames, hBrush_FrameDark);

			EndPaint(hWnd, &ps);

			return (LRESULT)0;
		}

		case WM_ERASEBKGND:
		{
			// Manually redraw child controls that excluded by main window (Reduce Flickering)
			RedrawWindow(ButtonCtrl_CancelTimer, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return (LRESULT)1;
		}

		case WM_CTLCOLORSTATIC:
		{
			if ((HWND)lp == SSCtrl_Close || (HWND)lp == SSCtrl_Minimize)
			{
				SetBkMode((HDC)wp, TRANSPARENT);
				SetTextColor((HDC)wp, RGB(0, 0, 0));
				SetBkColor((HDC)wp, RGB(0, 0, 0));

				hBrush_CTLCOLORSTATIC = hBrush_PriDark;
				return (LRESULT)hBrush_CTLCOLORSTATIC;
			}
			else
			{
				SetBkMode((HDC)wp, TRANSPARENT);
				SetTextColor((HDC)wp, CLR_PriDark);
				SetBkColor((HDC)wp, CLR_SecDark);

				hBrush_CTLCOLORSTATIC = hBrush_SecDark;
				return (LRESULT)hBrush_CTLCOLORSTATIC;
			}

			break;
		}

		case WM_NCCALCSIZE:
		{
			return (LRESULT)0; // Remove standard window frames
		}

		case WM_NCHITTEST:
		{
			// Default WM_NCHITTEST response
			const LRESULT result = ::DefWindowProcW(hWnd, msg, wp, lp);

			// Get title rectangle region
			RECT lrc = RECT_Title;

			// Get and map window points to track mouse location
			POINT pt;
			pt.x = GET_X_LPARAM(lp);
			pt.y = GET_Y_LPARAM(lp);
			MapWindowPoints(hWnd, NULL, reinterpret_cast<POINT*>(&lrc), (sizeof(RECT) / sizeof(POINT)));
			
			// Disable size borders, the app is not designed for resizing
			if (result == HTLEFT || result == HTRIGHT || result == HTTOP || result == HTBOTTOM)
				return HTCAPTION;

			// Catch title bar events
			if ((result == HTCLIENT) && (PtInRect(&lrc, pt))) 
			{
				return HTCAPTION;
			}

			return result;
		}

		case WM_CTLCOLORBTN:
		{
			if (!hBrush_CTLCOLORBTN)
			{
				hBrush_CTLCOLORBTN = hBrush_SecDark;
			}

			return (LRESULT)hBrush_CTLCOLORBTN;
		}

		case WM_WINDOWPOSCHANGED:
		{
			// Null "invalid" resize events, the app is not designed for resizing
			WINDOWPOS* wndpos = (WINDOWPOS*)lp;
			if (wndpos->cx > APPLICATION_WIDTH || wndpos->cy > APPLICATION_HEIGHT)
			{
				SetWindowPos(hWnd, NULL, (SCREEN_WIDTH / 2) - (APPLICATION_WIDTH / 2), (SCREEN_HEIGHT / 2) - (APPLICATION_HEIGHT / 2), APPLICATION_WIDTH, APPLICATION_HEIGHT, SWP_NOZORDER);
				return (LRESULT)0;
			}
			break;
		}

		case WM_KEYDOWN:
		{
			switch (wp)
			{
				case VK_F1:
				{
					// Debug key
					cWin32::OnExitApp(hWnd);
					DestroyWindow(hWnd);
					return (LRESULT)0;
				}
			}

			break;
		}

		case WM_CLOSE:
		{
			cWin32::OnExitApp(hWnd);
			DestroyWindow(hWnd);
			return (LRESULT)0;
		}

		case WM_DESTROY:
		{
			delete eSol;
			PostQuitMessage(0);
			return (LRESULT)0;
		}

		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}