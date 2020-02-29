#include "TypeConverter.hpp"

TypeConverter::TypeConverter() {}

void TypeConverter::getCorrectType(BlackCard *card, Personality **person, Holding **hold)
{
	if (card->getType() == PERSONALITY) {
		(*person) = getPersonality(card);
        (*hold) = nullptr;
	}
	else {
		(*hold) = getHolding(card);
        (*person) = nullptr;
	}
}

void TypeConverter::getCorrectType(GreenCard *card, Follower **follow, Item **item)
{
	if (card->getType() == FOLLOWER) {
		(*follow) = getFollower(card);
        (*item) = nullptr;
	}
	else {
		(*item) = getItem(card);
        (*follow) = nullptr;
	}
}

Personality *TypeConverter::getPersonality(BlackCard *d)
{
	if (d->getType() == PERSONALITY)
        return static_cast<Personality *>(d);
    return nullptr;
}

Holding *TypeConverter::getHolding(BlackCard *d)
{
	if (d->getType() == HOLDING)
        return static_cast<Holding *>(d);
    return nullptr;
}

Follower *TypeConverter::getFollower(GreenCard *d)
{
	if (d->getType() == FOLLOWER)
        return static_cast<Follower *>(d);
    return nullptr;
}

Item *TypeConverter::getItem(GreenCard *d)
{
	if (d->getType() == ITEM)
        return static_cast<Item *>(d);
    return nullptr;
}
