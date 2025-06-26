#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::string& message, int& count ,double& interval)
{
	int Method = 0;
	std::cout << "(1)ʹ����Ϣ+���� (2)����" << std::endl;

    // �жϺϷ���
    while (true)
    {
        std::cout << "������ 1 ���� 2 ѡ���ͷ�ʽ��";
        if (!(std::cin >> Method) || Method <= 0 || Method >= 3)
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

    if (Method == 1)
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
    }
    else
    {
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
    }

    // ѯ�ʼ�����
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