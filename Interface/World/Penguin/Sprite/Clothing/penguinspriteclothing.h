#ifndef CLOTHINGITEM_H
#define CLOTHINGITEM_H

#include "Interface/World/Penguin/Sprite/penguinspritebase.h"
#include "Objects/Constants/constants.h"

using namespace PENGUIN;

class PenguinSpriteClothing : public PenguinSpriteBase
{
public:

    explicit PenguinSpriteClothing(AtlasCanvasObject* parent = nullptr);

};

#endif // CLOTHINGITEM_H
