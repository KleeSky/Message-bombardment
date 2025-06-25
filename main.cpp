#include <iostream>
#include <windows.h>
#include "InputHandler.h"
#include "AutoSender.h"

std::atomic<bool> running(true);

int main()
{
	// 调用InputHandler类的getUserInput方法
	std::string message;
	int count;
	double interval;
	getUserInput(message, count, interval);

	std::cout << "五秒后开始输出内容，请将焦点放在输入框中..." << std::endl;
	Sleep(5000);

	// 调用AutoSender类的sendMessages方法
	AutoSender::sendMessages(message, count, interval, 1);

	return 0;
}