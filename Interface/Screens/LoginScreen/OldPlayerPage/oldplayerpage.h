#ifndef OLDPLAYERPAGE_H
#define OLDPLAYERPAGE_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/Containers/GridContainer/gridcontainer.h"
#include "Interface/Widgets/BackgroundContainer/backgroundcontainer.h"
#include "Interface/World/Penguin/Paper/penguinpaper.h"
#include "Interface/Screens/LoginScreen/Buttons/PenguinSlotButton/penguinslotbutton.h"
#include "Interface/Screens/LoginScreen/Buttons/OvalButton/ovalbutton.h"
#include "Interface/Common/TitleLabel/titlelabel.h"

namespace LoginScreen {
class OldPlayerPage : public MultiCanvasObject
{
public:
    explicit OldPlayerPage(MultiCanvasObject* parent = nullptr);

    void drawSavedPlayers();

    void addPlayer(QString name, PenguinPaper* paper = new PenguinPaper());

    QMap<QString,PenguinPaper*> savedPenguins;
};
}

#endif // OLDPLAYERPAGE_H
