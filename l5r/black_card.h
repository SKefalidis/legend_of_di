#ifndef BLACKCARD_H
#define BLACKCARD_H
#include "card.h"

class BlackCard : public Card
{
protected:
    bool isRevealed;
public:
    BlackCard(string iName);
    virtual int getType() const override;
    virtual void PrintCard() const override;
    virtual void AddToPrintBuffer() const override;
    //getter/setters for isRevealed
    void Reveal(){isRevealed = true;}
    void Hide(){isRevealed = false;}
    bool getIsRevealed() const;

#ifdef GUI_SUPPORT
    virtual void PrintGUICard() const override;
#endif
};

#endif // BLACKCARD_H
