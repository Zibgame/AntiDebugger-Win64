#ifndef ANTIDEBUG_H
#define ANTIDEBUG_H

#include <windows.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool antidebug_init(void);
bool antidebug_detected(void);
void antidebug_exit(void);

#ifdef __cplusplus
}
#endif

#endif