# 🛡️ AntiDebugger-Win64

Lightweight and modular C/C++ library for debugger detection **and active response** on Windows.

---

## 🎯 Overview

AntiDebugger-Win64 is a focused Windows security utility that provides practical, low-level debugger detection mechanisms packaged as a reusable static library.

The project is designed to be:

* 🧩 **Composable**: each detection technique is isolated and extendable
* 🧠 **Low-level oriented**: direct interaction with Windows internals (PEB, TLS, threads)
* ⚙️ **Production-friendly**: minimal overhead, simple API, easy linking
* ⚔️ **Active defense capable**: can react by killing debuggers and notifying the user

Typical use cases:

* 🔒 Protecting sensitive code paths
* 🛠️ Hardening binaries against casual debugging
* 📚 Learning Windows internals and reverse engineering techniques

---

## 🚀 Integration (Recommended)

### 📦 Minimal structure

```
/project
 ├── main.cpp
 ├── include/antidebug.h
 ├── build/libantidebug.a
```

---

### ⚙️ Compilation

```
g++ main.cpp -Iinclude -Lbuild -lantidebug -o app.exe
```

---

### 🧪 Usage

```cpp
#include "antidebug.h"
#include <iostream>

int main()
{
    if (!antidebug_init())
        return 1;

    if (antidebug_detected())
        antidebug_exit();

    std::cout << "Application running" << std::endl;
    return 0;
}
```

---

## 🧩 Public API

### 🔧 Initialization

```c
bool antidebug_init(void);
```

Initializes the system:

* runs early detection
* enables required privileges (SeDebugPrivilege)
* starts monitoring thread

---

### 🔍 Detection state

```c
bool antidebug_detected(void);
```

Returns whether a debugger has been detected at runtime.

---

### 💀 Process termination

```c
void antidebug_exit(void);
```

Immediately terminates the current process.

---

### ⚔️ Active response

```c
int kill_debugger(void);
```

Attempts to terminate known debugger processes:

* x64dbg
* x32dbg
* IDA (32/64)
* OllyDbg

Requires sufficient privileges to succeed.

---

### 🔫 Low-level helpers

```c
int kill_process_by_name(const std::string &target);
int kill_process_by_pid(DWORD pid);
```

Used internally to terminate processes.

---

### 🔔 Notification

```c
void show_notification(std::string title, std::string info);
```

Displays a Windows notification when a debugger is detected.

⚠️ Note:

* Uses legacy Shell_NotifyIcon API
* Behavior may vary depending on Windows version

---

## 🏗️ Architecture

```
src/
 ├── core/
 │    └── antidebug.cpp
 │
 ├── checks/
 │    ├── api.cpp
 │    ├── peb.cpp
 │    └── remote.cpp
 │
 ├── process/
 │    └── process.cpp
 │
 ├── notification/
 │    └── notification.cpp
 │
 ├── runtime/
 │    └── monitor.cpp
 │
 ├── tls/
 │    └── tls_callback.cpp
 │
 └── examples/
      └── basic.cpp

include/
 └── antidebug.h

build/
 └── libantidebug.a
```

---

## 🧠 Detection & Response Strategy

The library implements a layered **detection + reaction model**:

### ⚡ Early stage (TLS callback)

* Executed before `main()`
* Detects debuggers attached at process startup
* Sets detection flag (no heavy action here)

---

### 🔎 Init phase

* PEB inspection (BeingDebugged, NtGlobalFlag)
* WinAPI checks (`IsDebuggerPresent`)
* Remote debugger detection

---

### 🔁 Runtime monitoring

* Background thread continuously checks environment
* Non-deterministic timing

---

### ⚔️ Active response (NEW)

When a debugger is detected:

1. Detection flag is set
2. Privileges are elevated (SeDebugPrivilege)
3. Known debugger processes are terminated
4. Notification is displayed
5. Application can terminate itself

---

## ⚠️ Limitations

* Requires sufficient privileges to kill external processes
* Some debuggers may resist termination
* Windows notification system is not fully reliable
* Not resistant to advanced anti-anti-debug techniques

---

## ⚠️ Disclaimer

This project is intended for:

* defensive security
* reverse engineering practice
* low-level Windows experimentation

It does **not guarantee protection** against advanced analysis tools or skilled reverse engineers.
