#include "map.h"

Map::Map(MultiCanvasObject* parent) : AbstractButton(parent) {
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/map/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/map/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/map/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);

    notification = new Notification(this);
    notification->setPos(QPointF(25,-5));
    notification->setNumber(1);
}

Notification* Map::getNotification(){
    return this->notification;
}
