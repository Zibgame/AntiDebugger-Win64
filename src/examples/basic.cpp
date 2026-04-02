#include <iostream>
#include "antidebug.h"

int main()
{
    antidebug_init();

    if (antidebug_detected())
        antidebug_exit();

    std::cout << "Hello World" << std::endl;

    while (true)
    {
        Sleep(1000);
    }
    return 0;
}