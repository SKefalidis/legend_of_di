#include "bow.h"

Bow::Bow(string iName) : Item(iName)
{
    cost = 2;
    attackBonus = 2;
    defenceBonus = 2;
    minimumHonour = 2;
    effectBonus = 3;
    effectCost = 4;
    durability = 5;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::bow;
#endif
}
