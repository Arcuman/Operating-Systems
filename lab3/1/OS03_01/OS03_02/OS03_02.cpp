// OS03_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
#include <process.h>
using namespace std;
int main()
{
    // LP — Long Pointer(Длинный указатель)
    // C — Constant(константа)
    // WSTR — Wide character String(строка больших символов)
    LPCWSTR an1 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\lab3\\1\\OS03_01\\Debug\\OS03_02_1.exe";
    LPCWSTR an2 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\lab3\\1\\OS03_01\\Debug\\OS03_02_2.exe";
    // Структура STARTUPINFO используется функцией CreateProcess для определения свойств главного окна,
    // если новое окно создаётся для нового процесса
    STARTUPINFO si1;
    STARTUPINFO si2;
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si1, sizeof(STARTUPINFO)); si1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&si2, sizeof(STARTUPINFO)); si2.cb = sizeof(STARTUPINFO);

    if (
        CreateProcess(an1, NULL,NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)
        )
        cout << "-- Process OS03_02_1 created" << endl;
    else {
        cout << "-- Process OS03_02_1 not created" << endl;
    }
    if (
        CreateProcess(an2, NULL,NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)
        )
        cout << "-- Process OS03_02_2 created" << endl;
    else {
        cout << "-- Process OS03_02_2 not created" << endl;
    }
    for (int i = 0; i < 100; i++) {
        cout << i << "  OS03_02 " << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }

    WaitForSingleObject(
        pi1.hProcess, // идентификатор объекта
        INFINITE      // время ожидания в милисекундах
    );
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
}