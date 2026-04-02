#include <windows.h>
#include <stdbool.h>
#include "antidebug.h"

bool check_debugger(void);
void antidebug_exit(void);
void antidebug_set_detected(void);

// thread that continuously checks for debugger
DWORD WINAPI monitor_thread(LPVOID arg)
{
    (void)arg;

    while (1)
    {
        if (check_debugger())
        {
            antidebug_set_detected();
            antidebug_exit();
        }

        Sleep(50 + rand() % 100); // random delay to avoid pattern
    }
    return 0;
}