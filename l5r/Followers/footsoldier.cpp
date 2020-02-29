#include "footsoldier.h"

Footsoldier::Footsoldier(string iName) : Follower(iName)
{
    cost = 0;
    attackBonus = 2;
    defenceBonus = 0;
    minimumHonour = 1;
    effectBonus = 1;
    effectCost = 2;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::footsoldier;
#endif
}
