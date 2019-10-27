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

std::string Utils::goodToString(Good good)
{
	switch (good)
	{
		case Good::food: return "Food";
		case Good::gem: return "Gem";
		case Good::metal: return "Metal";
		case Good::stone: return "Stone";
		case Good::wood: return "Wood";
		case Good::wild: return "Wild";
		default: return "INVALID GOOD";
	}
}
