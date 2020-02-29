#ifndef FARMLAND_H
#define FARMLAND_H

#include "../holding.h"

#define HOLDING_TYPE_FARMLAND "FARMLAND"

class Farmland : public Holding
{
public:
    Farmland(string iName);
};

#endif // FARMLAND_H
