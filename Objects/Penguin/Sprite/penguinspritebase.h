#ifndef PENGUINSPRITEBASE_H
#define PENGUINSPRITEBASE_H

#include "../../../canvasobject.h"
#include "../../Constants/constants.h"

class PenguinSpriteBase : public CanvasObject
{
public:
    struct PENGUINSPRITEPROPERTIES : public PROPERTIES {
        PENGUIN::STATE state = PENGUIN::STATE::STANDING;
        PENGUIN::DIRECTION direction = PENGUIN::DIRECTION::S;
    };
    explicit PenguinSpriteBase(CanvasObject* parent = nullptr);

    PENGUIN::DIRECTION getCurrentDirection();
    void setCurrentDirection(PENGUIN::DIRECTION direction);
    PENGUIN::STATE getCurrentState();
    void setCurrentState(PENGUIN::STATE state);

    void initializeFrames(QString filePath, PENGUIN::DIRECTION direction, PENGUIN::STATE state);
    void setCurrentFrames(PENGUIN::DIRECTION direction, PENGUIN::STATE state);

    PENGUIN::STATE getStateFromString(QString string);

private:
    PENGUIN::DIRECTION currentDirection = PENGUIN::DIRECTION::S;
    PENGUIN::STATE currentState = PENGUIN::STATE::STANDING;
};

#endif // PENGUINSPRITEBASE_H
