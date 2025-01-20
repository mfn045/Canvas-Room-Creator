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

class PlayerCard : public BlueRectButton
{
public:
    explicit PlayerCard(Scene* scene = nullptr);

private:
    Scene* scene = nullptr;
    DialogGrid* body = nullptr;
    GridContainer* container = nullptr;
    Badge* badge = nullptr;
    TextLabel* username = nullptr;
    PenguinPaper* penguin_paper = nullptr;

};

#endif // PLAYERCARD_H
