// App1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../synchlib/synchlib.h"

int main()
{
    synchlib::PrintMessage();
    synchlib::synch_CreateSharedMemory();
}

