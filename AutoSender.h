#ifndef AUTOSENDER_H
#define AUTOSENDER_H

#include <string>

namespace AutoSender {

	void sendMessages(const std::wstring& message, int repeatCount, double intervalBetweenMessagesMs, int intervalBetweenCharsMs);

}
#endif