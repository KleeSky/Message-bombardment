#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

namespace AutoSender {

    // ģ��������뵥���ַ�
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

	// ģ�ⰴ�»س���
    void sendEnter() {
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    }

    void sendMessages(const std::string& message, int repeatCount, double intervalBetweenMessagesMs, int intervalBetweenCharsMs) {
        if (!message.empty()) {
            // ģʽ 1�������Զ�����Ϣ
            for (int i = 0; i < repeatCount; ++i) {
                std::cout << "���͵� " << i + 1 << " ��: " << message << std::endl;

                for (char ch : message) {
                    sendChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }
        else {
            // ģʽ 2�����ʹ�1��repeatCount������
            for (int i = 1; i <= repeatCount; ++i) {
                std::string numStr = std::to_string(i);
                std::cout << "�������֣�" << numStr << std::endl;

                for (char ch : numStr) {
                    sendChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }

        std::cout << "��Ϣ���������~" << std::endl;
    }
}