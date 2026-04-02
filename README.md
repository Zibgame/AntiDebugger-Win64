# 🛡️ AntiDebugger-Win64

Lightweight and modular C/C++ library for debugger detection on Windows.

---

## 🎯 Overview

AntiDebugger-Win64 is a focused Windows security utility that provides practical, low-level debugger detection mechanisms packaged as a reusable static library.

The project is designed to be:

* 🧩 **Composable**: each detection technique is isolated and extendable
* 🧠 **Low-level oriented**: direct interaction with Windows internals (PEB, TLS, threads)
* ⚙️ **Production-friendly**: minimal overhead, simple API, easy linking

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

### 🧠 Internal (used by runtime / TLS)

```c
void antidebug_set_detected(void);
```

Sets internal detection flag (used by monitoring thread and TLS callback).

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

## 🧠 Detection Strategy

The library implements a layered detection model:

* ⚡ **Static checks (early stage)**

  * Executed via TLS callback before `main()`
  * Detects debuggers attached at process startup

* 🔎 **Synchronous checks (init phase)**

  * PEB inspection (BeingDebugged, NtGlobalFlag)
  * WinAPI checks (`IsDebuggerPresent`)
  * Remote debugger detection

* 🔁 **Asynchronous monitoring (runtime)**

  * Background thread continuously re-checks environment
  * Non-deterministic timing to reduce pattern detection

This approach ensures coverage across:

* 🚀 process startup
* ⏱️ runtime attachment
* 🌐 external debugger interaction

---

## ⚠️ Disclaimer

This project is intended for defensive security, reverse engineering practice, and low-level Windows experimentation.

It does not guarantee resistance against advanced debugging techniques.
