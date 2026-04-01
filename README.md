# 🛡️ AntiDebugger-Win64

Lightweight C/C++ anti-debugging library for Windows ⚙️

---

## ✨ Features

* 🧠 Basic debugger detection
* ⚡ Minimal overhead
* 🧩 Easy integration
* 🪶 Lightweight design

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/yourname/AntiDebugger-Win64.git
```

---

## 🚀 Usage

Include the header:

```cpp
#include "antidebug.h"
```

Initialize in your program:

```cpp
int main()
{
    ad_init();
    return 0;
}
```

---

## 🧪 Example

```cpp
#include "antidebug.h"

int main()
{
    ad_init();

    if (ad_detected())
    {
        // handle detection
    }

    return 0;
}
```

---

## ⚠️ Disclaimer

This project is for educational and defensive purposes only 📚

It does NOT guarantee protection against reverse engineering ❗

---

## 🧩 Goals

* 🔍 Learn low-level security concepts
* 🛠️ Provide a simple reusable library
* 🚀 Build a clean and minimal tool

---

## 📄 License

MIT License 📜
