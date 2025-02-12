#include "map.h"

Map::Map(MultiCanvasObject* parent) : AbstractButton(parent) {
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.world.buttons.map.up"));
    setDown(am->getAssetPath("interface.world.buttons.map.down"));
    setOver(am->getAssetPath("interface.world.buttons.map.over"));

    notification = new Notification(this);
    notification->setPos(QPointF(25,-5));
    notification->setNumber(1);
}

Notification* Map::getNotification(){
    return this->notification;
}
