#pragma once

#include "resource.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <string>
#include <fstream>
#include <Uxtheme.h>

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
int cMessageBox(std::wstring lpText = L"", bool EnableButtonResponse = 0, std::wstring lpCaption = L"Shutdown Timer v3.5.0")
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

/*
*   These functions handle menu items & application setting file
*   LoadConfig()    | Read and load setting file on program start
*   ResetSettings() | Reset setting file to default
*   RefreshMenu()   | Synchronize settings with the interface menu
*   FastModeSwitch  | Update setting file (FastMode)
*/

// Forward declaration program parameters
extern bool cFastMode;

void LoadConfig()
{
    short Attempts = 0;
    bool FirstWarning = 1;
    while (true)
    {
        std::ifstream cFile("settings.cfg");
        if (cFile.is_open()) // Check if the file is exists
        {
            std::string line;
            while (std::getline(cFile, line))
            {
                // line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); | Remove all whitespaces on line
                if (line[0] == '#' || line.empty()) continue; // Ignore lines start with '#' or empty lines

                auto delimiterPos = line.find("=");
                auto name = line.substr(0, delimiterPos);
                auto value = line.substr(delimiterPos + 1);
                if (value[0] == ' ') value = line.substr(delimiterPos + 2);

                // Scan and read data from file
                if (name == "FastMode" || name == "FastMode ") { if (value == "1" || value == "true" || value == "on" || value == "yes") cFastMode = true; else cFastMode = false; }
            }
            cFile.close(); // Close file
            break;
        }
        else {
            if (FirstWarning == 1) { cMessageBox(L"Không tìm thấy tệp cài đặt mặc định, chương trình sẽ tự tạo tệp."); FirstWarning = 0; }
            std::ofstream gFile("settings.cfg");
            gFile << "# Available settings: FastMode\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = 0"; // Write default config file
            gFile.close(); // Close file
            if (Attempts == 3) { cMessageBox(L"[!] Có lỗi xảy ra, chương trình thiếu quyền đọc/ghi từ hệ thống?"); exit(1); }
            Attempts++;
        }
    }
}
void ResetSettings()
{
    short Attempts = 0;
    bool FirstWarning = 1;
    
    while (true)
    {
        std::ofstream gFile("settings.cfg");
        if (gFile.is_open())
        {
            if (FirstWarning == 1) { cMessageBox(L"Tệp cài đặt đã được khôi phục mặc định, hãy khởi động lại chương trình."); FirstWarning = 0; }
            gFile << "# Available settings: FastMode\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = 0"; // Write default config file
            gFile.close(); // Close file
            break;
        }
        else
        {
            if (Attempts == 3) { cMessageBox(L"[!] Có lỗi xảy ra, chương trình thiếu quyền đọc/ghi từ hệ thống?"); exit(1); }
            Attempts++;
        }
    }
    exit(0);
}
void RefreshMenu(HWND hWnd)
{
    HMENU hMenu = GetMenu(hWnd);

    /*-------------------------------------------------------------------------------------------------------------------*/
    // Fast Mode
    {
        if (!cFastMode)
        {

            ModifyMenu(hMenu, IDM_FASTMODE, MF_BYCOMMAND | MF_STRING, IDM_FASTMODE, L"Chế Độ Nhanh: OFF");
        }
        else
        {
            ModifyMenu(hMenu, IDM_FASTMODE, MF_BYCOMMAND | MF_STRING | MF_CHECKED, IDM_FASTMODE, L"Chế Độ Nhanh: ON");
        }
    }
    /*-------------------------------------------------------------------------------------------------------------------*/
}
void FastModeSwitch(bool mode)
{
    short Attempts = 0;
    while (true)
    {
        std::ofstream gFile("settings.cfg");
        if (gFile.is_open()) // Check if the file is exists
        {
            std::string TEMP_FastMode = "";
            if (mode == true) TEMP_FastMode += "1";
            else TEMP_FastMode += "0";

            std::string APPEND = "# Available settings: FastMode\n# Set to \"0\" to disable and \"1\" to enable\n# Example on enabling fast mode feature:\n# FastMode = 1\n\nFastMode = ";
            APPEND += TEMP_FastMode;


            gFile << APPEND;
            gFile.close(); // Close file
            break;
        }
        else
        {
            if (Attempts == 3) { cMessageBox(L"[!] Có lỗi xảy ra, chương trình thiếu quyền đọc/ghi từ hệ thống?"); exit(1); }
            Attempts++;
        }
    }
}