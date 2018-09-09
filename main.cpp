
#include <iostream>
#include "SerialPort.h"

class parser
{
public:
    parser() {}

    //头为0 尾为1024 包内5个int
    std::string HEAD = "0";
    std::string TAIL = "1024";
    int SIZE = 5;

    std::vector<int> push(char* c, int len)
    {

        std::vector<int> ret;

        for (size_t i = 0; i < len; i++)
        {
            //str.push_back(c[i]);
            if (c[i] == '\r')
            {
            }
            else if (c[i] == '\n')
            {
                STRLIST.push_back(STR);
                STR.clear();
            }
            else
            {
                STR.push_back(c[i]);
            }
        }

        int index = 0;
        while ((SIZE + 2 + index) < STRLIST.size())
        {
            if (STRLIST[index] == HEAD && STRLIST[index + 6] == TAIL)
            {
                ret.clear();
                for (size_t j = 0; j < SIZE; j++)
                {
                    ret.push_back(atoi(STRLIST[index + j + 1].c_str()));
                }
                index += (SIZE + 2);
            }
            else
            {
                STRLIST.erase(STRLIST.begin());
                index = 0;
            }
        }

        return ret;
    }

private:

    std::string STR;
    std::vector<std::string> STRLIST;
};


int main()
{
    std::cout << "start" << std::endl;

    //open serial port
    avSerialPorts::SerialPort* comm = avSerialPorts::SerialPort::create();
    comm->connect("COM6", "9600,n,8,1");

    //console
    // char line[2048+1] = {0};
    // while (std::cin.getline(line, 2048))
    // {
        // if (strcmp(line,"quit") == 0)
        // {
            // comm->setDone(true);
            // break;
        // }
        // comm->SendCom(line,strlen(line));
    // }

    //read loop
    char read_string[2048 + 1] = { 0 };
    parser p;
    while (true)
    {
        if (!comm->isConnected())
        {
            comm->connect("COM6", "9600,n,8,1");
        }

        int rn = comm->read(read_string, 2048);
        if (rn > 0)
        {
            //打印text模式
            //printf("%s", read_string);

            //打印二进制数据
            //for (size_t i = 0; i < rn; i++)
            //{
            //    int v = atoi(&read_string[i]);
            //    printf("%d ", v);
            //}
            //printf("\n");


            //拆分数据
            std::vector<int> l = p.push(read_string, rn);

            //输出拆分数据
            for (size_t i = 0; i < l.size(); i++)
            {
                printf("%d ", l[i]);
            }
            printf("\n");

        }
    }

    return 0;
}
