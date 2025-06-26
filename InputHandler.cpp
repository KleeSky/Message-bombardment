#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::wstring& message, int& count, double& interval)
{
    int Method = 0;
    std::wcout << L"(1)ʹ����Ϣ+���� (2)����" << std::endl;

    while (true)
    {
        std::wcout << L"������ 1 ���� 2 ѡ���ͷ�ʽ��";
        if (!(std::wcin >> Method) || Method <= 0 || Method >= 3)
        {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"������Ч�����������롣" << std::endl;
        }
        else
        {
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            break;
        }
    }

    if (Method == 1)
    {
        std::wcout << L"��������Ϣ���ݣ�";
        std::getline(std::wcin, message);

        while (true)
        {
            std::wcout << L"��������Ϣ������";
            if (!(std::wcin >> count) || count < 0)
            {
                std::wcin.clear();
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                std::wcout << L"������Ч�����������롣" << std::endl;
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
            std::wcout << L"��������Ϣ������";
            if (!(std::wcin >> count) || count < 0)
            {
                std::wcin.clear();
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                std::wcout << L"������Ч�����������롣" << std::endl;
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
        std::wcout << L"��������Ϣ��������룩��";
        if (!(std::wcin >> interval) || interval < 0)
        {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"������Ч�����������롣" << std::endl;
        }
        else
        {
            break;
        }
    }
}
