#include "spear.h"

Spear::Spear(string iName) : Item(iName)
{
    cost = 0;
    attackBonus = 0;
    defenceBonus = 2;
    minimumHonour = 1;
    effectBonus = 1;
    effectCost = 2;
    durability = 3;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::spear;
#endif
}
