#include "KeyWaiter.h"
#include <iostream>
#include <thread>
#include <windows.h>

bool waitForF12()
{
    std::wcout << L"按下 F12 键开始发送消息，请将焦点放在输入框中..." << std::endl;

    while (true)
    {
        if (GetAsyncKeyState(VK_F12) & 0x8000)
        {
            return true;
        }
        Sleep(100);
    }
}
