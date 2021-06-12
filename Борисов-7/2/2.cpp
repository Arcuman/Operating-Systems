// OS07_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime>

DWORD pid = NULL;
DWORD WINAPI ChildThread();
DWORD WINAPI ChildThread2();

CRITICAL_SECTION cs;
int start_time;

int main()
{
    start_time = clock();
    pid = GetCurrentProcessId();

    DWORD tid = GetCurrentThreadId();
    DWORD ChildId = NULL;
    DWORD ChildId2 = NULL;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread2, NULL, 0, &ChildId2);

    InitializeCriticalSection(&cs);
    for (int i = 0; i < 90; i++)
    {

        if (i == 29) {
            EnterCriticalSection(&cs);
        }
        int iter_time = clock();
        printf("PID = %d, Child Thread: tid - %d: %d  time: %d\n", pid, tid, i, iter_time - start_time);
        Sleep(100);
        if (i == 59) {
            LeaveCriticalSection(&cs);
        }
    }
    WaitForSingleObject(hChild, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);

    DeleteCriticalSection(&cs);
}

DWORD WINAPI ChildThread() {
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 90; i++)
    {
        if (i == 29) {
            EnterCriticalSection(&cs);
        }
        int iter_time = clock();
        printf("PID = %d, Child Thread A: tid - %d: %d  time: %d\n", pid, tid, i, iter_time - start_time);
        Sleep(100);
        if (i == 59) {
            LeaveCriticalSection(&cs);
        }
    }

    return 0;
}

DWORD WINAPI ChildThread2() {
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 90; i++)
    {
        if (i == 29) {
            EnterCriticalSection(&cs);
        }
        int iter_time = clock();
        printf("PID = %d, Child Thread B: tid - %d: %d  time: %d\n", pid, tid, i, iter_time - start_time);
        Sleep(100);
        if (i == 59) {
            LeaveCriticalSection(&cs);
        }
    }

    return 0;
}