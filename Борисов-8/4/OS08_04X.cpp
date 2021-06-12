#include <iostream>
#include <ctime>
#include <Windows.h>
#include <tlhelp32.h>
#include <stdio.h>

DWORD getppid()
{
	HANDLE hSnapshot;
	PROCESSENTRY32 pe32;
	DWORD ppid = 0, pid = GetCurrentProcessId();

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	__try {
		if (hSnapshot == INVALID_HANDLE_VALUE) __leave;

		ZeroMemory(&pe32, sizeof(pe32));
		pe32.dwSize = sizeof(pe32);
		if (!Process32First(hSnapshot, &pe32)) __leave;

		do {
			if (pe32.th32ProcessID == pid) {
				ppid = pe32.th32ParentProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe32));

	}
	__finally {
		if (hSnapshot != INVALID_HANDLE_VALUE) CloseHandle(hSnapshot);
	}
	return ppid;
}

bool flag = true;

int simple(int n) {
	for (int i = 2; i <= n / 2; i++) if ((n % i) == 0) return 0;
	return 1;
}

DWORD ChildThread() {
	DWORD tid = GetCurrentThreadId();


	for (long long i = 2; i < 10000000000000000000; i++) {
		if (!flag) {
			break;
		}
		if (simple(i))
			printf("%d \n", i);
	}

	return 0;
}


int main()
{
	clock_t t1 = clock();
	std::cout << "ppid: " << getppid() << std::endl;
	DWORD pid = GetCurrentThreadId();
	HANDLE htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"OS08_02");
	DWORD ChildId2 = NULL;
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId2);
	WaitForSingleObject(htimer, INFINITE);
	flag = false;
	CloseHandle(hChild2);
	std::cout << "time: " << clock() - t1 << std::endl;
	std::cout << "ppid: " << getppid() << std::endl;
	system("pause");
}