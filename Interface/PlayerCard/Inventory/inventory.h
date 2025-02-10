#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../../CanvasObject/Multi/multicanvasobject.h"
#include "../../../Objects/Constants/constants.h"
#include "../../SvgGridContainer/gridcontainer.h"
#include "../../Buttons/WhiteSquareButton/whitesquarebutton.h"
#include "../../Buttons/OvalButton/ovalbutton.h"
#include "../../Buttons/CircleButton/circlebutton.h"
#include "../../Buttons/WhiteRectButton/whiterectbutton.h"
#include "../../Buttons/Inventory/CategoryButton/categorybutton.h"
#include "../../../Objects/Items/items.h"
#include "../../../Objects/Player/player.h"
#include "../../../Objects/Penguin/clothes.h"

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
