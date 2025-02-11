#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"
#include "Interface/World/Buttons/Notification/notification.h"

class Map : public AbstractButton
{
    Q_OBJECT
public:
    explicit Map(MultiCanvasObject* parent = nullptr);
    Notification* getNotification();

private:
    Notification* notification = nullptr;
};

#endif // MAP_H
