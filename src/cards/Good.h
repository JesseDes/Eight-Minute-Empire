#pragma once
#include <string>
/*
Types of goods that can be acquired in the game
*/

enum class GoodType {
	wood = 0,
	stone = 1,
	food = 2,
	gem = 3,
	metal = 4,
	wild = 5

};
class Good {
public:
	static std::string GoodToString(GoodType good);	//returns string value associate with a goodType
	static int GoodToScore(GoodType good, int amount); //calculates the score for a specific GoodType for a certain amount of it
};