#ifndef PLAYER_H
#define PLAYER_H

#include "../Penguin/Sprite/penguinsprite.h"
#include "../Penguin/Paper/penguinpaper.h"
#include "../Constants/constants.h"

class Player
{
public:
    QString getUsername();
    QString setUsername(QString username);

    QList<int> getFriends() const;
    QList<int> addFriend(int playerId);
    QList<int> remFriend(int playerId);

    QList<int> getIgnoreList() const;
    QList<int> addIgnore(int playerId);
    QList<int> remIgnore(int playerId);


    QList<int>& getOwnedItems();

    int getID();
    int setID(int playerId);

    PENGUIN::BADGE getBadge();
    PENGUIN::BADGE setBadge(PENGUIN::BADGE badge);

    QString getColor();
    QString setColor(QString color);

    PenguinSprite* getPenguinSprite();

    PenguinPaper* getPenguinPaper();

    Player& operator=(const Player&) = delete;
    Player& operator=(Player&&) = delete;

private:
    Player();
    ~Player();

    QString username = "";

    int id = -1;

    QString color = "";

    PENGUIN::BADGE badge = PENGUIN::BADGE::PLAYER;

    QList<int> friendList;
    QList<int> ignoreList;
    QList<int> ownedItems;

    PenguinSprite* penguinSprite = nullptr;

    PenguinPaper* penguinPaper = nullptr;

    friend class PlayerFactory;

};

#endif // PLAYER_H
