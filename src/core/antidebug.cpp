#include "antidebug.h"

bool check_peb_flags(void);
bool check_api(void);
bool check_remote(void);
DWORD WINAPI monitor_thread(LPVOID arg);

static volatile bool g_detected = false;

bool check_debugger(void)
{
    if (check_peb_flags())
        return true;
    if (check_api())
        return true;
    if (check_remote())
        return true;
    return false;
}

bool antidebug_init(void)
{
    HANDLE thread;

    srand(GetTickCount());

    if (check_debugger())
    {
        g_detected = true;
        antidebug_exit();
    }

    thread = CreateThread(NULL, 0, monitor_thread, NULL, 0, NULL);
    if (!thread)
        return false;
    CloseHandle(thread);
    return true;
}

bool antidebug_detected(void)
{
    return g_detected;
}

void antidebug_exit(void)
{
    TerminateProcess(GetCurrentProcess(), 1);
}

void antidebug_set_detected(void)
{
    g_detected = true;
}