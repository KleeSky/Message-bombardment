#include <iostream>
#include <string>
#include <limits>

void getUserInput(std::string& message, int& count ,double& interval)
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