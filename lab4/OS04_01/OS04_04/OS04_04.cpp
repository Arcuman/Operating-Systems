// OS04_04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>

using namespace std;

DWORD pid = NULL;

DWORD WINAPI OS04_02_T1()
{
	DWORD tid = GetCurrentThreadId();
	int d = 50;

	for (int i = 0; i < d; i++)
	{
		Sleep(1000);
		cout << "PID = " << pid << ", Child Thread 1: " << " tid- " << tid << " : " << i << endl;
		if (i == 24) {
			cout << "Sleep Child Thread 1" << endl;
			Sleep(10000);
			cout << "Wake up Child Thread 1" << endl;
		}
	}
	return 0;
}

DWORD WINAPI OS04_02_T2()
{
	DWORD tid = GetCurrentThreadId();
	int d2 = 125;
	for (int i = 0; i < d2; i++)
	{
		Sleep(1000);
		cout << "PID = " << pid << ", Child Thread 2: " << " tid- " << tid << " : " << i << endl;
		if (i == 79) {
			cout << "Sleep Child Thread 2" << endl;
			Sleep(15000);
			cout << "Wake up Child Thread 2" << endl;
		}

	}
	return 0;
}

int main()
{
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	int d = 100;
	DWORD ChildId = NULL;
	DWORD ChildId2 = NULL;

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_02_T1, NULL, 0, &ChildId);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OS04_02_T2, NULL, 0, &ChildId2);

	for (int i = 0; i < d; i++) {
		Sleep(1000);
		cout << "PID = " << pid << ", Parent Thread: " << " tid- " << tid << " : " << i << endl;
		if (i == 29) {
			cout << "Sleep Parent Thread" << endl;
			Sleep(10000);
			cout << "Wake up Parent Thread" << endl;

		}
	}
	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);

	system("pause");
	return 0;

}