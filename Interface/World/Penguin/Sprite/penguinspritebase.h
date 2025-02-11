#ifndef PENGUINSPRITEBASE_H
#define PENGUINSPRITEBASE_H

#include "Interface/Common/CanvasObject/Atlas/atlascanvasobject.h"
#include "Objects/Constants/constants.h"

class PenguinSpriteBase : public AtlasCanvasObject
{
public:
    /*struct PENGUINSPRITEPROPERTIES : public PROPERTIES {
        PENGUIN::STATE state = PENGUIN::STATE::STANDING;
        PENGUIN::DIRECTION direction = PENGUIN::DIRECTION::S;
    };*/
    explicit PenguinSpriteBase(AtlasCanvasObject* parent = nullptr);

    PENGUIN::DIRECTION getCurrentDirection();
    void setCurrentDirection(PENGUIN::DIRECTION direction);

    PENGUIN::STATE getCurrentState();
    void setCurrentState(PENGUIN::STATE state);

    void setCurrentSprite(PENGUIN::DIRECTION direction, PENGUIN::STATE state);

    PENGUIN::STATE getStateFromString(QString string);

private:
    PENGUIN::DIRECTION currentDirection = PENGUIN::DIRECTION::S;
    PENGUIN::STATE currentState = PENGUIN::STATE::STANDING;
};

#endif // PENGUINSPRITEBASE_H
