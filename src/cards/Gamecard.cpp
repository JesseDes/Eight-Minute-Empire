#pragma once

#include "Cardsfactory.h"


void Wood::Draw() { 
    numberOfActions = 2;
    isAnd = false;
    good = GoodType(0);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    Action action2;
    action2.type = (ActionType)(rand() % 5);
    action2.amount = 2;
    actions[1] = action2;
}

    numberOfActions = 2;
    isAnd = false;

    good = GoodType(1);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    Action action2;
    action2.type = (ActionType)(rand() % 5);
    action2.amount = 2;
    actions[1] = action2;
}
    numberOfActions = 2;
    isAnd = true;

    good = GoodType(2);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    Action action2;
    action2.type = (ActionType)(rand() % 5);
    action2.amount = 2;
    actions[1] = action2;
}
    numberOfActions = 1;
    isAnd = false;

    good = GoodType(3);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    //setting 2nd action to null
    Action action2;
    action2.type = (ActionType)(-1);
    action2.amount = 0;
    actions[1] = action2;
}
    numberOfActions = 1;
    isAnd = false;

    good = GoodType(4);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    //setting 2nd action to null
    Action action2;
    action2.type = (ActionType)(-1);
    action2.amount = 0;
    actions[1] = action2;
}
    numberOfActions = 1;
    isAnd = false;

    good = GoodType(5);

    Action action1;
    action1.type = (ActionType)(rand() % 5);
    action1.amount = 3;
    actions[0] = action1;

    //setting 2nd action to null
    Action action2;
    action2.type = (ActionType)(-1);
    action2.amount = 0;
    actions[1] = action2;
}