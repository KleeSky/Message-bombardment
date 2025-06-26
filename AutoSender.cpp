#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

namespace AutoSender {

    // ���͵���Unicode�ַ���֧�ֺ��ֺͷ��ţ�
    void sendUnicodeChar(wchar_t ch) {
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

    // ���ͻس���
    void sendEnter() {
        INPUT inputs[2] = {};

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_RETURN;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_RETURN;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(2, inputs, sizeof(INPUT));
    }

    // ������Ϣ����Ϣ��wstring֧�ֺ���
    void sendMessages(const std::wstring& message, int repeatCount, double intervalBetweenMessagesMs, int intervalBetweenCharsMs) {
        if (!message.empty()) {
            for (int i = 0; i < repeatCount; ++i) {
                std::wcout << L"���͵� " << i + 1 << L" ��: " << message << std::endl;

                for (wchar_t ch : message) {
                    sendUnicodeChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }
        else {
            // ��������ģʽ
            for (int i = 1; i <= repeatCount; ++i) {
                std::wstring numStr = std::to_wstring(i);
                std::wcout << L"�������֣�" << numStr << std::endl;

                for (wchar_t ch : numStr) {
                    sendUnicodeChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }

        std::wcout << L"��Ϣ���������~" << std::endl;
    }
}
