#include "../common_includes.h"
#include <vector>
#include <tuple>
#define noble std::vector<int>
extern int gameSeed;
extern int pointsToWin;
extern int maxGemCount;
extern std::vector<int> maxGems; // Red,Blue,Green, Black, White, Gold.
extern int colourCount;

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
    devCard(const devCard& other);
    int get_cost(devColour) const;
};

extern std::vector<devCard> commonDevs;
extern std::vector<devCard> rareDevs;
extern std::vector<devCard> epicDevs;
extern int noble_value;
extern std::vector<noble> nobles;