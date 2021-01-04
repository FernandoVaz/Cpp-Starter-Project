#include <iostream>
#include "include/SerialPort.h"
#include <cstdio>
#include <string.h>
#include <fstream>
#include <regex>

using namespace std;

const char *portName = R"(\\.\COM3)";

#define MAX_DATA_LENGTH_ARDUINO 8
char incomingData[MAX_DATA_LENGTH_ARDUINO];

//Arduino SerialPort object
SerialPort *arduino;


int main()
{
    //ofstream numbers;

    arduino = new SerialPort(portName);
    std::cout << portName << std::endl;
    std::cout << "Is connected: " << arduino->isConnected() << std::endl;
    //numbers.open("number.txt", std::ios::app);
    int hasRead;
    while(arduino->isConnected())
    {
        hasRead = arduino ->readSerialPort(incomingData, MAX_DATA_LENGTH_ARDUINO);
        if(hasRead)
        {
            std::cout << incomingData << std::endl;
        }
    }
}

