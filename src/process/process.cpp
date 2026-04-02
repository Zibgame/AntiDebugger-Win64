#include <antidebug.h>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <tlhelp32.h>
#include <string>

void show_notification(std::string title, std::string info);

typedef struct s_process
{
    std::string name;
    DWORD pid;
} t_process;

std::vector<t_process> get_process_list()
{
    std::vector<t_process> list;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return list;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &pe))
    {
        do
        {
            t_process p;
            p.name = pe.szExeFile;
            p.pid = pe.th32ProcessID;
            list.push_back(p);
        }
        while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);
    return list;
}

int is_process_running(const std::string &target)
{
    std::vector<t_process> list;
    size_t i;

    list = get_process_list();
    i = 0;
    while (i < list.size())
    {
        if (_stricmp(list[i].name.c_str(), target.c_str()) == 0)
            return (1);
        i++;
    }
    return (0);
}

int is_debugger_running(void)
{
    if (is_process_running("x32dbg.exe"))
        return (1);
    if (is_process_running("x64dbg.exe"))
        return (1);
    if (is_process_running("ida32.exe"))
        return (1);
    if (is_process_running("ida64.exe"))
        return (1);
    if (is_process_running("ollydbg.exe"))
        return (1);
    return (0);
}

int kill_debugger(void)
{
    int killed = 0;

    killed |= kill_process_by_name("x64dbg.exe");
    killed |= kill_process_by_name("x32dbg.exe");
    killed |= kill_process_by_name("ida64.exe");
    killed |= kill_process_by_name("ollydbg.exe");
    show_notification("Security Alert", "Unauthorized debugging attempt detected.");

    return (killed);
}

int kill_process_by_pid(DWORD pid)
{
    HANDLE handle;

    handle = OpenProcess(PROCESS_TERMINATE, 0, pid);
    if (!handle)
        return (0);
    if (!TerminateProcess(handle, 1))
    {
        CloseHandle(handle);
        return (0);
    }
    CloseHandle(handle);
    return (1);
}

int kill_process_by_name(const std::string &target)
{
    std::vector<t_process> list;
    size_t i;
    int killed;

    list = get_process_list();
    i = 0;
    killed = 0;
    while (i < list.size())
    {
        if (_stricmp(list[i].name.c_str(), target.c_str()) == 0)
        {
            if (kill_process_by_pid(list[i].pid))
                killed = 1;
        }
        i++;
    }
    return (killed);
}