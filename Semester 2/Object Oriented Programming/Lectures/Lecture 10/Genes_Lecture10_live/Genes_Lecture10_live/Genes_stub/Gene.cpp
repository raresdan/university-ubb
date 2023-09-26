#include "Gene.h"
#include <sstream>

std::string Gene::toString()
{
	std::stringstream s;
	s << this->organismName << " \t" << this->name << std::endl;
	return std::string(s.str());
}