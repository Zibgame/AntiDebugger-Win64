# 🛡️ AntiDebugger-Win64

Une petite librairie C/C++ pour détecter les débogueurs sous Windows ⚙️🪟

---

## ✨ Objectif du projet

Ce projet a pour but de fournir une base simple pour comprendre et expérimenter les techniques de détection de debug sous Windows :

* 🧠 Détection basique de debugger
* ⚡ Faible overhead
* 🧩 Intégration rapide dans un projet C/C++
* 🔍 Approche éducative (reverse engineering / sécurité)

---

## 🧩 Fonctionnalités

✔ Détection via API Windows (`IsDebuggerPresent`)
✔ Détection via PEB (anti-hook simple)
✔ Détection de debugger distant
✔ Thread de surveillance continue
✔ TLS callback (détection avant `main()`)

---

## 📦 Installation

Clone le projet :

```bash
git clone https://github.com/yourname/AntiDebugger-Win64.git
cd AntiDebugger-Win64
```

Ajoute les fichiers `.c/.cpp` à ton projet Visual Studio ou MinGW.

---

## 🚀 Utilisation rapide

### 1️⃣ Inclure la librairie

```cpp
#include "antidebug.h"
```

---

### 2️⃣ Initialiser le système anti-debug

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

## 🧪 API disponible

### 🔧 Initialisation

```cpp
bool antidebug_init(void);
```

➡ Lance les vérifications + démarre le thread de monitoring

---

### 🔍 Vérification manuelle

```cpp
bool antidebug_detected(void);
```

➡ Retourne `true` si un debugger a été détecté

---

### 💀 Quitter proprement

```cpp
void antidebug_exit(void);
```

➡ Termine immédiatement le process

---

## 🧠 Mécanismes internes

### 🧪 Checks utilisés

* `IsDebuggerPresent()` (API Windows)
* Lecture du PEB (BeingDebugged + NtGlobalFlag)
* `CheckRemoteDebuggerPresent()`

---

### 🧵 Thread de surveillance

Un thread tourne en boucle :

* vérifie les signaux de debug
* ajoute un délai aléatoire pour éviter les patterns
* kill le process si nécessaire

---

### 🧬 TLS Callback

Le check est exécuté **avant `main()`** :

➡ Permet de bloquer très tôt l’exécution si debug détecté

---

## 📁 Architecture suggérée

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

Ce projet est fourni à des fins :

* 📚 éducatives
* 🔬 recherche sécurité

❗ Il ne garantit pas une protection complète contre le reverse engineering ou le debugging avancé.

---

## 🎯 Améliorations possibles

* 🧬 Anti-tampering (checksum du code)
* 🧠 Détection VM (VirtualBox / VMware)
* ⏱ Timing checks (rdtsc)
* 🔒 Obfuscation des fonctions critiques
* 🧪 Détection breakpoints logiciels (0xCC)

---

## 📄 Licence

MIT License 📜

---

## 🚀 Exemple complet

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
