#include "ChatSession.h"

void ChatSession::addMessage(std::string user, std::string message)
{
	messages.push_back(std::pair(user, message));
	this->notify();
}

std::vector<std::pair<std::string, std::string>> ChatSession::getMessages()
{
	return this->messages;
}
