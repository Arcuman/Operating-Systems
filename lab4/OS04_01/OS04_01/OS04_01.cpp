// OS04_01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <iostream>

using namespace std;




int main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	unsigned long long d = MAXULONGLONG / 100000000000;

	for (unsigned long long i = 0; i < MAXULONGLONG; i++) {
		if (i % d == 0)
			cout << "PID = " << pid << ", TID = " << tid << " : " << i << endl;
	}
	system("pause");
	return 0;
}