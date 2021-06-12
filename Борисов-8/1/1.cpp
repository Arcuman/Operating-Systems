#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    time_t t = time(&t);
    tm ttm;
    localtime_s(&ttm, &t);

    cout << ttm.tm_mday << "."
        << ttm.tm_mon + 1 << "."
        << ttm.tm_year << " "
        << ttm.tm_hour << ":"
        << ttm.tm_min << ":"
        << ttm.tm_sec << endl;

    system("pause");
}