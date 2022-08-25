#pragma once

#include "resource.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <string>

/*
*   This function execute system command line via CreateProcess()
*/
void ExecCmd(std::string sCmdLine)
{
    /*-------------------------------------------------------------*/
    // Initialize basic parameters for CreateProcess() function
    // Using CreateProcessA() instead because the project using unicode character set
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    // Set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    /*-------------------------------------------------------------*/

    /*-------------------------------------------------------------*/
    // Execute system command via CreateProcess()
    CreateProcessA("C:\\Windows\\System32\\cmd.exe",   // The path
        (LPSTR)sCmdLine.c_str(),    // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW, // "CREATE_NO_WINDOW" flag prevent command prompt from showing up
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    /*-------------------------------------------------------------*/
}

/*
*   This function exec SendMessage() to all HWND handles
*   In this case, the aim is to set the default font for all HWND handles.
*/
bool CALLBACK SetFont(HWND child, LPARAM font) {
    SendMessage(child, WM_SETFONT, font, true);
    return true;
}

/*
*   Alternative of ::MessageBox()
*/
int cMessageBox(std::wstring lpText = L"", bool EnableButtonResponse = 0, std::wstring lpCaption = L"Shutdown Timer v3.0.0")
{
    int msgboxID = MessageBox(
        NULL,
        lpText.c_str(),
        lpCaption.c_str(),
        MB_OK
    );

    if (EnableButtonResponse == 1)
    {
        if (msgboxID == IDYES)
        {
            ::MessageBox(NULL, L"YES BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDNO)
        {
            ::MessageBox(NULL, L"NO BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDOK)
        {
            ::MessageBox(NULL, L"OK BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDABORT)
        {
            ::MessageBox(NULL, L"ABORT BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDCANCEL)
        {
            ::MessageBox(NULL, L"CANCEL BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDCONTINUE)
        {
            ::MessageBox(NULL, L"CONTINUE BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDIGNORE)
        {
            ::MessageBox(NULL, L"IGNORE BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDRETRY)
        {
            ::MessageBox(NULL, L"RETRY BUTTON TRIGGERED", L"", MB_OK);
        }
        else if (msgboxID == IDTRYAGAIN)
        {
            ::MessageBox(NULL, L"RETRY AGAIN BUTTON TRIGGERED", L"", MB_OK);
        }
    }

    return msgboxID;
}


/*
*   These functions handle global pointers used to store temporary content (Transfer contents between windows)
*   cPostGlobal()         | Allocate the pointer
*   ClearGlobalPointers() | Deallocate all global pointers
*/

// Forward declaration global pointers
extern std::wstring* globalwstr_ptr;

void cPostGlobal(std::wstring*& wstr_ptr, std::wstring wstr_content)
{
    wstr_ptr = new std::wstring(wstr_content);
}
void ClearGlobalPointers()
{
    if (globalwstr_ptr != nullptr)
    {
        delete globalwstr_ptr;
        globalwstr_ptr = nullptr;
    }
}