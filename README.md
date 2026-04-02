# 🛡️ AntiDebugger-Win64

A lightweight C/C++ library for detecting debuggers on Windows ⚙️🪟

---

## ✨ Project Goal

This project provides a simple base to learn and experiment with debugger detection techniques on Windows:

* 🧠 Basic debugger detection
* ⚡ Low overhead design
* 🧩 Easy integration into C/C++ projects
* 🔍 Educational purpose (reverse engineering / security learning)

---

## 🧩 Features

✔ Detection via Windows API (`IsDebuggerPresent`)
✔ Detection via PEB (anti-hook technique)
✔ Remote debugger detection
✔ Continuous monitoring thread
✔ TLS callback (early execution before `main()`)

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/yourname/AntiDebugger-Win64.git
cd AntiDebugger-Win64
```

Then add the `.c/.cpp` files to your Visual Studio or MinGW project.

---

## 🚀 Quick Start

### 1️⃣ Include the library

```cpp
#include "antidebug.h"
```

---

### 2️⃣ Initialize the anti-debug system

```cpp
int main()
{
    antidebug_init();

    if (antidebug_detected())
        antidebug_exit();

    std::cout << "Hello World" << std::endl;
    return 0;
}
```

---

## 🧪 API Reference

### 🔧 Initialization

```cpp
bool antidebug_init(void);
```

➡ Starts all checks and launches the monitoring thread

---

### 🔍 Manual check

```cpp
bool antidebug_detected(void);
```

➡ Returns `true` if a debugger was detected

---

### 💀 Exit process

```cpp
void antidebug_exit(void);
```

➡ Immediately terminates the current process

---

## 🧠 Internal Mechanisms

### 🧪 Detection methods

* `IsDebuggerPresent()` (Windows API)
* PEB structure inspection (BeingDebugged + NtGlobalFlag)
* `CheckRemoteDebuggerPresent()`

---

### 🧵 Monitoring thread

A background thread continuously:

* checks debugger signals
* applies random sleep delays to avoid patterns
* terminates process if a debugger is detected

---

### 🧬 TLS Callback

Runs checks **before `main()` execution**:

➡ Allows early termination if a debugger is attached

---

## 📁 Suggested Architecture

```
/antidebug
 ├── antidebug.c / antidebug.cpp
 ├── check_api.c
 ├── check_peb.c
 ├── check_remote.c
 ├── monitor_thread.c
 ├── tls_callback.c
 └── antidebug.h
```

---

## ⚠️ Disclaimer

This project is provided for:

* 📚 educational purposes
* 🔬 security research learning

❗ It does NOT guarantee protection against advanced reverse engineering or debugging techniques.

---

## 🎯 Possible Improvements

* 🧬 Anti-tampering (code checksum validation)
* 🧠 VM detection (VirtualBox / VMware)
* ⏱ Timing-based checks (rdtsc)
* 🔒 Function obfuscation
* 🧪 Software breakpoint detection (0xCC)

---

## 📄 License

MIT License 📜

---

## 🚀 Full Example

```cpp
#include "antidebug.h"
#include <iostream>

int main()
{
    antidebug_init();

    if (antidebug_detected())
    {
        antidebug_exit();
    }

    std::cout << "Application running safely" << std::endl;
    return 0;
}
```

---

🛡️ *Built for learning low-level Windows security concepts*

---

## 📘 How to use `libantidebug.a` in your project

### 📦 1. Project structure example

```
/project
 ├── main.cpp
 ├── include/antidebug.h
 ├── build/libantidebug.a
```

---

### ⚙️ 2. Compilation (MinGW / g++)

Make sure you link the static library:

```bash
g++ main.cpp -Iinclude -Lbuild -lantidebug -o app.exe
```

---

### 🧠 3. Example usage

```cpp
#include "antidebug.h"
#include <iostream>

int main()
{
    if (!antidebug_init())
    {
        std::cout << "Failed to initialize anti-debug system" << std::endl;
        return 1;
    }

    if (antidebug_detected())
    {
        antidebug_exit();
    }

    std::cout << "App running normally" << std::endl;
    return 0;
}
```

---

### 🧩 4. Important notes

* Ensure `libantidebug.a` matches your compiler (MinGW/MSVC mismatch will break linking)
* Include path must contain `antidebug.h`
* Library path must point to `/build`

---

### 🚀 5. Recommended (clean setup)

For larger projects:

```
/project
 ├── external/antidebug/
 │    ├── include/
 │    ├── build/
 ├── src/
 ├── main.cpp
```

Compile:

```bash
g++ main.cpp -Iexternal/antidebug/include -Lexternal/antidebug/build -lantidebug
```

---

### 📊 Integration level

✔ Simple drop-in static library
✔ No runtime dependencies
✔ Cross-project reusable module

---

---

## 🏗️ Build Output

After compilation, the project produces a static library:

```
build/libantidebug.a
```

This library can be linked directly into any C/C++ project:

```bash
-lantidebug
```

or linked manually depending on your toolchain.

Example (MinGW):

```bash
g++ main.cpp -Lbuild -lantidebug
```

---

## 📊 Project Status

This project is under active development 🛠️

### Current state:

* ✔ Core anti-debug engine implemented
* ✔ Monitoring thread system
* ✔ TLS early execution layer
* 🔄 Ongoing improvements and extensions

### Design level:

➡ Modular architecture ready for extension
➡ Suitable for learning, experimentation, and integration into C/C++ projects
➡ Built with performance and simplicity in mind

---

## 🚀 Professional positioning

The goal of this project is to evolve into a **clean, modular and reusable security utility library**:

* clean separation of detection modules
* easy integration into larger software
* predictable and minimal runtime overhead
* maintainable architecture aligned with low-level Windows internals

---
