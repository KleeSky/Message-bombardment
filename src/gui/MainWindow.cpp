#include "MainWindow.h"
#include <commctrl.h>
#include <sstream>

#pragma comment(lib, "comctl32.lib")

// 控件 ID
#define IDC_MODE_COMBO 1001
#define IDC_MESSAGE_EDIT 1002
#define IDC_MESSAGE_LABEL 1003
#define IDC_COUNT_EDIT 1004
#define IDC_MSG_INTERVAL_EDIT 1005
#define IDC_CHAR_INTERVAL_EDIT 1006
#define IDC_START_BUTTON 1007
#define IDC_STOP_BUTTON 1008
#define IDC_PROGRESS_BAR 1009
#define IDC_STATUS_LABEL 1010
#define IDC_PROGRESS_LABEL 1011

// 窗口尺寸
#define WINDOW_WIDTH 450
#define WINDOW_HEIGHT 400

MainWindow::MainWindow(HINSTANCE hInstance) 
    : m_hInstance(hInstance), m_hwnd(nullptr), m_sender(std::make_unique<core::MessageSender>()) {
    
    // 初始化配置
    m_config.mode = core::SendMode::CustomMessage;
    m_config.count = 10;
    m_config.messageIntervalMs = 1000;
    m_config.charIntervalMs = 1;
    
    // 设置回调
    m_sender->setProgressCallback([this](int current, int total) {
        PostMessage(m_hwnd, WM_USER + 1, current, total);
    });
    
    m_sender->setStatusCallback([this](const std::wstring& status) {
        PostMessage(m_hwnd, WM_USER + 2, 0, reinterpret_cast<LPARAM>(new std::wstring(status)));
    });
}

MainWindow::~MainWindow() = default;

bool MainWindow::initialize() {
    // 注册窗口类
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = windowProc;
    wc.hInstance = m_hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"WeChatBombWindowClass";
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    
    if (!RegisterClassExW(&wc)) {
        return false;
    }
    
    // 创建窗口
    m_hwnd = CreateWindowExW(
        0,
        L"WeChatBombWindowClass",
        L"微信消息轰炸器 - GUI 版",
        WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        nullptr,
        nullptr,
        m_hInstance,
        this
    );
    
    if (!m_hwnd) {
        return false;
    }
    
    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);
    
    return true;
}

int MainWindow::run() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK MainWindow::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    MainWindow* pThis = nullptr;
    
    if (uMsg == WM_NCCREATE) {
        CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        pThis = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hwnd = hwnd;
    } else {
        pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }
    
    if (pThis) {
        return pThis->handleMessage(uMsg, wParam, lParam);
    }
    
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        createControls();
        return 0;
        
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_START_BUTTON:
            onStartButtonClick();
            break;
        case IDC_STOP_BUTTON:
            onStopButtonClick();
            break;
        case IDC_MODE_COMBO:
            if (HIWORD(wParam) == CBN_SELCHANGE) {
                onModeChange();
            }
            break;
        }
        return 0;
        
    case WM_USER + 1: // 进度更新
        updateProgress(static_cast<int>(wParam), static_cast<int>(lParam));
        return 0;
        
    case WM_USER + 2: // 状态更新
        {
            std::wstring* pStatus = reinterpret_cast<std::wstring*>(lParam);
            if (pStatus) {
                updateStatus(*pStatus);
                delete pStatus;
            }
        }
        return 0;
        
    case WM_CLOSE:
        if (m_sender->isSending()) {
            m_sender->stopSending();
        }
        DestroyWindow(m_hwnd);
        return 0;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProcW(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::createControls() {
    HFONT hFont = CreateFontW(
        16, 0, 0, 0, FW_NORMAL,
        FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        L"Microsoft YaHei UI"
    );
    
    // 发送模式标签
    CreateWindowExW(0, L"STATIC", L"发送模式:",
        WS_CHILD | WS_VISIBLE,
        20, 15, 80, 20,
        m_hwnd, nullptr, m_hInstance, nullptr);
    
    // 发送模式下拉框
    m_modeCombo = CreateWindowExW(0, L"COMBOBOX", L"",
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
        110, 12, 180, 100,
        m_hwnd, (HMENU)IDC_MODE_COMBO, m_hInstance, nullptr);
    SendMessageW(m_modeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"自定义消息 + 数量"));
    SendMessageW(m_modeCombo, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(L"仅数量 (递增数字)"));
    SendMessageW(m_modeCombo, CB_SETCURSEL, 0, 0);
    
    // 消息内容标签
    m_messageLabel = CreateWindowExW(0, L"STATIC", L"消息内容:",
        WS_CHILD | WS_VISIBLE,
        20, 50, 80, 20,
        m_hwnd, (HMENU)IDC_MESSAGE_LABEL, m_hInstance, nullptr);
    
    // 消息内容输入框
    m_messageEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
        WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
        110, 47, 300, 25,
        m_hwnd, (HMENU)IDC_MESSAGE_EDIT, m_hInstance, nullptr);
    
    // 数量标签
    CreateWindowExW(0, L"STATIC", L"发送数量:",
        WS_CHILD | WS_VISIBLE,
        20, 85, 80, 20,
        m_hwnd, nullptr, m_hInstance, nullptr);
    
    // 数量输入框
    m_countEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"10",
        WS_CHILD | WS_VISIBLE | ES_NUMBER,
        110, 82, 100, 25,
        m_hwnd, (HMENU)IDC_COUNT_EDIT, m_hInstance, nullptr);
    
    // 消息间隔标签
    CreateWindowExW(0, L"STATIC", L"消息间隔 (ms):",
        WS_CHILD | WS_VISIBLE,
        20, 120, 100, 20,
        m_hwnd, nullptr, m_hInstance, nullptr);
    
    // 消息间隔输入框
    m_messageIntervalEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"1000",
        WS_CHILD | WS_VISIBLE | ES_NUMBER,
        130, 117, 100, 25,
        m_hwnd, (HMENU)IDC_MSG_INTERVAL_EDIT, m_hInstance, nullptr);
    
    // 字符间隔标签
    CreateWindowExW(0, L"STATIC", L"字符间隔 (ms):",
        WS_CHILD | WS_VISIBLE,
        20, 155, 100, 20,
        m_hwnd, nullptr, m_hInstance, nullptr);
    
    // 字符间隔输入框
    m_charIntervalEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"1",
        WS_CHILD | WS_VISIBLE | ES_NUMBER,
        130, 152, 100, 25,
        m_hwnd, (HMENU)IDC_CHAR_INTERVAL_EDIT, m_hInstance, nullptr);
    
    // 开始按钮
    m_startButton = CreateWindowExW(0, L"BUTTON", L"开始发送",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 195, 120, 35,
        m_hwnd, (HMENU)IDC_START_BUTTON, m_hInstance, nullptr);
    
    // 停止按钮
    m_stopButton = CreateWindowExW(0, L"BUTTON", L"停止",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED,
        160, 195, 120, 35,
        m_hwnd, (HMENU)IDC_STOP_BUTTON, m_hInstance, nullptr);
    
    // 进度条
    m_progressBar = CreateWindowExW(0, PROGRESS_CLASSW, L"",
        WS_CHILD | WS_VISIBLE,
        20, 245, 390, 25,
        m_hwnd, (HMENU)IDC_PROGRESS_BAR, m_hInstance, nullptr);
    SendMessageW(m_progressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
    SendMessageW(m_progressBar, PBM_SETPOS, 0, 0);
    
    // 进度标签
    m_progressLabel = CreateWindowExW(0, L"STATIC", L"进度：0 / 0",
        WS_CHILD | WS_VISIBLE,
        20, 275, 200, 20,
        m_hwnd, (HMENU)IDC_PROGRESS_LABEL, m_hInstance, nullptr);
    
    // 状态标签
    m_statusLabel = CreateWindowExW(0, L"STATIC", L"状态：就绪",
        WS_CHILD | WS_VISIBLE,
        20, 300, 390, 20,
        m_hwnd, (HMENU)IDC_STATUS_LABEL, m_hInstance, nullptr);
    
    // 为所有控件设置字体
    HWND hWndChild = GetWindow(m_hwnd, GW_CHILD);
    while (hWndChild) {
        SendMessageW(hWndChild, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
        hWndChild = GetNextWindow(hWndChild, GW_HWNDNEXT);
    }
}

void MainWindow::updateUIState(bool isSending) {
    EnableWindow(m_modeCombo, !isSending);
    EnableWindow(m_messageEdit, !isSending);
    EnableWindow(m_countEdit, !isSending);
    EnableWindow(m_messageIntervalEdit, !isSending);
    EnableWindow(m_charIntervalEdit, !isSending);
    EnableWindow(m_startButton, !isSending);
    EnableWindow(m_stopButton, isSending);
}

void MainWindow::updateProgress(int current, int total) {
    std::wstring text = L"进度：" + std::to_wstring(current) + L" / " + std::to_wstring(total);
    SetWindowTextW(m_progressLabel, text.c_str());
    
    int percent = (total > 0) ? (current * 100 / total) : 0;
    SendMessageW(m_progressBar, PBM_SETPOS, percent, 0);
}

void MainWindow::updateStatus(const std::wstring& status) {
    std::wstring displayText = L"状态：" + status;
    SetWindowTextW(m_statusLabel, displayText.c_str());
}

void MainWindow::onStartButtonClick() {
    // 获取配置
    wchar_t buffer[256];
    
    // 获取模式
    int selectedMode = static_cast<int>(SendMessageW(m_modeCombo, CB_GETCURSEL, 0, 0));
    m_config.mode = (selectedMode == 0) ? core::SendMode::CustomMessage : core::SendMode::NumberSequence;
    
    // 获取消息内容
    GetWindowTextW(m_messageEdit, buffer, 256);
    m_config.message = buffer;
    
    // 获取数量
    GetWindowTextW(m_countEdit, buffer, 256);
    m_config.count = _wtoi(buffer);
    if (m_config.count <= 0) {
        MessageBoxW(m_hwnd, L"请输入有效的发送数量", L"错误", MB_OK | MB_ICONERROR);
        return;
    }
    
    // 获取消息间隔
    GetWindowTextW(m_messageIntervalEdit, buffer, 256);
    m_config.messageIntervalMs = _wtoi(buffer);
    if (m_config.messageIntervalMs < 0) {
        m_config.messageIntervalMs = 0;
    }
    
    // 获取字符间隔
    GetWindowTextW(m_charIntervalEdit, buffer, 256);
    m_config.charIntervalMs = _wtoi(buffer);
    if (m_config.charIntervalMs < 0) {
        m_config.charIntervalMs = 0;
    }
    
    // 验证自定义消息模式
    if (m_config.mode == core::SendMode::CustomMessage && m_config.message.empty()) {
        MessageBoxW(m_hwnd, L"请输入消息内容", L"错误", MB_OK | MB_ICONERROR);
        return;
    }
    
    // 设置进度条范围
    SendMessageW(m_progressBar, PBM_SETRANGE, 0, MAKELPARAM(0, m_config.count));
    
    // 开始发送
    updateUIState(true);
    m_sender->startSending(m_config);
}

void MainWindow::onStopButtonClick() {
    m_sender->stopSending();
    updateUIState(false);
}

void MainWindow::onModeChange() {
    int selectedMode = static_cast<int>(SendMessageW(m_modeCombo, CB_GETCURSEL, 0, 0));
    
    if (selectedMode == 1) { // 数字序列模式
        EnableWindow(m_messageEdit, FALSE);
        SetWindowTextW(m_messageEdit, L"");
    } else {
        EnableWindow(m_messageEdit, TRUE);
    }
}

// 程序入口点
extern "C" int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow) {
    
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
    
    // 初始化通用控件
    INITCOMMONCONTROLSEX icex = {};
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icex);
    
    MainWindow window(hInstance);
    
    if (!window.initialize()) {
        MessageBoxW(nullptr, L"窗口创建失败", L"错误", MB_OK | MB_ICONERROR);
        return -1;
    }
    
    return window.run();
}
