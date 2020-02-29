#ifndef CARD_H
#define CARD_H

#include <iostream>
#define CARD_WIDTH 35 //used for printing

#ifdef GUI_SUPPORT
#include "../image_files_enum.h"
#include <fstream>
#endif

using std::string;

class Card
{
protected:
    string name;
    int cost;
    bool isTapped;
public:
    Card(string iName);
    virtual ~Card(){};
    virtual int getType() const = 0;
    virtual void PrintCard() const;
    virtual void AddToPrintBuffer() const; //add the card to the printBuffer (printer.cpp/h)
    void PrintHorizontalBorder() const; //the top and bottom border of the card
    void AddHorizontalBorderToPrintBuffer() const; //add a border of the card to the printBuffer

    string getName() const;
    bool getIsTapped() const;
    void setIsTapped(bool value);
    int getCost() const;

#ifdef GUI_SUPPORT
    IMAGE_FILE_ID id;
    IMAGE_FILE_ID id_back;
    virtual void PrintGUICard() const;
#endif
};

enum CardType{
    personality = 1,
    holding = 2,
    follower = 3,
    item = 4
};

#endif // CARD_H
