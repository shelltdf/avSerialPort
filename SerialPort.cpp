
#include "SerialPort.h"

#if _WIN32
#include "SerialPortWin32.cpp"
#endif // _WIN32


using namespace avSerialPorts;

SerialPort* SerialPort::create()
{

#if _WIN32
    return new SerialPortWin32();
#endif // _WIN32

    return 0;
}

std::vector<std::string> SerialPort::getNames()
{

#if _WIN32
    return getNamesWin32();
#endif // _WIN32

}