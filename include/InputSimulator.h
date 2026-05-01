#ifndef INPUT_SIMULATOR_H
#define INPUT_SIMULATOR_H

#include <string>

namespace core {

class InputSimulator {
public:
    // 发送单个 Unicode 字符（支持汉字和符号）
    static void sendUnicodeChar(wchar_t ch);
    
    // 发送回车键
    static void sendEnter();
    
    // 发送字符串消息
    static void sendString(const std::wstring& text, int charIntervalMs = 1);
};

} // namespace core

#endif // INPUT_SIMULATOR_H
