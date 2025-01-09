#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"
#include "../Notification/notification.h"

class Map : public AbstractButton
{
    Q_OBJECT
public:
    explicit Map(CanvasObject* parent = nullptr);
    Notification* getNotification();

private:
    Notification* notification = nullptr;
};

#endif // MAP_H
