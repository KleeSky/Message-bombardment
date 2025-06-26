#include <iostream>
#include <windows.h>
#include <atomic>
#include <io.h>
#include <fcntl.h>
#include "InputHandler.h"
#include "AutoSender.h"
#include "KeyWaiter.h"

std::atomic<bool> running(true);

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // ¸Ä³É¿í×Ö·û´®
    std::wstring message;
    int count;
    double interval;

    getUserInput(message, count, interval);

    if (waitForF12())
    {
        AutoSender::sendMessages(message, count, interval, 1);
    }

    return 0;
}
