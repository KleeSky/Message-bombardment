#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::wstring& message, int& count, double& interval)
{
    int Method = 0;
    std::wcout << L"(1)使用消息+数量 (2)数量" << std::endl;

    while (true)
    {
        std::wcout << L"请输入 1 或者 2 选择发送方式：";
        if (!(std::wcin >> Method) || Method <= 0 || Method >= 3)
        {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"输入无效，请重新输入。" << std::endl;
        }
        else
        {
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            break;
        }
    }

    if (Method == 1)
    {
        std::wcout << L"请输入消息内容：";
        std::getline(std::wcin, message);

        while (true)
        {
            std::wcout << L"请输入消息数量：";
            if (!(std::wcin >> count) || count < 0)
            {
                std::wcin.clear();
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                std::wcout << L"输入无效，请重新输入。" << std::endl;
            }
            else
            {
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                break;
            }
        }
    }
    else
    {
        while (true)
        {
            std::wcout << L"请输入消息数量：";
            if (!(std::wcin >> count) || count < 0)
            {
                std::wcin.clear();
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                std::wcout << L"输入无效，请重新输入。" << std::endl;
            }
            else
            {
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                break;
            }
        }
    }

    while (true)
    {
        std::wcout << L"请输入消息间隔（毫秒）：";
        if (!(std::wcin >> interval) || interval < 0)
        {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"输入无效，请重新输入。" << std::endl;
        }
        else
        {
            break;
        }
    }
}
