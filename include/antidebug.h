#ifndef ANTIDEBUG_H
#define ANTIDEBUG_H

#include <windows.h>
#include <string>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool antidebug_init(void);
bool antidebug_detected(void);
void antidebug_exit(void);
int is_debugger_running(void);
int kill_debugger(void);
int kill_process_by_name(const std::string &target);
int kill_process_by_pid(DWORD pid);

#ifdef __cplusplus
}
#endif

void show_notification(std::string title, std::string info);

#endif