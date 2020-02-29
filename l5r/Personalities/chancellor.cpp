#include "chancellor.h"

Chancellor::Chancellor(string iName)  : Personality(iName)
{
    cost = 15;
    attack = 5;
    defence = 10;
    honour = 8;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::chancellor;
#endif
}
