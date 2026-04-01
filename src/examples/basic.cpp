#include <iostream>
#include "antidebug.h"

int main()
{
    //ajout du anti debug quand jaurais fini
    antidebug_init();

    if (antidebug_detected())
        antidebug_exit();

    std::cout << "Hello World" << std::endl;

    return 0;
}