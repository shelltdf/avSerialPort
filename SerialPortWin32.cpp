
#ifndef _SerialPortWin32_h_
#define _SerialPortWin32_h_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <Winbase.h>
//#include <iostream>
//#include <tchar.h>
//#include "winnt.h"
//#include <queue>

#include "SerialPort.h"

namespace avSerialPorts
{

    class SerialPortWin32
        :public SerialPort
    {
    public:
        SerialPortWin32(void);
        ~SerialPortWin32(void);

        ///连接端口
        bool connect(const char* comName, const char* com_sting) override;

        virtual void disconnect()
        {
            if (hcom > 0)
            {
                CloseHandle(hcom);
                hcom = 0;
            }
        }

        virtual bool isConnected() { return hcom > 0; }

        int read(char* cr, int len) override;

        bool send(char* cr, int len) override;

        ///设置等待数据的长度
        //void SetWaitLength(unsigned int len = 1);

        //设置接收轮询的休眠时间  毫秒
        //void SetSleepTime(unsigned int ms = 10);

        ////获取缓冲池中所有数据
        ////返回值为数据长度  参数为输出目标
        //unsigned int getPool(std::vector<char> * data);

        ////锁定接收池
        //void lockPool();
        //void unlockPool();

        ////获取接受池对象
        //std::deque<char>* getPool();


    private:

        HANDLE hcom;
        OVERLAPPED over;
        OVERLAPPED Wover;
        DWORD dwEvtMask;

        DWORD dwError;
        DCB dcb;
        COMMPROP prop;
        COMMTIMEOUTS t;


        //轮询的休眠时间
        //unsigned int m_sleeptime;

        ///本地pool
        //std::deque<char> m_pool;

        ///等待数据长度
        unsigned int WaitLength;
    };

    SerialPortWin32::SerialPortWin32(void)
        :hcom(0)
        , WaitLength(1)
        //,receipt(0)
        //,done(true)
        //,m_sleeptime(10) //初始化为10毫秒
    {
        ZeroMemory(&over, sizeof(over));			//必须清零
        ZeroMemory(&Wover, sizeof(Wover));		//必须清零  不然可能导致数据不能正常接受和发送

        over.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        Wover.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    }

    SerialPortWin32::~SerialPortWin32(void)
    {
        disconnect();
    }

    bool SerialPortWin32::connect(const char* comName, const char* com_sting)
    {
        //需要释放的指针
        if (isConnected())
        {
            disconnect();
        }

        hcom = CreateFileA(comName
            , GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
            , NULL/*FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED*/
            , NULL);
        if (hcom == INVALID_HANDLE_VALUE)
        {
            //setDone(true);
            hcom = 0;
            return false;
        }

        SetupComm(hcom, 128, 128);

        GetCommState(hcom, &dcb);
        GetCommProperties(hcom, &prop);
        GetCommTimeouts(hcom, &t);
        BuildCommDCBA(com_sting, &dcb);
        SetCommState(hcom, &dcb);

        t.ReadIntervalTimeout = 1000;
        t.ReadTotalTimeoutConstant = 1000;
        t.ReadTotalTimeoutMultiplier = 1000;
        t.WriteTotalTimeoutConstant = 1000;
        t.WriteTotalTimeoutMultiplier = 1000;
        SetCommTimeouts(hcom, &t);

        SetCommMask(hcom, EV_RXFLAG | EV_RXCHAR);

        return true;
    }

    int SerialPortWin32::read(char* buf, int len)
    {
        //Sleep(m_sleeptime);//休眠40毫秒  //等待确定这里的延误 是否过于长了

        //如果com已经打开
        if (this->hcom <= 0) return 0;

        //DWORD hi = 0;
        unsigned long r_len = 0;
        //char buf[1024];		//接收数据用的临时变量
        //buf[0] = '\0';
        COMSTAT  stat;
        DWORD error;

        BOOL cce = ClearCommError(hcom, &error, &stat);

        // 缓冲区无数据
        if (stat.cbInQue <= 0)
        {
            return 0;
        }

        // 缓冲区有数据
        if (stat.cbInQue > 0)
        {
            EscapeCommFunction(hcom, CLRRTS);

            //2000 下 ReadFile 始终返回 True
            //还有一个问题 就是len小于缓冲区大小也会失败
            if (!ReadFile(hcom, buf, stat.cbInQue, &r_len, &over))
            {
                error = GetLastError();
                if (error == ERROR_IO_PENDING) // 结束异步I/O
                {
                    if (!GetOverlappedResult(hcom, &over, &r_len, false))
                    {
                        if (error != ERROR_IO_INCOMPLETE)//其他错误
                        {
                            r_len = 0;
                        }
                    }
                }
                else if (error == ERROR_NOACCESS)
                {
                    disconnect();
                    r_len = 0;
                }
                else
                {
                    r_len = 0;
                }
            }


            //把接受到的数据放到pool中
            //for (unsigned int bi = 0; bi < r_len && r_len <= 1024; bi++)
            //{
                //m_pool.push_back(buf[bi]);
            //}

            if (ClearCommError(hcom, &error, &stat) && error > 0) //清除错误
            {
                //清除输入缓冲区
                PurgeComm(hcom, PURGE_RXABORT | PURGE_RXCLEAR);

                //this->_mutex.unlock();
                //continue;
            }

            if (stat.cbInQue < WaitLength)
            {
                EscapeCommFunction(hcom, SETRTS);
            }

        }//if (stat.cbInQue > 0)

        return r_len;
    }

    bool SerialPortWin32::send(char* cr, int len)
    {
        DWORD error;

        if (WriteFile(hcom, cr, len, NULL, &Wover) != 0)
        {
            return true;
        }
        else
        {
            error = GetLastError();
            return false;
        }
    }

}//avSerialPorts


#endif // _SerialPortWin32_h_




