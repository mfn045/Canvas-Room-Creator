#include "game.h"

Game* Game::getInstance(){
    if(game == nullptr){
        game = new Game();
    }
    return game;
}

Interface* Game::getInterface(){
    if(this->interface == nullptr){
        this->interface = createInterface();
    }
    return this->interface;
}

PlayerFactory* Game::getPlayerFactory(){
    if(this->playerFactory == nullptr){
        this->playerFactory = createPlayerFactory();
    }
    return this->playerFactory;
}

SoundManager* Game::getSoundManager(){
    if(this->soundManager == nullptr){
        this->soundManager = new SoundManager();
    }
    return this->soundManager;
}

Game* Game::game = nullptr;
