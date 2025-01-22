#ifndef PLAYERCARD_H
#define PLAYERCARD_H

#include "../Buttons/BlueRectButton/bluerectbutton.h"
#include "../Buttons/CircleButton/circlebutton.h"
#include "../Buttons/WhiteSquareButton/whitesquarebutton.h"
#include "../../widgets/scene.h"
#include "../DialogGrid/dialoggrid.h"
#include "../SvgGridContainer/gridcontainer.h"
#include "../TextLabel/textlabel.h"
#include "../../Objects/PenguinPaper/penguinpaper.h"
#include "../../Objects/Badge/badge.h"
#include "../../Objects/Items/items.h"

class PlayerCard : public BlueRectButton
{
public:
    explicit PlayerCard(Scene* scene = nullptr);

private:
    QList<int> ownedItems = {};
    int currentInventoryPage = 1;

    void loadInventoryPage(int page);

    Scene* scene = nullptr;
    Penguin* penguin = nullptr;
    DialogGrid* body = nullptr;
    GridContainer* container = nullptr;
    Badge* badge = nullptr;
    TextLabel* username = nullptr;
    PenguinPaper* penguin_paper = nullptr;

    QMap<int, WhiteSquareButton*> inventoryItems;

};

#endif // PLAYERCARD_H
