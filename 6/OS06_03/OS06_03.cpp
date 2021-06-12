#include <iostream>
#include <Windows.h>

using namespace std;
#define PG (4096)
int pg = 256;

int main()
{
	setlocale(LC_ALL, "rus");

	int* m1 = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);
	for (int i = 0; i < pg * PG / 4; i++)
	{
		m1[i] = i;
	}

	// Б = C1
	// О = CE
	// Р = D0
	// Страница C1 = 193, смещение CED = 3309
	int* m2 = m1 + 193 * 1024 + 3309;
	cout << *m2 << endl;
	system("pause");
}
