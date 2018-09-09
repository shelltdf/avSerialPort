
#include <iostream>
#include <map>
#include <string>

#include "SerialPort.h"
#include "SerialPortWrapper.h"


std::map<std::string, avSerialPorts::SerialPort*> gSerialPorts;

void avSerialPortInit()
{
    avSerialPortShutdown();
}

void avSerialPortShutdown()
{
    for (auto it = gSerialPorts.begin(); it != gSerialPorts.end(); it++)
    {
        if (it->second != nullptr)
        {
            delete it->second;
        }
    }
    gSerialPorts.clear();
}

//std::string avSerialPortGetNames()
int avSerialPortGetNames(char* str, int len)
{
    //return "1234567890";

    //char* c = "1234567890";
    //memcpy(str, c, 10);

    //char* r = new char[11];
    //char* r = (char*)malloc(11);
    //char* r = (char*)malloc(11);
    //memset(r, 0, 11);
    //r[10] = '\0';
    //memcpy(r, c, 10);
    //strcpy(r, c);

    std::string buffer;
    std::vector<std::string> names = avSerialPorts::SerialPort::getNames();
    for (size_t i = 0; i < names.size(); i++)
    {
        //printf("-> %s\n", names[i].c_str());
        buffer += names[i];
        if (i + 1 < names.size())
        {
            buffer += " ";
        }
    }

    if (str && len > names.size())
    {
        memcpy(str, &buffer[0], buffer.size());
        return names.size();
    }

    return 0;
}

#if 0
int avSerialPortGetNamesCount()
{
    return gSerialPorts.size();
}

int avSerialPortGetNameSize(int index)
{
    if ((gSerialPorts.size() > index) && (gSerialPorts[index] != nullptr))
    {
        //gSerialPorts[i];
    }
    return 0;
}

int avSerialPortGetNameData(int index, char* name)
{
    return 0;
}
#endif

bool avSerialPortOpen(const char* name, const char* str)
{
    avSerialPorts::SerialPort* comm = 0;
    auto it = gSerialPorts.find(name);
    if (it != gSerialPorts.end())
    {
        comm = it->second;
    }
    else
    {
        comm = avSerialPorts::SerialPort::create();
        gSerialPorts[name] = comm;
    }

    return comm->connect(name, str);
}

void avSerialPortClose(const char* name)
{
    auto it = gSerialPorts.find(name);
    if (it != gSerialPorts.end())
    {
        it->second->disconnect();
        gSerialPorts.erase(it);
    }
}

bool avSerialPortIsOpen(const char* name)
{
    auto it = gSerialPorts.find(name);
    if (it != gSerialPorts.end())
    {
        return it->second->isConnected();
    }

    return false;
}

bool avSerialPortRead(const char* name, char* str, int len)
{
    //std::string buffer;
    //buffer.resize(len);

    auto it = gSerialPorts.find(name);
    if (it != gSerialPorts.end())
    {
        //char* buffer = new char[len];
        int rs = it->second->read(/*&buffer[0]*/str, len);
        if (rs > 0 && rs < len)
        {
            //memcpy(str, &buffer[0], rs);
            str[rs + 1] = '\0';
            //delete[] buffer; buffer = 0;
            return true;
        }
        //delete[] buffer; buffer = 0;
    }

    return false;
}

bool avSerialPortSend(const char* name, char* str, int len)
{
    auto it = gSerialPorts.find(name);
    if (it != gSerialPorts.end())
    {
        //it->second->send();
        return true;
    }
    return false;
}

