#ifndef INVENTORY_H
#define INVENTORY_H

#include "../../../canvasobject.h"
#include "../../SvgGridContainer/gridcontainer.h"
#include "../../Buttons/WhiteSquareButton/whitesquarebutton.h"
#include "../../Buttons/OvalButton/ovalbutton.h"
#include "../../Buttons/CircleButton/circlebutton.h"
#include "../../Buttons/WhiteRectButton/whiterectbutton.h"
#include "../../Buttons/Inventory/CategoryButton/categorybutton.h"
#include "../../../Objects/Items/items.h"
#include "../../../Objects/Penguin/Paper/penguinpaper.h"
#include "../../../Objects/Penguin/clothes.h"
#include "../../../Objects/Penguin/Sprite/penguinsprite.h"

class Inventory : public CanvasObject
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
    explicit Inventory(CanvasObject* parent = nullptr);

    SORT sortItemsBy(SORT sort);

    PenguinPaper* setPenguinPaper(PenguinPaper* penguin_paper);
    PenguinSprite* setPenguin(PenguinSprite* penguin);

private:
    QList<int> ownedItems = {};

    int currentInventoryPage = 1;

    void loadInventoryPage(int page, SORT sort = SORT::ALL);

    SORT sort = SORT::ALL;

    QMap<int, WhiteSquareButton*> inventoryItems;

    PenguinPaper* penguin_paper = nullptr;
    PenguinSprite* penguin = nullptr;
};

#endif // INVENTORY_H
