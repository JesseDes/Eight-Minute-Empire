#include "Good.h"

std::string Good::GoodToString(GoodType good)
{
	switch (good)
	{
	case GoodType::food: return "Food";
	case GoodType::gem: return "Gem";
	case GoodType::metal: return "Metal";
	case GoodType::stone: return "Stone";
	case GoodType::wood: return "Wood";
	case GoodType::wild: return "Wild";
	default: return "INVALID GOOD";
	}
}

int Good::GoodToScore(GoodType good, int amount)
{
	int score = 0;
	switch (good)
	{
		case GoodType::food: 
			if(amount >= 3) score++; 
			if(amount >= 5) score++;
			if(amount >= 7) score++;
			if(amount >= 8) score += 2;
			break;
		case GoodType::gem:
			if (amount >= 1) score++;
			if (amount >= 2) score++;
			if (amount >= 3) score++;
			if (amount >= 8) score += 2;
			break;
		case GoodType::metal:
			if (amount >= 2) score++;
			if (amount >= 4) score++;
			if (amount >= 6) score++;
			if (amount >= 7) score += 2;
			break;

		case GoodType::stone:
			if (amount >= 2) score++;
			if (amount >= 3) score++;
			if (amount >= 4) score++;
			if (amount >= 5) score += 2;
			break;

		case GoodType::wood:
			if (amount >= 2) score++;
			if (amount >= 4) score++;
			if (amount >= 5) score++;
			if (amount >= 6) score += 2;
			break;
	}

	return score;
}