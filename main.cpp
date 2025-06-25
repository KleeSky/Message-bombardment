#include <iostream>
#include <windows.h>
#include "InputHandler.h"
#include "AutoSender.h"

std::atomic<bool> running(true);

int main()
{
	// ����InputHandler���getUserInput����
	std::string message;
	int count;
	double interval;
	getUserInput(message, count, interval);

	std::cout << "�����ʼ������ݣ��뽫��������������..." << std::endl;
	Sleep(5000);

	// ����AutoSender���sendMessages����
	AutoSender::sendMessages(message, count, interval, 1);

	return 0;
}