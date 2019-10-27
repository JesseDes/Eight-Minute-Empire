#pragma once
#include <string>
/*
Action contains a list of Action type and Action object
An Action is a type of action a player is allowed to do during the game.
*/

enum class ActionType {
	null = -1,
	build = 0,
	moveGround = 1,
	moveSea = 2,
	kill = 3,
	recruit = 4
};


struct Action {
	ActionType type;  // type of action
	int amount;  //amount of times an action will be done

	std::string static typeToString(ActionType type)
	{
		switch (type)
		{
			case ActionType::build: return "build";
			case ActionType::moveGround: return "move over Ground";
			case ActionType::moveSea: return "move over Sea";
			case ActionType::kill: return " Kill an army";
			case ActionType::recruit: return " recruit an army";
			default: return "NULL";
		}
	}
};




