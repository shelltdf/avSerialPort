
#include <iostream>
#include <map>
#include <string>

#include "SerialPort.h"
#include "SerialPortWrapper.h"


std::map<int, avSerialPorts::SerialPort*> gSerialPorts;

void avSerialPortInit()
{
    avSerialPortShutdown();
}

void avSerialPortShutdown()
{
    for (size_t i = 0; i < gSerialPorts.size(); i++)
    {
        if (gSerialPorts[i] != nullptr)
        {
            delete gSerialPorts[i];
        }
    }

    gSerialPorts.clear();
}

int avSerialPortGetNamesCount()
{
    return gSerialPorts.size();
}

int avSerialPortGetNameSize(int id)
{
    if ((gSerialPorts.size() > id) && (gSerialPorts[id] != nullptr))
    {
        //gSerialPorts[i];
    }
    return 0;
}

int avSerialPortGetNameData(int id, char* name)
{
    return 0;
}

bool avSerialPortOpen(int id, const char* name, const char* str)
{
    return false;
}

void avSerialPortClose(int id)
{
}

bool avSerialPortIsOpen(int id)
{
    return false;
}

bool avSerialPortRead(int id)
{
    return false;
}

bool avSerialPortSend(int id)
{
    return false;
}

