#ifndef INVENTORY_H
#define INVENTORY_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Widgets/Buttons/WhiteSquareButton/whitesquarebutton.h"
#include "Interface/Widgets/Buttons/OvalButton/ovalbutton.h"
#include "Interface/Widgets/Buttons/CircleButton/circlebutton.h"
#include "Interface/Widgets/Buttons/WhiteRectButton/whiterectbutton.h"
#include "Interface/Widgets/Buttons/Inventory/CategoryButton/categorybutton.h"
#include "Interface/World/Penguin/clothes.h"
#include "Objects/Items/items.h"
#include "Objects/Player/player.h"
#include "Objects/Constants/constants.h"

class Inventory : public MultiCanvasObject
{
public:
    explicit Inventory(MultiCanvasObject* parent = nullptr);

    INVENTORY::SORT sortItemsBy(INVENTORY::SORT sort);

    Player* setPlayer(Player* player);

private:
    int currentInventoryPage = 1;

    void loadInventoryPage(int page, INVENTORY::SORT sort = INVENTORY::SORT::ALL);

    INVENTORY::SORT sort = INVENTORY::SORT::ALL;

    Player* player = nullptr;

    QMap<int, WhiteSquareButton*> inventoryItems;
};

#endif // INVENTORY_H
