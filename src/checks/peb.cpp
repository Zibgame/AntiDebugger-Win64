#include <windows.h>
#include <stdbool.h>
#include "antidebug.h"

// check debugger using PEB (no API)
bool check_peb_flags(void)
{
    unsigned char* peb;
    DWORD flag;

    peb = (unsigned char*)__readgsqword(0x60); // get PEB address

    if (peb[2]) // BeingDebugged flag
        return true;

    flag = *(DWORD*)(peb + 0x68); // NtGlobalFlag
    if (flag & 0x70)
        return true;

    return false;
}