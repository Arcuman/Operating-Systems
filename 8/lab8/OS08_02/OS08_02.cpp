#include <iostream>
#include <ctime>

int main()
{
    clock_t t1 = clock();
    int i = 0;
    bool flag1 = true;

    while (true) {
        i++;
        clock_t t2 = clock();
        if (t2 - t1 == 5000 && flag1) {
            std::cout << i << std::endl;
            flag1 = false;
        }
        if (t2 - t1 == 10000 && !flag1) {
            std::cout << i << std::endl;
            flag1 = true;
        }
        if (t2 - t1 == 15000) {
            std::cout << i << std::endl;
            break;
        }
    }
    system("pause");
}
