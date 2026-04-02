#include <windows.h>
#include <stdbool.h>
#include "antidebug.h"

// detect debugger attached from another process
bool check_remote(void)
{
    BOOL remote;

    CheckRemoteDebuggerPresent(GetCurrentProcess(), &remote);
    if (remote)
        return true;

    return false;
}