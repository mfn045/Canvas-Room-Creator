#ifndef MAIL_H
#define MAIL_H

#include <QObject>
#include "../Buttons/AbstractButton/abstractbutton.h"
#include "../Notification/notification.h"

class Mail : public AbstractButton
{
    Q_OBJECT
public:
    explicit Mail(MultiCanvasObject* parent = nullptr);
    void animationIn();
    Notification* getNotification();

private:
    Notification* notification = nullptr;
    QThread* animationThread = nullptr;
};

#endif // MAP_H
