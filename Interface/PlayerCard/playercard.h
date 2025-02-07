#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include "../Buttons/BlueRectButton/bluerectbutton.h"
#include "../../widgets/scene.h"
#include "../DialogGrid/dialoggrid.h"
#include "../SvgGridContainer/gridcontainer.h"
#include "../TextLabel/textlabel.h"
#include "../../Objects/Badge/badge.h"
#include "../PlayerCard/Inventory/inventory.h"
#include "../../Objects/Player/player.h"

class PlayerCard : public BlueRectButton
{
public:
    explicit PlayerCard(Scene* scene = nullptr);
    Inventory* getInventory();
    MultiCanvasObject* getBackground();

    Player* setPlayer(Player* player);
    Player* currentPlayer();


private:
    Scene* scene = nullptr;
    DialogGrid* body = nullptr;
    GridContainer* container = nullptr;
    Badge* badge = nullptr;
    TextLabel* username = nullptr;

    MultiCanvasObject* bg = nullptr;

    Inventory* inventory = nullptr;
    Player* player = nullptr;

};

#endif // PLAYERCARD_H
