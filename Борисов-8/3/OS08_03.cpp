// OS08_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <Windows.h>
#define SECOND 10000000

int i = 0;
HANDLE htimer = NULL;

int main()
{
    htimer = CreateWaitableTimer(NULL, FALSE, NULL);
    long long it = -3 * SECOND;

    clock_t start_time = clock();
    while (true) {
        i++;
        if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 3000, NULL, NULL, FALSE)) { throw "Error SrtWaitableTimer"; }
        if (i == 6) {
            std::cout << clock() - start_time << " " << i << std::endl;
            break;
        }
        std::cout << clock() - start_time << " " << i << std::endl;
        WaitForSingleObject(htimer, INFINITE);
    }

    system("pause");
}