#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <windows.h>
#include <string>
#include <memory>
#include "../include/MessageSender.h"

class MainWindow {
public:
    MainWindow(HINSTANCE hInstance);
    ~MainWindow();
    
    bool initialize();
    int run();
    
private:
    static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    void createControls();
    void updateUIState(bool isSending);
    void updateProgress(int current, int total);
    void updateStatus(const std::wstring& status);
    
    void onStartButtonClick();
    void onStopButtonClick();
    void onModeChange();
    
    HINSTANCE m_hInstance;
    HWND m_hwnd;
    
    // 控件句柄
    HWND m_modeCombo;
    HWND m_messageEdit;
    HWND m_messageLabel;
    HWND m_countEdit;
    HWND m_messageIntervalEdit;
    HWND m_charIntervalEdit;
    HWND m_startButton;
    HWND m_stopButton;
    HWND m_progressBar;
    HWND m_statusLabel;
    HWND m_progressLabel;
    
    // 核心组件
    std::unique_ptr<core::MessageSender> m_sender;
    
    // 当前配置
    core::SendConfig m_config;
};

#endif // MAIN_WINDOW_H
