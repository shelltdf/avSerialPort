
#include <iostream>
#include <map>
#include <string>

void avSerialPortInit();
void avSerialPortShutdown();

int avSerialPortGetNamesCount();
int avSerialPortGetNameSize(int id);
int avSerialPortGetNameData(int id, char* name);

bool avSerialPortOpen(int id, const char* name, const char* str);
void avSerialPortClose(int id);
bool avSerialPortIsOpen(int id);
bool avSerialPortRead(int id);
bool avSerialPortSend(int id);


