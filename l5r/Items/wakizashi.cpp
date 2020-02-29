#include "wakizashi.h"

Wakizashi::Wakizashi(string iName) : Item(iName)
{
    cost = 8;
    attackBonus = 5;
    defenceBonus = 5;
    minimumHonour = 3;
    effectBonus = 3;
    effectCost = 3;
    durability = 8;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::wakizashi;
#endif
}
