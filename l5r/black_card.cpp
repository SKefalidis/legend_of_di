#include <iostream>
#include <iomanip>
#include <string>
#include "black_card.h"
#include "terminal_colours.h"
#include "assert.h"
#include "printer.h"

using namespace std;

bool BlackCard::getIsRevealed() const
{
    return isRevealed;
}

BlackCard::BlackCard(string iName) : Card(iName)
{
    isRevealed = false;
#ifdef GUI_SUPPORT
    id = IMAGE_FILE_ID::black;
    id_back = IMAGE_FILE_ID::black_card_back;
#endif
}

void BlackCard::PrintCard() const
{
    COLOUR_REGION_RED;
    if(isRevealed)
    {
        Card::PrintCard();
        cout << "|" << setw(CARD_WIDTH - 2) << "Revealed: " + to_string(isRevealed) << "|" << endl;
    }else
    {
        cout << "|";
        for(int i = 0; i < CARD_WIDTH - 2; i++)
            cout << "-";
        cout << "|" << endl;
        cout << "|" << setw(CARD_WIDTH - 2) << "NOT REVEALED" << "|" << endl;
        cout << "|";
        for(int i = 0; i < CARD_WIDTH - 2; i++)
            cout << "-";
        cout << "|" << endl;
    }
}

void BlackCard::AddToPrintBuffer() const
{
    string s;
    if(isRevealed)
    {
        Card::AddToPrintBuffer();
        s = "Revealed: " + to_string(isRevealed) + " |";
        Printer::AddStringToBuffer(s);
        //child cards add more information
    }else
    {
        AddHorizontalBorderToPrintBuffer();
        s = "NOT REVEALED |";
        //No call to Card::AddToPrintBuffer therefore I have to add a bunch of lines.
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
        Printer::AddStringToBuffer(s);
    }
}


#ifdef GUI_SUPPORT
void BlackCard::PrintGUICard() const
{
    if(isRevealed)
    {
        //this should never run, holdings/personalities have their own PrintGUICard methods
        Card::PrintGUICard();
        assert(false);
    }else
    {
        //print a turned down card (id_back)
        ofstream inputFile;
        inputFile.open(INPUT_PATH, ios::out | ios::app);
        inputFile << id_back << " END" << endl;
        inputFile.close();
    }
}
#endif


int BlackCard::getType() const
{
    assert(false);
}
