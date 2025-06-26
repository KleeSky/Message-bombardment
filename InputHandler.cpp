#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::string& message, int& count ,double& interval)
{
	int Method = 0;
	std::cout << "(1)使用消息+数量 (2)数量" << std::endl;

    // 判断合法性
    while (true)
    {
        std::cout << "请输入 1 或者 2 选择发送方式：";
        if (!(std::cin >> Method) || Method <= 0 || Method >= 3)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    if (Method == 1)
    {
        std::cout << "请输入消息内容：";
        std::getline(std::cin, message);

        while (true)
        {
            std::cout << "请输入消息数量：";
            if (!(std::cin >> count) || count < 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请重新输入。" << std::endl;
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
            std::cout << "请输入消息数量：";
            if (!(std::cin >> count) || count < 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请重新输入。" << std::endl;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
			}
        }
    }

    // 询问键入间隔
    while (true)
    {
        std::cout << "请输入消息间隔（毫秒）：";
        if (!(std::cin >> interval) || interval < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
        else
        {
            break;
        }
    }
}