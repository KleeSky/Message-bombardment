#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::string& message, int& count ,double& interval)
{
    std::cout << "��������Ϣ���ݣ�";
    std::getline(std::cin, message);

    while (true)
    {
        std::cout << "��������Ϣ������";
        if (!(std::cin >> count) || count < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������Ч�����������롣" << std::endl;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    while (true)
    {
        std::cout << "��������Ϣ��������룩��";
        if (!(std::cin >> interval) || interval < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������Ч�����������롣" << std::endl;
        }
        else
        {
            break;
		}
    }

}