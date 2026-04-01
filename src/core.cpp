#include "antidebug.h"

static bool g_detected = false;

// check with all algo if has debuger
bool check_debugger(void)
{
    if (IsDebuggerPresent())
        return true;

    BOOL remote = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &remote);
    if (remote)
        return true;
    return false;
}

DWORD WINAPI monitor_thread(LPVOID arg)
{
    (void)arg;

    while (true)
    {
        if (check_debugger())
        {
            g_detected = true;
            antidebug_exit();
        }
        Sleep(50 + rand() % 100);
    }
    return 0;
}

// launch all algo to detec debugger
bool antidebug_init(void)
{
    HANDLE thread;

    // prev scan
    if (check_debugger())
    {
        g_detected = true;
        antidebug_exit();
    }
    // creat thread loop check debugger
    thread = CreateThread(NULL, 0, monitor_thread, NULL, 0, NULL);
    if (!thread)
        return false;

    CloseHandle(thread);
    return true;
}

// return if antidebugger detected
bool antidebug_detected(void)
{
    return (g_detected);
}

void antidebug_exit(void)
{
    TerminateProcess(GetCurrentProcess(), 1);
}

// a function start berfore main()
void NTAPI tls_callback(void* DllHandle, DWORD Reason, void* Reserved)
{
    (void)DllHandle;
    (void)Reserved;

    if (Reason == DLL_PROCESS_ATTACH)
    {
        if (check_debugger())
        {
            g_detected = true;
            TerminateProcess(GetCurrentProcess(), 1);
        }
    }
}

// This "PAVERRRR" in french juste to include tls_callback
#ifdef _MSC_VER
#pragma const_seg(".CRT$XLB")
EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback = tls_callback;
#pragma const_seg()
#else
PIMAGE_TLS_CALLBACK p_tls_callback __attribute__((section(".CRT$XLB"))) = tls_callback;
#endif