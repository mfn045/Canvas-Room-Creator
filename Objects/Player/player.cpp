#include "player.h"

Player::Player() {
}


Player::~Player(){
    delete penguinSprite;
    delete penguinPaper;
    username = "";
    badge = BADGE::NONE;
    ownedItems.clear();
    friendList.clear();
    ignoreList.clear();
}


QString Player::getUsername(){
    return this->username;
}
QString Player::setUsername(QString username){
    this->username = username;
    return this->username;
}

QList<int> Player::getFriends() const{
    return this->friendList;
}

QList<int> Player::addFriend(int playerId) {
this->friendList.append(playerId);
return this->friendList;
}

QList<int> Player::remFriend(int playerId) {
    this->friendList.removeAll(playerId);
    return this->friendList;
}

QList<int> Player::getIgnoreList() const {
    return this->ignoreList;
}
QList<int> Player::addIgnore(int playerId){
    this->ignoreList.append(playerId);
    return this->friendList;
}
QList<int> Player::remIgnore(int playerId){
    this->ignoreList.removeAll(playerId);
    return this->friendList;
}

int Player::getID(){
    return this->id;
}
int Player::setID(int playerId){
    this->id = playerId;
    return this->id;
}

PENGUIN::BADGE Player::getBadge(){
    return this->badge;
}
PENGUIN::BADGE Player::setBadge(PENGUIN::BADGE badge){
    this->badge = badge;
    return this->badge;
}

QString Player::getColor(){
    return this->color;
}

QString Player::setColor(QString color){
    this->color = color;
    return this->color;
}


QList<int>& Player::getOwnedItems() {
    return this->ownedItems;
}

PenguinSprite* Player::getPenguinSprite(){
    if(this->penguinSprite == nullptr){
        this->penguinSprite = new PenguinSprite();
    }
    return this->penguinSprite;
}

PenguinPaper* Player::getPenguinPaper(){
    if(this->penguinPaper == nullptr){
        this->penguinPaper = new PenguinPaper();
    }
    return this->penguinPaper;
}
