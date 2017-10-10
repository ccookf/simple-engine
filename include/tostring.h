#ifndef TOSTRING_H
#define TOSTRING_H

#include <iomanip>
#include <sstream>
#include <string>

template<class T>
std::string toString(T input)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << input;
	return stream.str();
}

#endif