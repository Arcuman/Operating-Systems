// OS07_03A.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>
#include <ctime>

int startTime;

int main()
{
    startTime = clock();
    HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
    if (hm == NULL)
        std::cout << "OS07_03A: Open Error Mutex\n";
    else std::cout << "OS07_03A: Open Mutex\n";
    for (int i = 0; i < 90; i++)
    {
        Sleep(100);
        std::cout << "OS07_03A: " << i << ": Time: " << clock() - startTime << "\n";
        if (i == 29)
            WaitForSingleObject(hm, INFINITE);
        else if (i == 59)
            ReleaseMutex(hm);
    }
    CloseHandle(hm);

    system("pause");
}