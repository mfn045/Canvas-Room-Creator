#include "penguinspritebase.h"

PenguinSpriteBase::PenguinSpriteBase(MultiCanvasObject* parent) : MultiCanvasObject(parent) {}

void PenguinSpriteBase::initializeFrames(QString filePath, PENGUIN::DIRECTION direction, PENGUIN::STATE state){
    if(filePath.isEmpty()) return;
    PENGUINSPRITEPROPERTIES* p = nullptr;
    for(PROPERTIES* properties : getFrames().keys()){
        PENGUINSPRITEPROPERTIES* penguinProperties = (PENGUINSPRITEPROPERTIES*) properties;
        if(penguinProperties->direction == direction && penguinProperties->state == state){
            p = (PENGUINSPRITEPROPERTIES*)properties;
        }
    }
    if(p == nullptr){
        p = new PENGUINSPRITEPROPERTIES();
        p->direction = direction;
        p->state = state;
        p->filePath = filePath;
    }
    initFrames(filePath,p);
}

void PenguinSpriteBase::setCurrentFrames(PENGUIN::DIRECTION direction, PENGUIN::STATE state){
    bool changed = false;
    for(PROPERTIES* properties : getFrames().keys()){
        PENGUINSPRITEPROPERTIES* penguinProperties = (PENGUINSPRITEPROPERTIES*) properties;
        if(penguinProperties->direction == direction && penguinProperties->state == state){
            MultiCanvasObject::setCurrentFrames(properties);
            changed = true;
        }
    }
    if(changed){
        this->currentDirection = direction;
        this->currentState = state;
        setFrame(getCurrentFrame());
        QList<QGraphicsItem*> children = childItems();
        for(QGraphicsItem* child : children){
            PenguinSpriteBase* childObj = (PenguinSpriteBase*)child;
            childObj->setCurrentFrames(direction,state);
            childObj->setFrame(getCurrentFrame());
        }
    }
}

PENGUIN::DIRECTION PenguinSpriteBase::getCurrentDirection(){
    return this->currentDirection;
}

void PenguinSpriteBase::setCurrentDirection(PENGUIN::DIRECTION direction){
    if(direction != this->currentDirection){
        setCurrentFrames(direction,this->currentState);
        setFrame(getCurrentFrame());
        QList<QGraphicsItem*> children = childItems();
        for(QGraphicsItem* child : children){
            PenguinSpriteBase* childObj = (PenguinSpriteBase*)child;
            childObj->setCurrentFrames(direction,this->currentState);
            childObj->setFrame(getCurrentFrame());
        }
    }
}

PENGUIN::STATE PenguinSpriteBase::getCurrentState(){
    return this->currentState;
}

void PenguinSpriteBase::setCurrentState(PENGUIN::STATE state){
    setCurrentFrames(this->currentDirection,state);
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
}
