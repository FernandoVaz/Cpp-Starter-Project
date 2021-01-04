#include <iostream>
#include "include/SerialPort.h"
#include "winuser.h"
#include <cstdio>
#include <string.h>
#include <fstream>
#include <regex>
#include <winable.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const char *portName = R"(\\.\COM3)";

#define MAX_DATA_LENGTH_ARDUINO 8
char incomingData[MAX_DATA_LENGTH_ARDUINO];

//Arduino SerialPort object
SerialPort *arduino;

int main()
{
    //ofstream numbers;
    INPUT ip;

    arduino = new SerialPort(portName);
    std::cout << portName << std::endl;
    std::cout << "Is connected: " << arduino->isConnected() << std::endl;
    //numbers.open("number.txt", std::ios::app);
    int hasRead;
    while(arduino->isConnected())
    {
        hasRead = arduino ->readSerialPort(incomingData, MAX_DATA_LENGTH_ARDUINO);
        if(hasRead) {
            // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;

            // Press the "A" key
            ip.ki.wVk = 0x41;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));

            std::cout << incomingData << std::endl;
        }
        Sleep(50);
    }

    // This structure will be used to create the keyboard
    // input event.
    //




    // Exit normally
    return 0;
}

