#include "defender.h"

Defender::Defender(string iName)  : Personality(iName)
{
    cost = 5;
    attack = 2;
    defence = 3;
    honour = 2;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::defender;
#endif
}
