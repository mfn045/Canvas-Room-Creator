#ifndef FRIEND_REQUESTS_H
#define FRIEND_REQUESTS_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"
#include "../Notification/notification.h"

class Friend_Requests : public AbstractButton
{
    Q_OBJECT
public:
    explicit Friend_Requests(MultiCanvasObject* parent = nullptr);
    Notification* getNotification();

private:
    Notification* notification = nullptr;
};

#endif // MAP_H
