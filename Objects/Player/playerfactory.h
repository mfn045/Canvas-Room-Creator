#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "player.h"
#include <QString>

class PlayerFactory
{
public:
    explicit PlayerFactory();
    ~PlayerFactory();

    Player* getPlayerByUsername(QString username);
    Player* getPlayerByID(int playerID);

    Player* createPlayer();
    void destroyPlayer(Player* playerObj);


    QList<Player*> getPlayers();



private:
    QList<Player*> players;

    Player* activePlayer = nullptr;
};

#endif // PLAYERFACTORY_H
