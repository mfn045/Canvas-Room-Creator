#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include "Interface/Widgets/Buttons/BlueRectButton/bluerectbutton.h"
#include "AbstractQtWidgets/scene.h"
#include "Interface/Widgets/BackgroundContainer/backgroundcontainer.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Common/TextLabel/textlabel.h"
#include "Interface/Widgets/PlayerCard/Inventory/inventory.h"
#include "Interface/Widgets/PlayerCard/Badge/badge.h"
#include "Objects/Player/player.h"

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
    BackgroundContainer* body = nullptr;
    GridContainer* container = nullptr;
    Badge* badge = nullptr;
    TextLabel* username = nullptr;

    MultiCanvasObject* bg = nullptr;

    Inventory* inventory = nullptr;
    Player* player = nullptr;

};

#endif // PLAYERCARD_H
