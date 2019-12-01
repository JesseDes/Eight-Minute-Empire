#include "pch.h"
#include "Utils.h"

int Utils::validInputRange(int min, int max, std::string msg)
{
	int selection;
	try
	{
		std::cin >> selection;
		if (selection < min || selection > max || std::cin.fail())
			throw msg;
	}
	catch (std::string error)
	{
		std::cout << error << "\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');

		selection = validInputRange(min, max, error);
	}

	return selection;

}

int Utils::validInputMin(int min, std::string msg)
{
	int selection;
	try
	{
		std::cin >> selection;
		if (selection < min || std::cin.fail())
			throw msg;
	}
	catch (std::string error)
	{
		std::cout << error << "\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');

		selection = validInputMin(min, error);
	}

	return selection;
}

int Utils::validInputMax( int max, std::string msg)
{
	int selection;
	try
	{
		std::cin >> selection;
		if (selection > max || std::cin.fail())
			throw msg;
	}
	catch (std::string error)
	{
		std::cout << error << "\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');

		selection = validInputMax( max, error);
	}

	return selection;
}

void Utils::View(std::string output)
{
	std::cout << output << std::endl;
}