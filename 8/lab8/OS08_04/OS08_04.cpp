#include <iostream>
#include <ctime>
#include <Windows.h>
#define SECOND 10000000

int main()
{
    clock_t t1 = clock();

    DWORD pid = GetCurrentProcessId();
    std::cout << "pid: " << pid << std::endl;
    long long it = -60 * SECOND;
    HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"OS08_02");


    //LPCWSTR an = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\8\\lab8\\Debug\\OS08_04X.exe";
    LPCWSTR an = L".\\OS08_04X.exe";
    PROCESS_INFORMATION pi1, pi2;
    pi1.dwThreadId = 1;
    pi2.dwThreadId = 2;
    if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 60000, NULL, NULL, FALSE)) { throw "Error SrtWaitableTimer"; }
    {
        STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
            std::cout << "Process OS08_04xA created \n";
        else  std::cout << "Process OS08_04xA not created \n";
    }
    {
        STARTUPINFO si; ZeroMemory(&si, sizeof(STARTUPINFO)); si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
            std::cout << "Process OS08_04xB created \n";
        else  std::cout << "Process OS08_04xB not created \n";
    }


    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CancelWaitableTimer(htimer);

    std::cout << "time: " << clock() - t1;
    system("pause");
}