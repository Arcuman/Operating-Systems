// lab7zad1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;
int mutex = 0;
int startTime;
void enter_critical_section(void)
{
	//JC- Jump if carry (cf=1)	CF=1
	//Команда BTS сохраняет значение бита, из первого операнда со смещением, 
	//указанным вторым операндом, во флаге CF, а затем устанавливает этот бит в 1.
	__asm {
		SpinLoop:
		lock bts mutex, 0;
		jc SpinLoop
	}
}
void leave_critical_section(void)
{
	//Команда BTR сохраняет значение бита, из первого операнда со смещением, 
	//указанным вторым операндом, во флаге CF, а затем обнуляет этот бит.
	__asm lock btr mutex, 0
}
DWORD WINAPI my_thread()
{
	enter_critical_section();
	int	i;
	for (i = 0; i < 20; i++)
	{
		cout << "Thread 1:" << i << " Time: " << clock() - startTime << endl;
	}
	leave_critical_section();
	return 0;
}

DWORD WINAPI my_thread1()
{
	
	enter_critical_section();
	int	i;
	for (i = 0; i < 20; i++)
	{
		cout <<"Thread 2:" << i << " Time: "<< clock() - startTime << endl;
	}
	leave_critical_section();
	return 0;
}


int main() {
	startTime = clock();
	DWORD ChildId = NULL;
	DWORD ChildId2 = NULL;

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)my_thread, NULL, 0, &ChildId);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)my_thread1, NULL, 0, &ChildId2);
	ResumeThread(hChild);
	ResumeThread(hChild2);
	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);
	system("pause");
}