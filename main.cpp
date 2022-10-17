/*
 *	Shutdown Timer (WinAPI)
 */

#include "Sources/Headers/func.h"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd)
{
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wc.hInstance = hInstance;
	wc.lpszClassName = L"sdTimerApp1";
	wc.lpfnWndProc = WindowProcedure;

	hInst = hInstance;

	if (!RegisterClassW(&wc))
	{
		MessageBoxW(NULL, L"Error occurred!\n(Init main failed)", L"", MB_OK | MB_ICONERROR);
		return -1;
	}

	cWin32::LoadConfig();
	cWin32::SetLang(cLang, true);

	int cWidth = 0, cHeight = 0;
	cExtra::GetDesktopResolution(cWidth, cHeight);
	G_hWnd = CreateWindowW(
		L"sdTimerApp1", AppTitle.c_str(),
		C_WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_VISIBLE,
		(cWidth / 2) - 251, (cHeight / 2) - 201,
		502, 401+2,
		NULL, NULL, hInstance, NULL);

	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		if (IsDialogMessageW(G_hWnd, &msg) == 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			// cWin32::InitExtra(hWnd, rBorder);
			cWin32::InitMedia();
			cWin32::InitControl(hWnd);
			cWin32::EndCreate(hWnd);

			break;
		}

		case WM_COMMAND:
		{
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
						sType = 0;
					}
					else
					{
						ShowWindow(EditCtrl_1, SW_SHOW);
						ShowWindow(CBCtrl_1, SW_HIDE);
						SetWindowTextW(EditCtrl_1, L"");
						sType = 1;
					}
				}
				else if ((HWND)lp == CBCtrl_2)
				{
					if (iIndex == 0)
					{
						sMode = 0;
					}
					else
					{
						sMode = 1;
					}
				}
			}

			switch (wp)
			{
				case BUTTON_CLOSE:
				{
					DestroyWindow(hWnd);
					break;
				}

				case BUTTON_MINIMIZE:
				{
					ShowWindow(hWnd, SW_SHOWMINIMIZED);
					SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
					break;
				}

				case BUTTON_CONFIRM:
				{
					if (!sType)
					{
						WCHAR tBuffer_1[10];
						memset(&tBuffer_1, 0, sizeof(tBuffer_1));
						if (!cExtraMode)
							GetWindowTextW(CBCtrl_1, tBuffer_1, 10);
						else GetWindowTextW(EditCtrl_1e, tBuffer_1, 10);
						int time = 0;

						if (cExtraMode)
						{
							std::wstring lwstr = tBuffer_1;
							if (lwstr == L"")
								break;

							time = std::stoi(lwstr);
							if (time <= 0 || time > 24)
							{
								SetWindowTextW(EditCtrl_1e, L"");
								if (!cFastMode) MessageBoxW(hWnd, MBLimit_1.c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							SetWindowTextW(EditCtrl_1e, L"");
						}
						else time = std::stoi(tBuffer_1);

						WCHAR tBuffer_2[MAX_COMPUTERNAME_LENGTH + 1];
						memset(tBuffer_2, 0, sizeof(tBuffer_2));
						DWORD machineNameSize = MAX_COMPUTERNAME_LENGTH + 1;
						GetComputerNameW(tBuffer_2, &machineNameSize);
						DWORD dMode = SHUTDOWN_POWEROFF;
						if (sMode == 1)
							dMode = SHUTDOWN_RESTART;

						if (InitiateShutdownW(tBuffer_2, NULL, (time * 3600), dMode, SHTDN_REASON_MINOR_OTHER) == ERROR_SHUTDOWN_IS_SCHEDULED)
						{
							int iMB;
							if (cFastMode)
								iMB = IDYES;
							else iMB = MessageBoxW(hWnd, MBAlreadyScheduled.c_str(), L"", MB_YESNO | MB_ICONINFORMATION);
							if (iMB == IDYES)
							{
								AbortSystemShutdownW(tBuffer_2);
								InitiateShutdownW(tBuffer_2, NULL, (time * 3600), dMode, SHTDN_REASON_MINOR_OTHER);
								if (!cFastMode) MessageBoxW(hWnd, (MBResult_1 + std::to_wstring(time) + MBResult_2).c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							else break;
						}
						if (!cFastMode) MessageBoxW(hWnd, (MBResult_1 + std::to_wstring(time) + MBResult_2).c_str(), L"", MB_OK | MB_ICONINFORMATION);
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
							if (!cFastMode) MessageBoxW(hWnd, MBLimit_2.c_str(), L"", MB_OK | MB_ICONINFORMATION);
							break;
						}
						SetWindowTextW(EditCtrl_1, L"");

						WCHAR tBuffer_2[MAX_COMPUTERNAME_LENGTH + 1];
						memset(tBuffer_2, 0, sizeof(tBuffer_2));
						DWORD machineNameSize = MAX_COMPUTERNAME_LENGTH + 1;
						GetComputerNameW(tBuffer_2, &machineNameSize);
						DWORD dMode = SHUTDOWN_POWEROFF;
						if (sMode == 1)
							dMode = SHUTDOWN_RESTART;

						if (InitiateShutdownW(tBuffer_2, NULL, (time * 60), dMode, SHTDN_REASON_MINOR_OTHER) == ERROR_SHUTDOWN_IS_SCHEDULED)
						{
							int iMB;
							if (cFastMode)
								iMB = IDYES;
							else iMB = MessageBoxW(hWnd, MBAlreadyScheduled.c_str(), L"", MB_YESNO | MB_ICONINFORMATION);
							if (iMB == IDYES)
							{
								AbortSystemShutdownW(tBuffer_2);
								InitiateShutdownW(tBuffer_2, NULL, (time * 60), dMode, SHTDN_REASON_MINOR_OTHER);
								if (!cFastMode) MessageBoxW(hWnd, (MBResult_1 + std::to_wstring(time) + MBResult_2a).c_str(), L"", MB_OK | MB_ICONINFORMATION);
								break;
							}
							else break;
						}
						if (!cFastMode) MessageBoxW(hWnd, (MBResult_1 + std::to_wstring(time) + MBResult_2a).c_str(), L"", MB_OK | MB_ICONINFORMATION);
					}

					break;
				}

				case BUTTON_CANCEL:
				{
					WCHAR tBuffer[MAX_COMPUTERNAME_LENGTH + 1];
					memset(tBuffer, 0, sizeof(tBuffer));
					DWORD machineNameSize = MAX_COMPUTERNAME_LENGTH + 1;
					GetComputerNameW(tBuffer, &machineNameSize);

					AbortSystemShutdownW(tBuffer);
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);

					break;
				}

				case BUTTON_CHANGELANGUAGE:
				{
					if (cLang == L"EN")
					{
						cWin32::UpdateConfig(L"LANGUAGE", L"vi");
						cWin32::SetLang(L"VI");
						SetWindowTextW(ButtonCtrl_ChangeLanguage, L"VI");
						cWin32::RefreshApp();
						cLang = L"VI";
					}
					else if (cLang == L"VI")
					{
						cWin32::UpdateConfig(L"LANGUAGE", L"en");
						cWin32::SetLang(L"EN");
						SetWindowTextW(ButtonCtrl_ChangeLanguage, L"EN");
						cWin32::RefreshApp();
						cLang = L"EN";
					}
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);

					break;
				}

				case BUTTON_FMODEON:
				{
					cWin32::UpdateConfig(L"FASTMODE", L"1");
					cFastMode = 1;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					break;
				}

				case BUTTON_FMODEOFF:
				{
					cWin32::UpdateConfig(L"FASTMODE", L"0");
					cFastMode = 0;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					break;
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

					sType = 0;
					cExtraMode = 1;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					break;
				}

				case BUTTON_EMODEOFF:
				{
					cWin32::UpdateConfig(L"EXTRAMODE", L"0");
					ShowWindow(EditCtrl_1e, SW_HIDE);
					ShowWindow(CBCtrl_1, SW_SHOW);
					SendMessageW(CBCtrl_3, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
					EnableWindow(CBCtrl_3, 1);
					SetWindowTextW(EditCtrl_1e, L"");

					sType = 0;
					cExtraMode = 0;
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					break;
				}

				case BUTTON_GITHUB:
				{
					ShellExecuteW(NULL, L"open", L"https://github.com/0xF5T9/Shutdown-Timer", NULL, NULL, SW_SHOWNORMAL);
					SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github);
					PlaySoundW(MAKEINTRESOURCEW(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
					break;
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

			{	
				RECT l1rc = ps.rcPaint;
				BP_PAINTPARAMS params = { sizeof(params), BPPF_NOCLIP | BPPF_ERASE };
				HDC memdc;
				HPAINTBUFFER hBuffer = BeginBufferedPaint(hdc, &l1rc, BPBF_TOPDOWNDIB, &params, &memdc);
				if (hBuffer)
				{
					BufferedPaintSetAlpha(hBuffer, &l1rc, 255);
					EndBufferedPaint(hBuffer, TRUE);
				}
			}

			FillRect(hdc, &ps.rcPaint, hBrush_SecDark);

			RECT rTitle_Paint = rTitle;
			FillRect(hdc, &rTitle_Paint, hBrush_PriDark);
			RECT rBottom_Paint = { 0, 400+2, 500, 399+2 };
			FillRect(hdc, &rBottom_Paint, hBrush_BorderGrey);

			RECT rDraw1 = { 40, 100, 460, 102 };
			FillRect(hdc, &rDraw1, hBrush_PriDark);
			RECT rDraw2 = { 40, 260, 460, 262 };
			FillRect(hdc, &rDraw2, hBrush_PriDark);

			EndPaint(hWnd, &ps);

			break;
		}

		case WM_CTLCOLORSTATIC:
		{
			if ((HWND)lp == SSCtrl_Close || (HWND)lp == SSCtrl_Minimize)
			{
				SetBkMode((HDC)wp, TRANSPARENT);
				SetTextColor((HDC)wp, RGB(0, 0, 0));
				SetBkColor((HDC)wp, RGB(0, 0, 0));

				hBrush_STATIC1 = hBrush_PriDark;
				return (LRESULT)hBrush_STATIC1;
			}
			else
			{
				SetBkMode((HDC)wp, TRANSPARENT);
				SetTextColor((HDC)wp, CLR_PriDark);
				SetBkColor((HDC)wp, CLR_SecDark);

				hBrush_STATIC1 = hBrush_SecDark;
				return (LRESULT)hBrush_STATIC1;
			}

			break;
		}

		case WM_NCACTIVATE:
		{
			return DefWindowProcW(hWnd, WM_NCACTIVATE, 1, -1);
		}

		case WM_NCCALCSIZE:
		{
			if (lp)
			{
				NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)lp;
				// sz->rgrc[0].left += rBorder.left;
				// sz->rgrc[0].right -= rBorder.right;
				// sz->rgrc[0].bottom -= rBorder.bottom;
				// sz->rgrc[0].top += rBorder.top;
				sz->rgrc[0].top += 1;
				sz->rgrc[0].left += 1;
				sz->rgrc[0].right -= 1;
				sz->rgrc[0].bottom -= 0;
				return 0;
			}

			break;
		}

		case WM_NCHITTEST:
		{
			const LRESULT result = ::DefWindowProcW(hWnd, msg, wp, lp);
			POINT pt;
			pt.x = GET_X_LPARAM(lp);
			pt.y = GET_Y_LPARAM(lp);
			RECT lrc = rTitle;
			MapWindowPoints(hWnd, NULL, reinterpret_cast<POINT*>(&lrc), (sizeof(RECT) / sizeof(POINT)));
			
			if (result == HTLEFT || result == HTRIGHT || result == HTTOP)
				return HTCAPTION;

			if ((result == HTCLIENT) && (PtInRect(&lrc, pt)))
			{
				return HTCAPTION;
			}

			return result;
		}

		case WM_CTLCOLORBTN:
		{
			if (!hBrush_STATIC2)
			{
				hBrush_STATIC2 = CreateSolidBrush(RGB(217, 218, 222));
			}

			return (LRESULT)hBrush_STATIC2;
		}

		/*
		case WM_NOTIFY:
		{
			LPNMHDR header = reinterpret_cast<LPNMHDR>(lp);
			switch (header->code)
			{
				case BCN_HOTITEMCHANGE:
				{
					NMBCHOTITEM* hot_item = reinterpret_cast<NMBCHOTITEM*>(lp);

					if (header->hwndFrom == ButtonCtrl_SetTimer)
					{
						// Handle to the button
						HWND button_handle = header->hwndFrom;

						// ID of the button, if using resources
						UINT_PTR button_id = header->idFrom;

						// Check if the mouse is entering or leaving the hover area
						bool entering = hot_item->dwFlags & HICF_ENTERING;
						if (entering)
						{
							MessageBeep(MB_OK);
						}
						else 
						{
							MessageBeep(MB_OK);
						}
					}

					return 0;
				}
			}
			return 0;
		}
		*/

		/*
		case WM_DRAWITEM:
		{
			DRAWITEMSTRUCT* pdis = (DRAWITEMSTRUCT*)lp; // Extract DRAWITEMSTRUCT pointer from lp
			switch (pdis->CtlID)
			{
				case BUTTON_CONFIRM:
				{
					DrawIconEx()...
					break;
				}
				default:
					break;
			}
			return (TRUE);
		}
		*/

		case WM_KEYDOWN:
		{
			switch (wp)
			{
				case VK_F1:
				{
					// MessageBoxW(NULL, L"Triggered debug WM_KEYDOWN event, exiting the program", L"[DEBUG]", MB_OK);
					DestroyWindow(hWnd);
					break;
				}
			}

			break;
		}

		case WM_CLOSE:
		{
			/*
			short tMB = MessageBoxW(hWnd, L"Are you sure want to quit?", L"", MB_YESNO | MB_ICONEXCLAMATION);
			if (tMB == IDYES)
				DestroyWindow(hWnd);
			else return true;
			*/
			break;
		}

		case WM_DESTROY:
		{
			delete eSol;
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}

LRESULT CALLBACK SSButtonHover(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	static bool isSet = 0;
	switch (uMsg)
	{
		case WM_NCDESTROY:
		{
			RemoveWindowSubclass(hWnd, &SSButtonHover, uIdSubclass);
			break;
		}

		case WM_MOUSEMOVE:
		{
			if (hWnd == SSCtrl_Close)
			{
				if (LOWORD(lParam) >= 15 && LOWORD(lParam) <= 35 && HIWORD(lParam) >= 15 && HIWORD(lParam) <= 35)
				{
					if (!isSet)
					{
						SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close_H);
						isSet = 1;
					}	
				}
				else
				{
					SendMessageW(SSCtrl_Close, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Close);
					isSet = 0;
				}
			}
			else if (hWnd == SSCtrl_Minimize)
			{
				if (LOWORD(lParam) >= 15 && LOWORD(lParam) <= 35 && HIWORD(lParam) >= 15 && HIWORD(lParam) <= 35)
				{
					if (!isSet)
					{
						SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize_H);
						isSet = 1;
					}
				}
				else
				{
					SendMessageW(SSCtrl_Minimize, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Minimize);
					isSet = 0;
				}
			}
			else if (hWnd == SSCtrl_Github)
			{
				if (LOWORD(lParam) >= 20 && LOWORD(lParam) <= 84 && HIWORD(lParam) >= 11 && HIWORD(lParam) <= 33)
				{
					if (!isSet)
					{
						SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github_H);
						isSet = 1;
					}
				}
				else
				{
					if (isSet)
					{
						SendMessageW(SSCtrl_Github, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon_Github);
						isSet = 0;
					}
						
				}
			}
				
			break;
		}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}