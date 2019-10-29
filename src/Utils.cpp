#include "pch.h"
#include "Utils.h"

int Utils::validInputRange(int min, int max, int value, std::string msg)
{
	while (value < min || value > max)
	{
		std::cout << msg << "\n";
		std::cin >> value;
	}

	return value;
}

int Utils::validInputMin(int min, int value, std::string msg)
{
	while (value < min)
	{
		std::cout << msg << "\n";
		std::cin >> value;
	}

	return value;
}

int Utils::validInputMax( int max, int value, std::string msg)
{
	while (value > max)
	{
		std::cout << msg << "\n";
		std::cin >> value;
	}

	return value;
}
