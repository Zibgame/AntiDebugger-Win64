#include <windows.h>
#include <shellapi.h>
#include <string>

void show_notification(std::string title, std::string info)
{
    NOTIFYICONDATAA nid;

    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.hWnd = GetConsoleWindow();
    nid.uID = 1;

    nid.uFlags = NIF_INFO | NIF_ICON;
    nid.dwInfoFlags = NIIF_WARNING;

    nid.hIcon = LoadIcon(NULL, IDI_WARNING);

    strncpy(nid.szInfo, info.c_str(), sizeof(nid.szInfo) - 1);
    strncpy(nid.szInfoTitle, title.c_str(), sizeof(nid.szInfoTitle) - 1);

    Shell_NotifyIconA(NIM_ADD, &nid);
    Shell_NotifyIconA(NIM_MODIFY, &nid);

    Sleep(2000);

    Shell_NotifyIconA(NIM_DELETE, &nid);
}