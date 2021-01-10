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
#include <tchar.h>

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
    int v_TestValue;

    arduino = new SerialPort(portName);
    std::cout << portName << std::endl;
    std::cout << "Is connected: " << arduino->isConnected() << std::endl;
    //numbers.open("number.txt", std::ios::app);
    int hasRead;

    if (!vJoyEnabled())
    {
        _tprintf("Failed Getting vJoy attributes.\n");
        return -2;
    }
    else
    {
        _tprintf("Vendor: %S\nProduct :%S\nVersion Number:%S\n",\
            TEXT(GetvJoyManufacturerString()),\
            TEXT(GetvJoyProductString()),\
            TEXT(GetvJoySerialNumberString()));
    };


    WORD VerDll, VerDrv;
    if (!DriverMatch(&VerDll, &VerDrv))
        _tprintf("Failed\r\nvJoy Driver (version %04x) does not match "
                 "vJoyInterface DLL (version %04x)\n", VerDrv ,VerDll);
    else
        _tprintf( "OK - vJoy Driver and vJoyInterface DLL match vJoyInterface "
                  "DLL (version %04x)\n", VerDrv);

    VjdStat status = GetVJDStatus(iInterface);

    switch (status)
    {
        case VJD_STAT_OWN:
            _tprintf("vJoy Device %d is already owned by this feeder\n", iInterface);
            break;
        case VJD_STAT_FREE:
            _tprintf("vJoy Device %d is free\n", iInterface);
            break;
        case VJD_STAT_BUSY:
            _tprintf("vJoy Device %d is already owned by another feeder\nCannot continue\n", iInterface);
            return -3;
        case VJD_STAT_MISS:
            _tprintf("vJoy Device %d is not installed or disabled\nCannot continue\n", iInterface);
            return -4;
        default:
            _tprintf("vJoy Device %d general error\nCannot continue\n", iInterface);
            return -1;
    };

    // Acquire the target if not already owned
    if ((status == VJD_STAT_OWN) || ((status == VJD_STAT_FREE) && (!AcquireVJD(iInterface))))
    {
        _tprintf("Failed to acquire vJoy device number %d.\n", iInterface);
        return -1;
    }
    else
        _tprintf("Acquired: vJoy device number %d.\n", iInterface);


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


        v_TestValue = 0;
        for(int i=0; i < 10; i++)
        {
            // Set position of 4 axes
            res = SetAxis(v_TestValue = 0+00, iInterface, HID_USAGE_X);
            res = SetAxis(v_TestValue = 0+10, iInterface, HID_USAGE_Y);
            res = SetAxis(v_TestValue = 0+20, iInterface, HID_USAGE_Z);
            res = SetAxis(v_TestValue = 0+30, iInterface, HID_USAGE_RX);
            res = SetAxis(v_TestValue = 0+40, iInterface, HID_USAGE_RZ);
            // Press Button 1, Keep button 3 not pressed
            res = SetBtn(TRUE, iInterface, 1);
            res = SetBtn(FALSE, iInterface, 3);
        }
        Sleep(20);
        v_TestValue = 0+=10;


        Sleep(20);
    }

    // This structure will be used to create the keyboard
    // input event.
    //




    // Exit normally
    return 0;
}

