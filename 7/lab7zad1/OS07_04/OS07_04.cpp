
#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

int main()
{
	int startTime = clock();
	PROCESS_INFORMATION pi1, pi2;
	DWORD pid = GetCurrentProcessId();
	HANDLE hs = CreateSemaphore(NULL, 2,3, L"Sem");
	//LPCWSTR an1 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_04A.exe";
	//LPCWSTR an2 = L"D:\\BSTU\\3 course\\OS\\LabsPractis\\7\\lab7zad1\\Debug\\OS07_04B.exe";
	LPCWSTR an1 = L".\\OS07_04A.exe";
	LPCWSTR an2 = L".\\OS07_04B.exe";
	{
		STARTUPINFO si; 
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1))
			cout << "Process OS07_04A created\n";
		else
			cout << "Process OS07_04A not created\n";
	}
	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2))
			cout << "Process OS07_04B created\n";
		else
			cout << "Process OS07_04B not created\n";
	}

	LONG prevcount = 0;
	for (int i = 0; i < 90; i++) {
		Sleep(100);
		
		cout << " OS07_04 " << "pid: " << pid << " i: " << i << " Time " << clock() - startTime << "\n";
		if (i == 29) {
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 59) {
			ReleaseSemaphore(hs, 1, &prevcount);
		}
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	CloseHandle(hs);
	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	system("pause");
	return 0;
}