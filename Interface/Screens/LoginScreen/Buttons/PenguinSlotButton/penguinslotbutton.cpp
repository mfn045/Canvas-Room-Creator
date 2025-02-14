#include "penguinslotbutton.h"

LoginScreen::Buttons::PenguinSlotButton::PenguinSlotButton(QGraphicsItem* parent, TYPE type) : AbstractButton(parent) {
    AssetsManager* am = AssetsManager::getInstance();
    if(type == VERTICAL){
        setUp(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.vertical.up"));
        setOver(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.vertical.over"));
        setDown(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.vertical.down"));
    } else if(type == HORIZONTAL){
        setUp(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.horizontal.up"));
        setOver(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.horizontal.over"));
        setDown(am->getAssetPath("interface.screens.loginscreen.buttons.penguinslotbutton.horizontal.down"));
    }
    setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);

    setIsClickable(true);
    setIsHoverable(true);
}
