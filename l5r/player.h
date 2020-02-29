#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include "game_manager.h"   //included because we want the GamePhase enumeration | TODO: decouple?
#include "DeckBuilder.hpp"

#define NUM_STARTING_HAND 5
#define MAX_HAND 6
#define NUM_PROVINCES 4

using std::list;
using std::string;

class GreenCard;
class BlackCard;
class Personality;
class Holding;
class Stronghold;
class Province;

class Player
{
public:
    Player(int index);
    ~Player();
    void SetupPlayer();
    void StartTurn(GamePhase phase);    //play logic
    void PrintPlayer() const;
    void PrintHandHorizontal() const;
    void PrintHandVertical() const;
    void PrintProvincesHorizontal() const;
    void PrintProvincesVertical() const;
    void PrintHoldings() const;
    void PrintArmy() const;
    void PrintProvincesUnderAttack() const;
    static int CompareHonour(Player* p1, Player* p2)
    {
        return p1->honour > p2->honour;
    }
    vector<Province *> getProvinces() const;
    int getNumberOfProvinces() const;
    int getNumberOfCardsInHand() const;
    int getPlayerIndex() const;
private:
    DeckBuilder builder;    //owns the decks
    list<GreenCard*> *fateDeck;
    list<BlackCard*> *dynastyDeck;
    vector<GreenCard*> hand;
    vector<Province*> provinces;
    vector<Holding*>  holdings;
    vector<Personality*> army;
    Stronghold* stronghold;
    int honour, initialDefence, numberOfProvinces, playerIndex;

    void EndTurn();
    void UntapEverything();
    void DrawFateCard();    //no arguments because I draw from my fateDeck
    void DrawDynastyCard();
    void ReplaceDynastyCard(int i);
    void RevealProvinces();
    int EquipCard(Personality* target, GreenCard* card);    //returns 0 if succesful -1 if not
    int CalculateAvailableMoney() const;
    int TapHoldings(int cost);
    int CalculateArmyPower() const;
    void BuyPersonality(Personality* target);
    void BuyHolding(Holding* target);
    void OptimizeChains();
    void DiscardCard(int index);
    void CleanCasualties(); //used every phase to remove dead/destroyed units/provinces
    string GetInput(string action);
#ifdef GUI_SUPPORT
    typedef void (Player::*PrintGUIFunc)(void);
    friend class GameManager;
    void ClearInputFile();
    void WriteToInputFile(int count, ...);
    void PrintGUIEnemyStats() const;
    void PrintGUIMyStats() const;
    void PrintGUIHoldings() const;
    void PrintGUIArmy() const;
    void PrintGUIUnit(Personality*& p) const;
    void PrintGUIProvinces() const;
    void PrintGUIHand() const;
#endif
};
#endif // PLAYER_H
