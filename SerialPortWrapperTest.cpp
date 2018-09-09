#include <iostream>

#include "SerialPortWrapper.h"

int main()
{
    avSerialPortInit();

    bool b = avSerialPortOpen("COM6", "9600,n,8,1");

    while (true)
    {
        if (!avSerialPortIsOpen("COM6"))
        {
            b = avSerialPortOpen("COM6", "9600,n,8,1");
        }

        if (b)
        {
            char buffer[1024];
            bool br = avSerialPortRead("COM6", buffer, 1024);
            if (br)
            {
                printf("%s\n", &buffer[0]);
            }
        }
    }

    avSerialPortShutdown();

    return 0;
}
