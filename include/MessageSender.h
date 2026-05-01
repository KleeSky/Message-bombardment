#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H

#include <string>
#include <atomic>
#include <functional>

namespace core {

enum class SendMode {
    CustomMessage,  // 自定义消息 + 数量
    NumberSequence  // 仅数量，自动发送递增数字
};

struct SendConfig {
    SendMode mode = SendMode::CustomMessage;
    std::wstring message;
    int count = 10;
    int messageIntervalMs = 1000;
    int charIntervalMs = 1;
};

class MessageSender {
public:
    using ProgressCallback = std::function<void(int current, int total)>;
    using StatusCallback = std::function<void(const std::wstring& status)>;

    MessageSender();
    ~MessageSender();

    // 开始发送消息（异步）
    void startSending(const SendConfig& config);
    
    // 停止发送
    void stopSending();
    
    // 是否正在发送
    bool isSending() const;
    
    // 设置进度回调
    void setProgressCallback(ProgressCallback callback);
    
    // 设置状态回调
    void setStatusCallback(StatusCallback callback);

private:
    void sendingThreadFunc(const SendConfig& config);
    
    std::atomic<bool> m_running{false};
    std::atomic<bool> m_stopRequested{false};
    ProgressCallback m_progressCallback;
    StatusCallback m_statusCallback;
};

} // namespace core

#endif // MESSAGE_SENDER_H
