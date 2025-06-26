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

    // �ĳɿ��ַ���
    std::wstring message;
    int count;
    double interval;

    getUserInput(message, count, interval);

    std::wcout << L"�����ʼ������ݣ��뽫��������������..." << std::endl;
    Sleep(5000);

    AutoSender::sendMessages(message, count, interval, 1);

    return 0;
}
