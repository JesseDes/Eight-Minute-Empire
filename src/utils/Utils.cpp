#include "../pch.h"
#include "Utils.h"

int Utils::ValidInputRange(int min, int max, std::string msg)
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

		selection = ValidInputRange(min, max, error);
	}

	return selection;

}

int Utils::ValidInputMin(int min, std::string msg)
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

		selection = ValidInputMin(min, error);
	}

	return selection;
}

int Utils::ValidInputMax( int max, std::string msg)
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

		selection = ValidInputMax( max, error);
	}

	return selection;
}

void Utils::View(std::string output , bool isNewLine)
{
	std::cout << output;
	
	if (isNewLine)
		std::cout << std::endl;
}