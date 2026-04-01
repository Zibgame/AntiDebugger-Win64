#ifndef ANTIDEBUG_H
#define ANTIDEBUG_H

#include <iostream>
#include <windows.h>
#include <debugapi.h>

#ifdef __cplusplus
extern "C" {
#endif

//fonction du projet

bool antidebug_init(void);
bool antidebug_detected(void);
bool check_debugger(void);
void antidebug_exit(void);
void NTAPI tls_callback(void* DllHandle, DWORD Reason, void* Reserved);

DWORD WINAPI monitor_thread(LPVOID arg);

#ifdef __cplusplus
}
#endif

#endif