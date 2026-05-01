#include "InputSimulator.h"
#include <Windows.h>
#include <thread>
#include <chrono>

namespace core {

void InputSimulator::sendUnicodeChar(wchar_t ch) {
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = 0;
    inputs[0].ki.wScan = ch;
    inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0;
    inputs[1].ki.wScan = ch;
    inputs[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
}

void InputSimulator::sendEnter() {
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_RETURN;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_RETURN;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inputs, sizeof(INPUT));
}

void InputSimulator::sendString(const std::wstring& text, int charIntervalMs) {
    for (wchar_t ch : text) {
        sendUnicodeChar(ch);
        if (charIntervalMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(charIntervalMs));
        }
    }
}

} // namespace core
