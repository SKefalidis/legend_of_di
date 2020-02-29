#include <iomanip>
#include <string>
#include "printer.h"
#include "card.h"

using namespace std;

Card::Card(string iName)
{
    this->name = iName;
    cost = -1;
    isTapped = true;
}

void Card::PrintCard() const
{
    PrintHorizontalBorder();
    cout << "|" << setw(CARD_WIDTH - 2) << "Name: " + name << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "Tapped: " + to_string(isTapped) << "|" << endl;
    cout << "|" << setw(CARD_WIDTH - 2) << "Cost: " + to_string(cost) << "|" << endl;
}

void Card::AddToPrintBuffer() const
{
    string s = "";
    AddHorizontalBorderToPrintBuffer();
    s = "Name: " + name + " |";
    Printer::AddStringToBuffer(s);
    s = "Tapped: " + to_string(isTapped) + " |";
    Printer::AddStringToBuffer(s);
    s = "Cost: " + to_string(cost) + " |";
    Printer::AddStringToBuffer(s);
}

void Card::AddHorizontalBorderToPrintBuffer() const
{
    string s = "";
    for(int i = 0; i < CARD_WIDTH - 1; i++) //-1 because I add a | in front of every line in the Printer
    {
        s += "-";
    }
    Printer::AddStringToBuffer(s);
}

void Card::PrintHorizontalBorder() const
{
    for(int i = 0; i < CARD_WIDTH; i++)
    {
        cout << "-";
    }
    cout << endl;
}

string Card::getName() const
{
    return name;
}

bool Card::getIsTapped() const
{
    return isTapped;
}

void Card::setIsTapped(bool value)
{
    isTapped = value;
}

int Card::getCost() const
{
    return cost;
}

#ifdef GUI_SUPPORT
void Card::PrintGUICard() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    inputFile << id /*<< " Name: " << name */<< " Cost: " << cost << " END" << endl;
    inputFile.close();
}
#endif
