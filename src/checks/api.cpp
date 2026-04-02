#include <windows.h>
#include <stdbool.h>
#include "antidebug.h"

// simple API check (can be hooked)
bool check_api(void)
{
    if (IsDebuggerPresent())
        return true;

    return false;
}