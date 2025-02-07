#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../../CanvasObject/Multi/multicanvasobject.h"
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
    enum SORT {
        COLOR=1,
        HEAD,
        FACE,
        NECK,
        BODY,
        HAND,
        FEET,
        PIN,
        BACKGROUND,
        AWARD,
        ALL
    };
    explicit Inventory(MultiCanvasObject* parent = nullptr);

    SORT sortItemsBy(SORT sort);

    Player* setPlayer(Player* player);

private:
    int currentInventoryPage = 1;

    void loadInventoryPage(int page, SORT sort = SORT::ALL);

    SORT sort = SORT::ALL;

    Player* player = nullptr;

    QMap<int, WhiteSquareButton*> inventoryItems;
};

#endif // INVENTORY_H
