#include "attacker.h"

Attacker::Attacker(string iName) : Personality(iName)
{
    cost = 5;
    attack = 3;
    defence = 2;
    honour = 2;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::attacker;
#endif
}
