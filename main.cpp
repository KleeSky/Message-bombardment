#include <iostream>
#include <windows.h>
#include <atomic>
#include <io.h>
#include <fcntl.h>
#include "InputHandler.h"
#include "AutoSender.h"

std::atomic<bool> running(true);

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // 改成宽字符串
    std::wstring message;
    int count;
    double interval;

    getUserInput(message, count, interval);

    std::wcout << L"五秒后开始输出内容，请将焦点放在输入框中..." << std::endl;
    Sleep(5000);

    AutoSender::sendMessages(message, count, interval, 1);

    return 0;
}
