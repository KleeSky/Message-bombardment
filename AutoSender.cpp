#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

namespace AutoSender {

    // 模拟键盘输入单个字符
    void sendChar(char ch) {
        SHORT vk = VkKeyScanA(ch);
        if (vk == -1) {
            std::cout << "无法映射字符: " << ch << "，跳过" << std::endl;
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

	// 模拟按下回车键
    void sendEnter() {
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    }

    void sendMessages(const std::string& message, int repeatCount, double intervalBetweenMessagesMs, int intervalBetweenCharsMs) {
        if (!message.empty()) {
            // 模式 1：发送自定义消息
            for (int i = 0; i < repeatCount; ++i) {
                std::cout << "发送第 " << i + 1 << " 次: " << message << std::endl;

                for (char ch : message) {
                    sendChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }
        else {
            // 模式 2：发送从1到repeatCount的数字
            for (int i = 1; i <= repeatCount; ++i) {
                std::string numStr = std::to_string(i);
                std::cout << "发送数字：" << numStr << std::endl;

                for (char ch : numStr) {
                    sendChar(ch);
                    std::this_thread::sleep_for(std::chrono::milliseconds(intervalBetweenCharsMs));
                }

                sendEnter();
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(intervalBetweenMessagesMs));
            }
        }

        std::cout << "消息发送完毕喵~" << std::endl;
    }
}