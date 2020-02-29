#include <iostream>
#include <algorithm>
#include <string>
#include "player.h"
#include "card.h"
#include "province.h"
#include "Holdings/holdings.h"
#include "Personalities/personalities.h"
#include "game_manager.h"
#include "TypeConverter.hpp"
#include "printer.h"
#include "assert.h"

#ifdef GUI_SUPPORT
#include <fstream>
#include <cstdarg>
#include "../image_files_enum.h"
#endif

using namespace std;

//Used by both StartTurn() and GetInput()
string input = "";

//The constructor initializes what will be needed for sure.
Player::Player(int index)
{
    fateDeck = builder.createFateDeck();
    builder.deckShuffler(fateDeck);
    dynastyDeck = builder.createDynastyDeck();
    builder.deckShuffler(dynastyDeck);
    playerIndex = index;
    numberOfProvinces = 0;
    stronghold = nullptr;
}

Player::~Player()
{
    if(stronghold != nullptr)
        delete stronghold;
    for(int i = 0, j = provinces.size(); i < j; i++){
        delete provinces.at(i);
    }
    for(int i = 0, j = hand.size(); i < j; i++){
        delete hand.at(i);
    }
}

//Complements the constructor, can be changed to change the game rules.
void Player::SetupPlayer()
{
    //Choose stronghold;
    GreatCity city("Kyoto");
    GreatCastle castle("Osaka");
    GreatPort port("Tokyo");
    cout << "PLAYER " << playerIndex << " SETTING UP." << endl;
    city.PrintCard();
    castle.PrintCard();
    port.PrintCard();
#ifdef GUI_SUPPORT
    ClearInputFile();
    city.PrintGUICard();
    castle.PrintGUICard();
    port.PrintGUICard();
#endif
    input = GetInput("CHOOSE_STRONGHOLD");
    if(input == "1")
    {
        stronghold = new GreatCity("Kyoto");
    }else if(input == "2")
    {
        stronghold = new GreatCastle("Osaka");
    }else
    {
        stronghold = new GreatPort("Tokyo");
    }
    holdings.push_back(stronghold);
    honour = stronghold->getHonour();
    initialDefence = stronghold->getInitialDefence();
    //Draw green cards
    for(int i = 0; i < NUM_STARTING_HAND; i++)
    {
        DrawFateCard();
    }
    //Create/Place provinces/black cards and set their defence.
    numberOfProvinces = NUM_PROVINCES;
    provinces.push_back(new Province("Northern Province"));
    provinces.push_back(new Province("Southern Province"));
    provinces.push_back(new Province("Western Province"));
    provinces.push_back(new Province("Eastern Province"));
    for(int i = 0; i < numberOfProvinces; i++)
    {
        DrawDynastyCard();
        provinces.at(i)->setStaticDefence(initialDefence);
    }
}

/* Player turn logic.
 * In the Starting Phase the player does nothing.
 * In the Equipment Phase the player can choose green cards from his hand to equip to his army.
 * The Battle Phase is split in two parts. In the first part the player
 * chooses whether to attack or defend (decides multiple times, once for every unit).
 * In the second part the player uses his remaining units to defend against attacking armies.
 * When the BattlePhase ends, the battles are simulated.
 * In the Economy Phase the player buys black cards.
 * In the Final Phase the player discards surplus cards.
 * In some instances the game will automatically skip the player's turn because he is unable to do anything.
 * e.g. BattlePhase is skipped when the player has no army
 *
 * When input is required GetInput(string) is called. GetInput takes care of handling bad input (in most cases at least).
 * GUI: If GUI_SUPPORT is enabled the current information on the board is written in a file everytime something changes.
 * The gui application then reads that file and updates it's representation of the board.
 */
void Player::StartTurn(GamePhase phase)
{
    cout << "Player: " << playerIndex << " playing." << endl;
    CleanCasualties();
    if(phase == GamePhase::StartingPhase)
    {
        cout << "Starting phase" << endl;
        DrawFateCard();
        UntapEverything();
        RevealProvinces();
        PrintHandHorizontal();
        PrintProvincesHorizontal();
    #ifdef GUI_SUPPORT
        ClearInputFile();
        WriteToInputFile(2, &Player::PrintGUIHand, &Player::PrintGUIProvinces);
    #endif
    }else if(phase == GamePhase::EquipPhase)
    {
        TypeConverter tc;
        GreenCard *greenChosen;
        int cardChosen;
        Personality* unitChosen;
        Item** itemBought = new Item*;
        Follower** followerBought = new Follower*;

        //If you have an army, select a card from your hand. If you have enough money select a unit to equip that card to.
        //If you have enough money for an upgrade chooose whether you want the upgrade.
        //If the unit is able to equip the card (honour/space requirements met) equip the card.
        //Tap provinces to cover the cost.
        cout << "Equip phase" << endl;
        if(army.size() > 0)
        {
            while(true)
            {
                PrintHandHorizontal();
                PrintArmy();
                #ifdef GUI_SUPPORT
                    ClearInputFile();
                    WriteToInputFile(2, &Player::PrintGUIHand, &Player::PrintGUIArmy);
                #endif
                input = GetInput("SELECT_EQUIPMENT");
                if(input == "N")
                    break;
                cardChosen = stoi(input);
                greenChosen = hand.at(cardChosen);
                if(hand.at(cardChosen)->getCost() <= CalculateAvailableMoney())
                {
                    tc.getCorrectType(hand.at(stoi(input)), followerBought, itemBought);
                    input = GetInput("SELECT_UNIT");
                    if(input == "N")
                        break;
                    unitChosen = army.at(stoi(input));
                    if(hand.at(cardChosen)->getCost() + hand.at(cardChosen)->getEffectCost() <= CalculateAvailableMoney())
                    {
                        input = GetInput("BUY_UPGRADE");
                        {
                            if(input == "Y")
                            {
                                   hand.at(cardChosen)->Upgrade();
                            }
                        }
                    }
                    if(*followerBought != nullptr)
                    {
                        if(unitChosen->AddFollower(*followerBought) == 0)
                        {
                            hand.erase(hand.begin() + cardChosen);
                        }else
                        {
                            //the chosen unit does not have enough honour/space
                            continue;
                        }
                    }
                    else
                    {
                        if(unitChosen->AddItem(*itemBought) == 0)
                        {
                            hand.erase(hand.begin() + cardChosen);
                        }else
                        {
                            //the chosen unit does not have enough honour/space
                            continue;
                        }
                    }
                    TapHoldings(greenChosen->getCost());
                }
            }
        }else
        {
            cout << "Can't do anything in the Equipment phase. Skipping..." << endl;
            EndTurn();
        }
    }else if(phase == GamePhase::BattlePhase)
    {
        Player *target;
        cout << "Battle phase" << endl;

        //if the player has an army, give him the choice described above.
        //if the player chooses a unit to attack that unit is added as an attacker to the province
        //that is it's target, after that in the battle simulation each province checks the attackers/defenders
        //and simulates the battle
        if(army.size() > 0)
        {
        #ifdef GUI_SUPPORT
            ClearInputFile();
            WriteToInputFile(1, &Player::PrintArmy);
        #endif
            //for every untapped personality
            for(auto &x : army)
            {
                if(x->getIsTapped() == false)
                {
                    x->PrintCard();
                #ifdef GUI_SUPPORT
                    ClearInputFile();
                    WriteToInputFile(1, &Player::PrintGUIArmy); //only functions with no arguments
                    Player::PrintGUIUnit(x);
                #endif
                    //select attack or defend
                    input = GetInput("ATTACK_DEFEND");
                    if(input == "ATTACK")
                    {
                        GameManager::PrintArena();
                        //select player to attack
                        input = GetInput("SELECT_PLAYER");
                        cout << "Attacking player: " << input << endl;
                        target = GameManager::getPlayers().at(stoi(input));
                        //select province
                        target->PrintProvincesHorizontal();
                        input = GetInput("SELECT_TARGET_PROVINCE_ATTACK");
                        //assign target to unit
                        target->provinces.at(stoi(input))->AddAttacker(x);
                        x->setIsTapped(true);
                        //notify target player that his province an attack force is on it's way
                    }else
                    {
                        //Do nothing. You will assign defences on the second part of the Battle Phase.
                    }
                }
            }
        }else
        {
            cout << "Can't do anything in the Battle phase. Skipping..." << endl;
            EndTurn();
        }
    }else if(phase == GamePhase::BattlePhase2)
    {
        PrintProvincesUnderAttack();
        for(auto &x : army)
        {
            if(x->getIsTapped() == false)
            {
                //select province
                this->PrintProvincesHorizontal();
                input = GetInput("SELECT_TARGET_PROVINCE_DEFEND");
                //assign target to unit
                this->provinces.at(stoi(input))->AddDefender(x);
                x->setIsTapped(true);
            }
        }
    }else if(phase == GamePhase::EconomyPhase)
    {
        TypeConverter tc;
        Holding** holdingBought = new Holding*;
        Personality** personalityBought = new Personality*;

        cout << endl << "ECONOMY PHASE" << endl;
        while(input != "N")
        {
            cout << "Available money: " << CalculateAvailableMoney() << endl;
            PrintProvincesHorizontal();
        #ifdef GUI_SUPPORT
            ClearInputFile();
            WriteToInputFile(1, &Player::PrintGUIProvinces);
        #endif
            input = GetInput("BUY_BLACK");
            if(input == "N")
                break;
            if(provinces.at(stoi(input))->card->getIsRevealed() == true && provinces.at(stoi(input))->card->getCost() <= CalculateAvailableMoney()) //is there enough money, is the card revealed?
            {
                TapHoldings(provinces.at(stoi(input))->card->getCost());
                tc.getCorrectType(provinces.at(stoi(input))->card, personalityBought, holdingBought);
                if(*personalityBought != nullptr)
                {
                    BuyPersonality(*personalityBought);
                }
                else
                {
                    BuyHolding(*holdingBought);
                }
                cout << input << " bought." << endl;
                ReplaceDynastyCard(stoi(input)); //draw a new black card to replace the on the player bought
            }
        }
    }else if(phase == GamePhase::EndPhase)
    {
        cout << "End phase" << endl;
        while(hand.size() > MAX_HAND)
        {
            PrintHandHorizontal();
        #ifdef GUI_SUPPORT
            ClearInputFile();
            WriteToInputFile(1, &Player::PrintGUIHand);
        #endif
            input = GetInput("DISCARD");
            DiscardCard(stoi(input));
        }
        PrintHandHorizontal();
    #ifdef GUI_SUPPORT
        ClearInputFile();
        WriteToInputFile(1, &Player::PrintGUIHand);
    #endif
    }else
    {
        cout << "Error: Invalid phase." << endl;
        assert(false);
    }
    if(input != "N")
        input = GetInput("NEXT_TURN");
    input = "";
    EndTurn();
}

//Call GameManager::Next()
void Player::EndTurn()
{
    GameManager::Next();
}

//Untaps all the player's cards. Called at the beggining of every round.
void Player::UntapEverything()
{
    for(auto &x : holdings)
    {
        x->setIsTapped(false);
    }
    for(auto &x : army)
    {
        x->setIsTapped(false);
    }
    for(auto &x : hand)
    {
        x->setIsTapped(false);
    }
}

void Player::DrawFateCard()
{
    GreenCard* card;
    if(fateDeck->size() > 0)
    {
        card = fateDeck->front();
        fateDeck->remove(card);
        hand.push_back(card);
    }else
    {
        cout << "You have run out of fate cards." << endl;
    }
}

void Player::DrawDynastyCard()
{
    BlackCard* card;
    if(dynastyDeck->size() > 0)
    {
        card = dynastyDeck->front();
        dynastyDeck->remove(card);
        for(auto &x : provinces)
        {
            if(x->getIsDestroyed() == false && x->card == nullptr)
            {
                x->card = card;
                break;
            }
        }
    }else
    {
        cout << "You have run out of dynasty cards." << endl;
    }
}

//Draws a dynasty card to replace a used dynasty card. Called in the EconomyPhase.
void Player::ReplaceDynastyCard(int i)
{
    BlackCard* card;
    if(dynastyDeck->size() > 0){
        card = dynastyDeck->front();
        dynastyDeck->remove(card);
        provinces.at(static_cast<size_t>(i))->card = card;
    }else{
        cout << "You have run out of dynasty cards." << endl;
    }
}

void Player::RevealProvinces()
{
    for(auto &x : provinces)
    {
        x->card->Reveal();
    }
}

int Player::CalculateAvailableMoney() const
{
    int money = 0;
    for(auto &x : holdings)
    {
        if(x->getIsTapped() == false)
        {
            money += x->getHarvestValue();
        }
    }
    return money;
}

//Tap holdings until the cost is covered (surplus money will be lost).
int Player::TapHoldings(int cost)
{
    string input = "";
    int valueTapped = 0;
    while(valueTapped < cost)
    {
        cout << "Remaining cost: " << cost - valueTapped << endl;
        #ifdef GUI_SUPPORT
            ClearInputFile();
            WriteToInputFile(1, &Player::PrintGUIHoldings);
        #endif
        PrintHoldings();
        input = GetInput("TAP_HOLDINGS");
        if(holdings.at(stoi(input))->getIsTapped() == false)
        {
            valueTapped += holdings.at(stoi(input))->getHarvestValue();
            holdings.at(stoi(input))->setIsTapped(true);
        }
    }
    return valueTapped;
}

int Player::CalculateArmyPower() const
{
    int power = 0;
    for(auto &x : army)
    {
        power += x->getAttack() + x->getDefence();
    }
    return power;
}

void Player::BuyPersonality(Personality *target)
{
    army.push_back(target);
    PrintArmy();
}

void Player::BuyHolding(Holding *target)
{
    holdings.push_back(target);
    OptimizeChains();
    PrintHoldings();
}

/* Used to chain mines for extra money.
 * Goes through every holding. If the current holding is one of the mines (and it has empty chain positions):
 * look for another mine (of the correct type) to chain.
 * otherwise continue
 */
void Player::OptimizeChains()
{
    //foreach holding
    for(auto &x : holdings)
    {
        HOLDING_TYPE hType = x->getHoldingType();
        if(hType == HOLDING_TYPE_MINE || hType == HOLDING_TYPE_GMINE || hType == HOLDING_TYPE_CMINE) //if x one of the mines
        {
            HOLDING_TYPE uType = x->getUpperHoldingType();
            HOLDING_TYPE sType = x->getSubHoldingType();
            Holding* uHolding = x->getUpperHolding();
            Holding* sHolding = x->getSubHolding();

            if(uType != HOLDING_TYPE_NONE && uHolding == nullptr) //if x has an empty upper holding slot
            {
                //search for correct upper holding with empty sub holding
                for(auto &y : holdings)
                {
                    if(y->getSubHoldingType() == hType && y->getSubHolding() == nullptr)
                    {
                        x->SetUpperHolding(y); //also takes care of making x subholding of y
                    }
                }
            }
            if(sType != HOLDING_TYPE_NONE && sHolding == nullptr) //if x has an empty sub holding slot
            {
                //search for correct sub holding with empty upper holding
                for(auto &y : holdings)
                {
                    if(y->getUpperHoldingType() == hType && y->getUpperHolding() == nullptr)
                    {
                        x->SetSubHolding(y); //also takes care of making x upperholding of y
                    }
                }
            }
        }else
        {
            continue;
        }
    }
    //Look for complete connections.
    for(auto &x : holdings)
    {
        HOLDING_TYPE hType = x->getHoldingType();
        if(hType == HOLDING_TYPE_CMINE)
        {
            CrystalMine* cm = static_cast<CrystalMine*>(x);
            cm->CheckCompleteConnection();
        }
    }
}

void Player::DiscardCard(int index)
{
    hand.erase(hand.begin() + index);
}

//Removes dead units and destroyed provinces. Runs at the beginning of every turn.
void Player::CleanCasualties()
{
    for(int i = 0; i < provinces.size(); i++)
    {
        if(provinces.at(i)->getIsDestroyed())
        {
            delete provinces.at(i);
            provinces.erase(provinces.begin() + i);
            numberOfProvinces--;
            i--;
        }
    }

    for(int i = 0; i < army.size(); i++)
    {
        if(army.at(i)->getIsDead())
        {
            army.erase(army.begin() + i);
            i--;
        }else
        {
            army.at(i)->CleanCasualties();
        }
    }
}

/* Gets input from the player.
 * This function guarantees tha the input will be valid.
 * 'action' is the action that the player has to give input for.
 */
string Player::GetInput(string action)
{
    string input = "";
    //Preparation phase (choose stronghold).
    if(action == "CHOOSE_STRONGHOLD")
    {
        //The player must choose one of three strongholds.
        do
        {
            cout << "Input a number to choose a stronghold. (1,2,3): ";
            cin >> input;
            cout << endl;
        } while(input != "1" && input != "2" && input != "3");
    }else if(action == "DISCARD")
    {
        while(true){
            try {
                do {
                    cout << "Choose a card to discard. (Input a number, 0-" << hand.size() - 1 << "): " ;
                    cin >> input;
                    cout << endl;
                } while(stoi(input) < 0 || stoi(input) >= hand.size());
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "BUY_BLACK")
    {
        while(true){
            try {
                do {
                    cout << "Choose a card to purchase. (Input a number, 0-" << numberOfProvinces - 1 << ", or 'N' to end your turn): " ;
                    cin >> input;
                    cout << endl;
                    if(input == "N" || input == "n") {
                        transform(input.begin(), input.end(), input.begin(), ::toupper); //transform the string to upper case
                        break;
                    }
                } while(stoi(input) < 0 || stoi(input) >= numberOfProvinces);
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "TAP_HOLDINGS")
    {
        while(true){
            try {
                do {
                    cout << "Choose a holding to tap. (Input a number 0-" << holdings.size() - 1 << "): " ;
                    cin >> input;
                    cout << endl;
                } while(stoi(input) < 0 || stoi(input) >= holdings.size());
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "SELECT_EQUIPMENT")
    {
        while(true){
            try {
                do {
                    cout << "Choose a card from your hand to equip. (Input a number 0-" << hand.size() - 1 << ", or 'N' to end your turn): " ;
                    cin >> input;
                    cout << endl;
                    if(input == "N" || input == "n") {
                        transform(input.begin(), input.end(), input.begin(), ::toupper); //transform the string to upper case
                        break;
                    }
                } while(stoi(input) < 0 || stoi(input) >= hand.size());
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "SELECT_UNIT")
    {
        while(true){
            try {
                do {
                    cout << "Choose a unit to equip. (Input a number 0-" << army.size() - 1 << ", or 'N' to end your turn): " ;
                    cin >> input;
                    cout << endl;
                } while(stoi(input) < 0 || stoi(input) >= army.size());
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }
    else if(action == "ATTACK_DEFEND")
    {
        do
        {
            cout << "Do you want this card to attack or defend? (ATTACK/DEFEND)";
            cin >> input;
            cout << endl;
            transform(input.begin(), input.end(), input.begin(), ::toupper); //transform the string to upper case
        }while(input != "ATTACK" && input != "DEFEND");
    }else if(action == "SELECT_PLAYER")
    {
        while(true){
            try {
                do {
                    cout << "Choose a player to attack. (Input a number 0-" << GameManager::getPlayerCount() - 1 << "): " ;
                    cin >> input;
                    cout << endl;
                } while((stoi(input) < 0 || stoi(input) >= GameManager::getPlayerCount()) || GameManager::getPlayers().at(stoi(input))->playerIndex == playerIndex);
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "SELECT_TARGET_PROVINCE_ATTACK")
    {
        Player* target = GameManager::getPlayers().at(stoi(::input));
        while(true){
            try {
                do {
                    cout << "Select a province to target: (Input a number 0-" << target->numberOfProvinces - 1 << "): ";
                    cin >> input;
                    cout << endl;
                } while(stoi(input) < 0 || stoi(input) >= target->numberOfProvinces);
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "SELECT_TARGET_PROVINCE_DEFEND")
    {
        Player* target = this;
        while(true){
            try {
                do {
                    cout << "Select a province to target: (Input a number 0-" << target->numberOfProvinces - 1 << "): ";
                    cin >> input;
                    cout << endl;
                } while(stoi(input) < 0 || stoi(input) >= target->numberOfProvinces);
                break;
            } catch (std::invalid_argument) {
                cout << "The given input is not a number (numbers should be entered using digits)." << endl;
            }
        }
    }else if(action == "BUY_UPGRADE")
    {
        do {
            cout << "Do you want to upgrade the card? (Y/N)";
            cin >> input;
            cout << endl;
            transform(input.begin(), input.end(), input.begin(), ::toupper); //transform the string to upper case
        } while(input != "Y" && input != "N");
    } else if(action == "NEXT_TURN")
    {
        do
        {
            cout << "Enter 'N' to end your turn." << endl;
            cin >> input;
            cout << endl;
            transform(input.begin(), input.end(), input.begin(), ::toupper); //transform the string to upper case
        }while(input != "N");
    }
    else
    {
        //not implemented yet
        assert(false);
    }
    return input;
}

void Player::PrintPlayer() const
{
    cout << "Player: " << playerIndex << endl;
    cout << "Honour: " << honour << endl;
    cout << "Provinces: " << numberOfProvinces << endl;
    cout << "Cards in hand: " << hand.size() << endl;
    cout << "Income: " << CalculateAvailableMoney() << endl;
    cout << "Army power: " << CalculateArmyPower() << endl;
    cout << "--------------------" << endl;
    cout << "--------------------" << endl;
}

void Player::PrintHandVertical() const
{
    for(auto &x : hand)
    {
        x->PrintCard();
    }
}

void Player::PrintHandHorizontal() const
{
    Printer::setVerticalLength(13); //12(card vertical size) + 1 (the number to select)
    Printer::setWidth(CARD_WIDTH);
    for(int i = 0; i < hand.size(); i++)
    {
        auto& x = hand.at(i);
        Printer::AddStringToBuffer(to_string(i));
        x->AddToPrintBuffer();
    }
    Printer::PrintBuffer("GREEN");
}

void Player::PrintProvincesVertical() const
{
    for(auto &x : provinces)
    {
        x->card->PrintCard();
    }
}

void Player::PrintProvincesHorizontal() const
{
    Printer::setVerticalLength(11); //9(card vertical size) + 1 (province name) + 1 (the number to select)
    Printer::setWidth(CARD_WIDTH);
    for(int i = 0; i < provinces.size(); i++)
    {
        auto& x = provinces.at(i);
        Printer::AddStringToBuffer(to_string(i));
        x->AddToPrintBuffer();
    }
    Printer::PrintBuffer("RED");
}

void Player::PrintHoldings() const
{
    for(auto &x : holdings)
    {
        x->PrintCard();
    }
}

void Player::PrintArmy() const
{
    cout << "YOUR ARMY CONTAINS THE FOLLOWING TROOPS: " << endl;
    Printer::setVerticalLength(10); //9(card vertical size) + 1 (the number to select)
    Printer::setWidth(CARD_WIDTH);
    for(int i = 0; i < army.size(); i++)
    {
        auto& x = army.at(i);
        Printer::AddStringToBuffer(to_string(i));
        x->AddToPrintBuffer();
    }
    Printer::PrintBuffer("RED");
}

void Player::PrintProvincesUnderAttack() const
{
    cout << "Provinces under attack: " << endl;
    for(auto &x : provinces)
    {
        if(x->getAttackers().size() > 0)
        {
            x->Print();
            cout << "Number of attacking units: " << x->getAttackers().size() << endl;
        }
    }
}

vector<Province *> Player::getProvinces() const
{
    return provinces;
}

int Player::getNumberOfProvinces() const
{
    int i = 0;
    for(auto &x: provinces){
        if(x->getIsDestroyed() == false)
            i++;
    }
    return i;
}

int Player::getNumberOfCardsInHand() const
{
    return hand.size();
}

int Player::getPlayerIndex() const
{
    return playerIndex;
}

#ifdef GUI_SUPPORT
void Player::ClearInputFile()
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH);
    inputFile.close();
}

void Player::WriteToInputFile(int count, ...)
{
    GameManager::PrintGUIEnemies(this);
    PrintGUIMyStats();
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; i++)
    {
        PrintGUIFunc func = va_arg(args, PrintGUIFunc);
        (this->*func)(); //C++ magic, ->* has lower precedence than ()!
    }
    va_end(args);
}

void Player::PrintGUIEnemyStats() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    inputFile << "PLAYER " << honour << " " << CalculateArmyPower() << " " << CalculateAvailableMoney() << " " << hand.size() << " " << numberOfProvinces << endl;
    PrintGUIProvinces();
    inputFile.close();
}

void Player::PrintGUIMyStats() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    inputFile << "THIS_PLAYER " << honour << " " << CalculateArmyPower() << " " << CalculateAvailableMoney() << " " << hand.size() << " " << numberOfProvinces << endl;
    inputFile.close();
}

void Player::PrintGUIHoldings() const
{

    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app); //append
    for(auto &x : holdings)
    {
        x->PrintGUICard();
    }
    inputFile << endl;
    inputFile.close();
}

void Player::PrintGUIArmy() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    for(auto &x : army)
    {
        x->PrintGUICard();
    }
    inputFile << endl;
    inputFile.close();
}

void Player::PrintGUIUnit(Personality*& p) const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    p->PrintGUICard();
    inputFile << endl;
    inputFile.close();
}

void Player::PrintGUIProvinces() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app); //append
    for(auto &x : provinces)
    {
        x->card->PrintGUICard();

    }
    inputFile << endl;
    inputFile.close();
}

void Player::PrintGUIHand() const
{
    ofstream inputFile;
    inputFile.open(INPUT_PATH, ios::out | ios::app);
    for(int i = 0; i < hand.size(); i++)
    {
        auto& x = hand.at(i);
        inputFile << x->id << " Cost: " << x->getCost() << " AttackBonus: " << x->getAttackBonus() << " DefenceBonus: " << x->getDefenceBonus() << " END" << endl;
    }
    inputFile << endl;
    inputFile.close();
}
#endif
