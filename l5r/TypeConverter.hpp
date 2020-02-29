#ifndef _TYPECONVERTER_HPP_
#define _TYPECONVERTER_HPP_

#define PERSONALITY 1
#define HOLDING 2
#define FOLLOWER 3
#define ITEM 4

#include "black_card.h"
#include "green_card.h"
#include "personality.h"
#include "holding.h"
#include "follower.h"
#include "item.h"

class TypeConverter
{
public:
	TypeConverter();
	void getCorrectType(BlackCard *card, Personality **person, Holding **hold);
	void getCorrectType(GreenCard *card, Follower **follow, Item **item);
	Personality *getPersonality(BlackCard *d);
	Holding *getHolding(BlackCard *d);
	Follower *getFollower(GreenCard *d);
	Item *getItem(GreenCard *d);
};

#endif
