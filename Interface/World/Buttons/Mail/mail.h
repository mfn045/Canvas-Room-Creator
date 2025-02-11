#ifndef MAIL_H
#define MAIL_H

#include <QObject>
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"
#include "Interface/World/Buttons/Notification/notification.h"

class Mail : public AbstractButton
{
    Q_OBJECT
public:
    explicit Mail(MultiCanvasObject* parent = nullptr);
    void animationIn();
    Notification* getNotification();

private:
    Notification* notification = nullptr;
};

#endif // MAP_H
