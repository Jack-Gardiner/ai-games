#include "../common_includes.h"
#include <vector>
#include <tuple>
#define noble std::vector<int>
int gameSeed = -1;
int pointsToWin = 15;
int maxGemCount = 10;
std::vector<int> maxGems = {7,7,7,7,7,5}; // Red,Blue,Green, Black, White, Gold.
enum devColour{
    RED,
    BLUE,
    GREEN,
    BLACK,
    WHITE,
    GOLD
};
class devCard
{
private:
    /* data */
    std::vector<int> cost_array = {0,0,0,0,0};
public:
    devColour colour;
    int points;
    devCard(devColour newcolour,int newpoints, int rCost,int bCost,int gCost,int blCost,int wCost);
    int get_cost(devColour);
};

devCard::devCard(devColour newcolour,int newpoints, int rCost,int bCost,int gCost,int blCost,int wCost)
{
    colour = newcolour;
    newpoints = newpoints;
    cost_array = {rCost,bCost,gCost,blCost,wCost};
}
int devCard::get_cost(devColour col){
    return cost_array[col];
}

std::vector<devCard> commonDevs = {};
std::vector<devCard> rareDevs = {};
std::vector<devCard> epicDevs = {};
int noble_value = 3;
std::vector<noble> nobles = {{4,0,4,0,0}
};