#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "player.h"
#include <QString>

Player* createPlayer();

class PlayerFactory
{
public:

    Player* getPlayerByUsername(QString username);
    Player* getPlayerByID(int playerID);

    Player* createPlayer();
    void destroyPlayer(Player* playerObj);

    Player* setActivePlayer(Player* playerObj);

    QList<Player*> getPlayers();

    PlayerFactory& operator=(const PlayerFactory&) = delete;
    PlayerFactory& operator=(PlayerFactory&&) = delete;

private:
    PlayerFactory();
    ~PlayerFactory();

    QList<Player*> players;

    Player* activePlayer = nullptr;

    PenguinSpriteMoveWorker* moveWorker = nullptr;

    friend PlayerFactory* createPlayerFactory();

};

#endif // PLAYERFACTORY_H
