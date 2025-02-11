#include "penguinspritebase.h"

PenguinSpriteBase::PenguinSpriteBase(AtlasCanvasObject* parent) : AtlasCanvasObject(parent) {}

void PenguinSpriteBase::setCurrentSprite(PENGUIN::DIRECTION direction, PENGUIN::STATE state){
    bool changed = false;
    int frame = -1;
    for(auto i = PENGUIN::spritesMapped.begin(); i != PENGUIN::spritesMapped.end(); i++){
        PENGUIN::SPRITEINFO info = *i;
        if(info.direction == direction && info.state == state){
            frame = i.key();
            AtlasCanvasObject::setCurrentSprite(frame);
            changed = true;
        }
    }
    if(changed){
        this->currentDirection = direction;
        this->currentState = state;
        setFrame(getCurrentFrame());
        QList<QGraphicsItem*> children = childItems();
        for(QGraphicsItem* child : children){
            AtlasCanvasObject* childObj = (AtlasCanvasObject*)child;
            childObj->setCurrentSprite(frame);
            childObj->setFrame(getCurrentFrame());
        }
    }
}

PENGUIN::DIRECTION PenguinSpriteBase::getCurrentDirection(){
    return this->currentDirection;
}

void PenguinSpriteBase::setCurrentDirection(PENGUIN::DIRECTION direction){
    if(direction != this->currentDirection){
        setCurrentSprite(direction,this->currentState);
        setFrame(getCurrentFrame());
        QList<QGraphicsItem*> children = childItems();
        for(QGraphicsItem* child : children){
            PenguinSpriteBase* childObj = (PenguinSpriteBase*)child;
            childObj->setCurrentSprite(direction,this->currentState);
            childObj->setFrame(getCurrentFrame());
        }
    }
}

PENGUIN::STATE PenguinSpriteBase::getCurrentState(){
    return this->currentState;
}

void PenguinSpriteBase::setCurrentState(PENGUIN::STATE state){
    setCurrentSprite(this->currentDirection,state);
    setFrame(getCurrentFrame());
}

PENGUIN::STATE PenguinSpriteBase::getStateFromString(QString string){
    if(string.toLower() == "standing"){
        return PENGUIN::STATE::STANDING;
    } else if(string.toLower() == "walking"){
        return PENGUIN::STATE::WALKING;
    } else if(string.toLower() == "dancing"){
        return PENGUIN::STATE::DANCING;
    } else if(string.toLower() == "sitting"){
        return PENGUIN::STATE::SITTING;
    } else if(string.toLower() == "waving"){
        return PENGUIN::STATE::WAVING;
    }
    return PENGUIN::STATE::UNUSED;
}
