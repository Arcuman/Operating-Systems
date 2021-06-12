// OS07_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <iostream>
#include <ctime>

int startTime;

int main()
{
    startTime = clock();
    PROCESS_INFORMATION pi1, pi2;
    DWORD pid = GetCurrentProcessId();
    HANDLE hm = CreateMutex(NULL, FALSE, L"Mutex");
    //LPCWSTR an1 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_03A.exe";
    //LPCWSTR an2 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_03B.exe";
    LPCWSTR an1 = L".\\OS07_03A.exe";
    LPCWSTR an2 = L".\\OS07_03B.exe";

    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
            std::cout << "-- Process OS07_03A created\n";
        else std::cout << "-- Process OS07_03A not created\n";
    }
    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
            std::cout << "-- Process OS07_03B created\n";
        else std::cout << "-- Process OS07_03B not created\n";
    }
    for (int i = 0; i < 90; i++)
    {
        Sleep(100);
        std::cout << pid << ": OS07_03: " << i << ": Time: " << clock() - startTime << "\n";
        if (i == 29)
            WaitForSingleObject(hm, INFINITE);
        else if (i == 59)
            ReleaseMutex(hm);
    }

    system("pause");
}