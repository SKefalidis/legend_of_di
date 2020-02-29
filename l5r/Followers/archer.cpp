#include "archer.h"

Archer::Archer(string iName) : Follower(iName)
{
    cost = 0;
    attackBonus = 0;
    defenceBonus = 2;
    minimumHonour = 1;
    effectBonus = 1;
    effectCost = 2;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::archer;
#endif
}
