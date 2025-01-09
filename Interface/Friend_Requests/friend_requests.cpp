#include "friend_requests.h"

Friend_Requests::Friend_Requests(CanvasObject* parent) : AbstractButton(parent) {
    QString upButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/friend_requests/up.svg";
    QString overButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/friend_requests/over.svg";
    QString downButton = "C:/Users/mfn45/OneDrive/Desktop/Interface_SVG/buttons/friend_requests/down.svg";

    setIsHoverable(true);
    setIsClickable(true);

    setUp(upButton);
    setDown(downButton);
    setOver(overButton);

    notification = new Notification(this);
    notification->setPos(QPointF(25,-5));
    notification->setNumber(7);
}

Notification* Friend_Requests::getNotification(){
    return this->notification;
}

