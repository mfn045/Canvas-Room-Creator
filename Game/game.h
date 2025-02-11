#ifndef GAME_H
#define GAME_H

#include "Interface/interface.h"
#include "Objects/Player/playerfactory.h"
#include "SoundManager/soundmanager.h"

Interface* createInterface();
PlayerFactory* createPlayerFactory();

class Game
{
public:
    static Game* getInstance();

    Interface* getInterface();
    PlayerFactory* getPlayerFactory();
    SoundManager* getSoundManager();

    Game& operator =(const Game& game) = delete;
    Game& operator ()(const Game& game) = delete;
    Game& operator ()(const Game&& game) = delete;


private:
    Game() = default;
    Game(const Game&) = default;

    static Game* game;

    Interface* interface = nullptr;

    PlayerFactory* playerFactory = nullptr;

    SoundManager* soundManager = nullptr;

public slots:
    void addToMoveWorker(PenguinSprite* sprite);

};

#endif // GAME_H
