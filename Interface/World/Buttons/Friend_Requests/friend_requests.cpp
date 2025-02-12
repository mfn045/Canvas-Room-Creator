#include "friend_requests.h"

Friend_Requests::Friend_Requests(MultiCanvasObject* parent) : AbstractButton(parent) {
    setIsHoverable(true);
    setIsClickable(true);

    AssetsManager* am = AssetsManager::getInstance();
    setUp(am->getAssetPath("interface.world.buttons.friend_requests.up"));
    setDown(am->getAssetPath("interface.world.buttons.friend_requests.down"));
    setOver(am->getAssetPath("interface.world.buttons.friend_requests.over"));

    notification = new Notification(this);
    notification->setPos(QPointF(25,-5));
    notification->setNumber(7);
}

Notification* Friend_Requests::getNotification(){
    return this->notification;
}

