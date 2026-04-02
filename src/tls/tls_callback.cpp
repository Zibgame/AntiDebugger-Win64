#include <windows.h>
#include <stdbool.h>
#include "antidebug.h"

bool check_debugger(void);
void antidebug_exit(void);
void antidebug_set_detected(void);
int is_debugger_running(void);
int kill_debugger(void);

// function executed before main()
static void NTAPI tls_callback(void* DllHandle, DWORD Reason, void* Reserved)
{
    (void)DllHandle;
    (void)Reserved;

    if (Reason == DLL_PROCESS_ATTACH)
    {
        if (check_debugger())
        {
            antidebug_set_detected();
            kill_debugger();
            antidebug_exit();
        }
    }
}

// force inclusion of TLS callback in binary
#ifdef _MSC_VER
#pragma const_seg(".CRT$XLB")
EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback = tls_callback;
#pragma const_seg()
#else
PIMAGE_TLS_CALLBACK p_tls_callback __attribute__((section(".CRT$XLB"))) = tls_callback;
#endif