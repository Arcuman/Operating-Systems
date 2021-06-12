
#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

int main()
{
	int startTime = clock();
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem");
	if (hs == NULL)
		cout << "OS07_04B: Open Error Semaphore\n";
	else
		cout << "OS07_04B: Open Semaphore";
	for (int i = 0; i < 90; i++) {
		Sleep(100);
		cout << " OS07_04B " << "pid: " << pid << " i: " << i << " Time " << clock() - startTime << "\n";
		if (i == 29) {
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 59) {
			LONG prevcount = 0;
			ReleaseSemaphore(hs, 1, &prevcount);
		}
	}
	CloseHandle(hs);
	system("pause");
	return 0;
}