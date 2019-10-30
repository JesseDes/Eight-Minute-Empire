#pragma once
#include <vector>
#include <list>

/*
    Handles the Creation of the map, via use of graphs for continent and subgraphs
*/

class Country
{
public:
    Country();
    void writeOwner(std::string owner);
    std::string getOwner();
    int addArmy();
    int removeArmy();
    int getArmy();


private:
    std::string* owner;
    std::vector<int> armies; //not implemented yet
};
