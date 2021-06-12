#include <iostream>
#include <ctime>
#include <Windows.h>
#include    <tlhelp32.h>
#include    <stdio.h>

DWORD getppid()
{


    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;
    DWORD ppid = 0, pid = GetCurrentProcessId();

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    __try {
        if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

        ZeroMemory(&pe32, sizeof(pe32));
        pe32.dwSize = sizeof(pe32);
        if (!Process32First(hSnapshot, &pe32)) __leave;

        do {
            if (pe32.th32ProcessID == pid) {
                ppid = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));

    }
    __finally {
        if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
    }
    return ppid;
}

bool flag = true;

DWORD WINAPI ChildThread() {
    DWORD tid = GetCurrentThreadId();

    while(true)
    {
        if (!flag)
            return 0;
        printf("PID = %d, Child Thread: tid - %d: %d  time: %d\n");
    }

    return 0;
}


int main()
{
    clock_t t1 = clock();

    std::cout << getppid() << std::endl;
    DWORD pid = GetCurrentThreadId();
    HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"OS08_02A");
    DWORD ChildId2 = NULL;
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId2);
    WaitForSingleObject(htimer, INFINITE);
    flag = false;
    CloseHandle(hChild2);
    std::cout << "time: " << clock() - t1 << std::endl;
    system("pause");
}

