#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "../Penguin/Sprite/penguinsprite.h"
#include "../Penguin/Paper/penguinpaper.h"
#include "../Constants/constants.h"
#include "../Badge/badge.h"

class Player
{
public:
    explicit Player();

    QString getUsername();
    QString setUsername(QString username);

    QList<int>& getFriends() const;
    QList<int>& addFriend(int playerId) const;
    QList<int>& remFriend(int playerId) const;

    QList<int>& getIgnoreList() const;
    QList<int>& addIgnore(int playerId) const;
    QList<int>& remIgnore(int playerId) const;

    int getID();
    int setID(int playerId);

    PENGUIN::BADGE getBadge();
    PENGUIN::BADGE setBadge(PENGUIN::BADGE badge);

    PenguinSprite& getPenguinSprite();

    PenguinPaper& getPenguinPaper();

private:
    QString username = "";

    int id = -1;

    PENGUIN::BADGE badge = PENGUIN::BADGE::PLAYER;

    QList<int> friendList;
    QList<int> ignoreList;

    PenguinSprite* penguinSprite;

    std::unique_ptr<PenguinPaper> penguinPaper;

};

#endif // PLAYER_H
