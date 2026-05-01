#include "MessageSender.h"
#include "InputSimulator.h"
#include <thread>
#include <chrono>

namespace core {

MessageSender::MessageSender() = default;

MessageSender::~MessageSender() {
    stopSending();
}

void MessageSender::startSending(const SendConfig& config) {
    if (m_running) {
        return;
    }
    
    m_stopRequested = false;
    m_running = true;
    
    std::thread(&MessageSender::sendingThreadFunc, this, config).detach();
}

void MessageSender::stopSending() {
    m_stopRequested = true;
}

bool MessageSender::isSending() const {
    return m_running;
}

void MessageSender::setProgressCallback(ProgressCallback callback) {
    m_progressCallback = callback;
}

void MessageSender::setStatusCallback(StatusCallback callback) {
    m_statusCallback = callback;
}

void MessageSender::sendingThreadFunc(const SendConfig& config) {
    if (m_statusCallback) {
        m_statusCallback(L"开始发送消息...");
    }
    
    if (config.mode == SendMode::CustomMessage && !config.message.empty()) {
        // 自定义消息模式
        for (int i = 0; i < config.count && !m_stopRequested; ++i) {
            if (m_statusCallback) {
                std::wstring status = L"发送第 " + std::to_wstring(i + 1) + L" 次：" + config.message;
                m_statusCallback(status);
            }
            
            InputSimulator::sendString(config.message, config.charIntervalMs);
            InputSimulator::sendEnter();
            
            if (m_progressCallback) {
                m_progressCallback(i + 1, config.count);
            }
            
            if (i < config.count - 1 && !m_stopRequested) {
                std::this_thread::sleep_for(std::chrono::milliseconds(config.messageIntervalMs));
            }
        }
    } else {
        // 数字序列模式
        for (int i = 1; i <= config.count && !m_stopRequested; ++i) {
            std::wstring numStr = std::to_wstring(i);
            
            if (m_statusCallback) {
                std::wstring status = L"发送数字：" + numStr;
                m_statusCallback(status);
            }
            
            InputSimulator::sendString(numStr, config.charIntervalMs);
            InputSimulator::sendEnter();
            
            if (m_progressCallback) {
                m_progressCallback(i, config.count);
            }
            
            if (i < config.count && !m_stopRequested) {
                std::this_thread::sleep_for(std::chrono::milliseconds(config.messageIntervalMs));
            }
        }
    }
    
    m_running = false;
    
    if (m_statusCallback) {
        if (m_stopRequested) {
            m_statusCallback(L"已停止发送");
        } else {
            m_statusCallback(L"消息发送完毕喵~");
        }
    }
}

} // namespace core
