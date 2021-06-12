#include <iostream>
#include <Windows.h>

using namespace std;
int mutex = 1;
void enter_critical_section(void)
{
	asm("spin:  btr  $0, mutex  ");
	asm("jnc  spin");
}
void leave_critical_section(void)
{
	asm("bts  $0, mutex ");
}
DWORD WINAPI my_thread()
{
	int	i, temp;
	for (i = 0; i < 5; i++)
	{
		enter_critical_section();
		cout << i;
		leave_critical_section();
	}
	return 0;
}


int main() {
	DWORD ChildId = NULL;
	DWORD ChildId2 = NULL;

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)my_thread, NULL, 0, &ChildId);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)my_thread, NULL, 0, &ChildId2);

	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);
}