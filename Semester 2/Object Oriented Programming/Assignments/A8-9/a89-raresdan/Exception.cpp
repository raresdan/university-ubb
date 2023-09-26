#include "Exception.h"

FileException::FileException(const std::string& throwMessage) : message(throwMessage)
{
}

const char* FileException::what()
{
	return message.c_str();
}
