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