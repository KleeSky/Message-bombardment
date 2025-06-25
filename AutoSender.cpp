#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

namespace AutoSender {

    void sendChar(char ch) {
        SHORT vk = VkKeyScanA(ch);
        if (vk == -1) {
            std::cout << "�޷�ӳ���ַ�: " << ch << "������" << std::endl;
            return;
        }

        BYTE vkCode = vk & 0xFF;
        BYTE shiftState = (vk >> 8) & 0xFF;

        if (shiftState & 1) {
            keybd_event(VK_SHIFT, 0, 0, 0);
        }

        keybd_event(vkCode, 0, 0, 0);
        keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0);

        if (shiftState & 1) {
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    void sendEnter() {
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    }

    void sendMessages(const std::string& message, int repeatCount, double intervalBetweenMessagesMs, int intervalBetweenCharsMs) {
        for (int i = 0; i < repeatCount; ++i) {
            std::cout << "��ʼ������Ϣ�� " << i + 1 << " ��" << std::endl;

            for (char ch : message) {
                sendChar(ch);
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
            }

            sendEnter();
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
        }

        std::cout << "��Ϣ���������~" << std::endl;
    }
}