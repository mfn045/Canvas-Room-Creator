#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include "../Buttons/BlueRectButton/bluerectbutton.h"
#include "../../widgets/scene.h"
#include "../DialogGrid/dialoggrid.h"
#include "../SvgGridContainer/gridcontainer.h"
#include "../TextLabel/textlabel.h"
#include "../../Objects/Penguin/Paper/penguinpaper.h"
#include "../../Objects/Badge/badge.h"
#include "../PlayerCard/Inventory/inventory.h"

class PlayerCard : public BlueRectButton
{
public:
    explicit PlayerCard(Scene* scene = nullptr);
    Inventory* getInventory();


private:
    Scene* scene = nullptr;
    PenguinSprite* penguin = nullptr;
    DialogGrid* body = nullptr;
    GridContainer* container = nullptr;
    Badge* badge = nullptr;
    TextLabel* username = nullptr;
    PenguinPaper* penguin_paper = nullptr;
    Inventory* inventory = nullptr;

};

#endif // PLAYERCARD_H
