
#include <iostream>
#include <map>
#include <string>

void avSerialPortInit();
void avSerialPortShutdown();

int avSerialPortGetNames(char* str, int len);

//int avSerialPortGetNamesCount();
//int avSerialPortGetNameSize(int index);
//int avSerialPortGetNameData(int index, char* name);

bool avSerialPortOpen(const char* name, const char* str);
void avSerialPortClose(const char* name);
bool avSerialPortIsOpen(const char* name);
bool avSerialPortRead(const char* name, char* str, int len);
bool avSerialPortSend(const char* name, char* str, int len);


