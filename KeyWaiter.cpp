#include "KeyWaiter.h"
#include <iostream>
#include <thread>
#include <windows.h>

bool waitForF12()
{
    std::wcout << L"���� F12 ����ʼ������Ϣ���뽫��������������..." << std::endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_F12) & 0x8000)
        {
            return true;
        }
        Sleep(100);
    }
}
