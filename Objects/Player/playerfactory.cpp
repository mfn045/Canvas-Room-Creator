#include "playerfactory.h"

PlayerFactory::PlayerFactory() {}

PlayerFactory* createPlayerFactory(){
    return new PlayerFactory();
}


PlayerFactory::~PlayerFactory(){
    for(auto i = players.begin(); i != players.end(); i++){
        delete *i;
    }
    players.clear();
}

Player* PlayerFactory::getPlayerByUsername(QString username){
    for(auto i = players.begin(); i != players.end(); i++){
        Player* player = *i;
        if(player->getUsername().toLower() == username.toLower()){
            return player;
        }
    }
    return nullptr;
}
Player* PlayerFactory::getPlayerByID(int playerID){
    for(auto i = players.begin(); i != players.end(); i++){
        Player* player = *i;
        if(player->getID() == playerID){
            return player;
        }
    }
    return nullptr;
}


QList<Player*> PlayerFactory::getPlayers()  {
    return players;
}

Player* PlayerFactory::setActivePlayer(Player* playerObj){
    this->activePlayer = playerObj;
    return this->activePlayer;
}

Player* PlayerFactory::createPlayer(){
    Player* player = new Player;
    players.append(player);
    return player;
}
void PlayerFactory::destroyPlayer(Player* playerObj){
    players.removeOne(playerObj);
    delete playerObj;
}
