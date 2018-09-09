#include <iostream>

#include "SerialPortWrapper.h"

int main()
{
    avSerialPortInit();

    bool b = avSerialPortOpen(1, "COM6", "9600,n,8,1");

    while (true)
    {
        if (!avSerialPortIsOpen(1))
        {
            b = avSerialPortOpen(1, "COM6", "9600,n,8,1");
        }

        if (b)
        {
            bool br = avSerialPortRead(1);
            if (br)
            {

            }
        }
    }

    avSerialPortShutdown();

    return 0;
}
