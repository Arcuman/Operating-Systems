// OS07_05B.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <iostream>
#include <Windows.h>
#include <ctime>

int start_time;

int main()
{
    start_time = clock();
    DWORD pid = GetCurrentProcessId();
    HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"OS07_05_EVENT");
    if (he == NULL) std::cout << "OS07_05_EVENT: Open  Error \n";
    else std::cout << "OS07_05_EVENT: Open \n";

    WaitForSingleObject(he, INFINITE);
    for (int i = 0; i < 90; i++)
    {
        Sleep(100);
        int iter_time = clock();
        std::cout << pid << " : OS07_05B: " << i << " time: " << iter_time - start_time << "\n";
    }

    CloseHandle(he);
    system("pause");
    return 0;
}