// OS07_05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime>

int start_time;

int main()
{
    PROCESS_INFORMATION pi1, pi2;
    DWORD pid = GetCurrentProcessId();
    HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"OS07_05_EVENT");
    //LPCWSTR an1 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_05A.exe";
    //LPCWSTR an2 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_05B.exe";
    LPCWSTR an1 = L".\\OS07_05A.exe";
    LPCWSTR an2 = L".\\OS07_05B.exe";
    {
        STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
            std::cout << "Process OS07_05A created \n";
        else  std::cout << "Process OS07_05A not created \n";
    }
    {
        STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
            std::cout << "Process OS07_05B created \n";
        else  std::cout << "Process OS07_05B not created \n";
    }
    start_time = clock();

    for (int i = 0; i < 90; i++) {
        Sleep(100);
        int iter_time = clock();
        std::cout << pid << " : OS07_05: " << i << " time: " << iter_time - start_time << "\n";
        if (i == 14) {
            PulseEvent(he);
        }
    }
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(he);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
    system("pause");
}