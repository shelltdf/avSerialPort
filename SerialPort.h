
#ifndef _avSerialPorts_
#define _avSerialPorts_

#include <queue>

namespace avSerialPorts
{
    class SerialPort
    {
    public:

        SerialPort() {}
        virtual ~SerialPort() {}

        static SerialPort* create();

        //win32 comName ="COM1",com_sting = "9600,n,8,1"
        virtual bool connect(const char* comName, const char* com_sting) = 0;

        virtual void disconnect() = 0;

        virtual bool isConnected() = 0;

        virtual int read(char* cr, int len) = 0;

        virtual bool send(char* cr, int len) = 0;

    };


}//avSerialPorts


#endif // _avSerialPorts_


