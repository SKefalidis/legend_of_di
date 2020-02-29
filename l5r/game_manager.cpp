#include <iostream>
#include "game_manager.h"
#include "player.h"
#include "province.h"

using namespace std;

GamePhase GameManager::currentPhase = GamePhase::StartingPhase;
vector<Player*> GameManager::players;
int GameManager::currentPlayerIndex = 0;
int GameManager::playerCount = 0;

GameManager::GameManager()
{
    cout << "GameManager created." << endl;
}

GameManager::~GameManager()
{
    for(int i = 0; i < playerCount; i++)    {
        delete players.at(static_cast<size_t>(i));
    }
}

void GameManager::InitializeGameBoard(int numberOfPlayers)
{
    currentPhase = GamePhase::StartingPhase;
    playerCount = numberOfPlayers;
    for(int i = 0; i <numberOfPlayers; i++)
    {
        players.push_back(new Player(i));
        players.at(static_cast<size_t>(i))->SetupPlayer();
    }
    currentPlayerIndex = 0;
    cout << "Game ready to begin." << endl;
}

void GameManager::GamePlay()
{
    cout << "Game starting." << endl;
    SortByHonour();
    players.at(static_cast<size_t>(currentPlayerIndex))->StartTurn(currentPhase);
}

//If two or more players destroy the final provinces at the same time the player with the most honour wins.
int GameManager::CheckWinningCondition()
{
    bool won;

    for(int j = 0; j < players.size(); j++)
    {
        won = true;
        for(int i = 0; i < players.size(); i++)
        {
            if(i != j && players.at(i)->getNumberOfProvinces() > 0)
            {
                won = false;
                break;
            }
        }
        if(won)
            return j;
    }

    return -1;
}

void GameManager::PrintGameStatistics()
{
    for(auto &x : players)
    {
        x->PrintPlayer();
        for(auto &y : x->getProvinces())
            y->Print();
    }
}

void GameManager::PrintArena()
{
    for(auto &x : players)
    {
        x->PrintPlayer();
    }
}

void GameManager::PrintOtherPlayers(Player *exceptThis)
{
    for(auto &x : players)
    {
        if(x != exceptThis)
        {
            x->PrintPlayer();
        }
    }
}

#ifdef GUI_SUPPORT
void GameManager::PrintGUIEnemies(Player *exceptThis)
{
    for(auto &x : players)
    {
        if(x != exceptThis)
        {
            x->PrintGUIEnemyStats();
        }
    }
}
#endif

void GameManager::NextPhase()
{
    SortByHonour();
    if(currentPhase == GamePhase::StartingPhase)
    {
        currentPhase = GamePhase::EquipPhase;
    }else if(currentPhase == GamePhase::EquipPhase)
    {
        currentPhase = GamePhase::BattlePhase;
    }else if(currentPhase == GamePhase::BattlePhase)
    {
        currentPhase = GamePhase::BattlePhase2;
    }else if(currentPhase == GamePhase::BattlePhase2)
    {
        //simulate battles
        for(auto &x : players)
        {
            for(auto &p : x->getProvinces())
            {
                p->SimulateBattle();
            }
        }
        currentPhase = GamePhase::EconomyPhase;
    }
    else if(currentPhase == GamePhase::EconomyPhase)
    {
        currentPhase = GamePhase::EndPhase;
    }
    else if(currentPhase == GamePhase::EndPhase)
    {
        PrintGameStatistics(); //prints provinces, statistics
        for(auto &x : players)
        {
            x->PrintHandHorizontal();
            x->PrintHoldings();
        }
        currentPhase = GamePhase::StartingPhase;
    }
}

//Players play in order of highest to lowest honour. This ranking gets updated every phase.
void GameManager::SortByHonour()
{
    sort(players.begin(), players.end(), Player::CompareHonour);
}

//Next turn.
void GameManager::Next()
{
    int j;
    cout << "Next turn" << endl;
    if((j = CheckWinningCondition()) != -1) //check if the player who called this won
    {
        cout << "Player: " << players.at(j)->getPlayerIndex() << " has won!!!" << endl;
        cout << "Press any button to exit." << endl;
        getchar();
        exit(0);
    }else
    {
        if(++currentPlayerIndex == playerCount) //if all the players have played this phase go the next one
        {
            currentPlayerIndex = 0;
            NextPhase();
        }
        players.at(static_cast<size_t>(currentPlayerIndex))->StartTurn(currentPhase); //Start the turn of the next player
    }
}

int GameManager::getPlayerCount()
{
    return playerCount;
}

vector<Player *> GameManager::getPlayers()
{
    return players;
}
