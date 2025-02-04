#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../../CanvasObject/Multi/multicanvasobject.h"
#include "../TextLabel/textlabel.h"
#include <QThread>

class Notification : public MultiCanvasObject
{
public:
    explicit Notification(MultiCanvasObject* parent = nullptr);
    int setNumber(int number);
    int getNumber();

private:
    PROPERTIES* oneDigitProperties = nullptr;
    PROPERTIES* twoDigitProperties = nullptr;
    TextLabel* digitLabel = nullptr;
    int number = 0;
    QThread* thread = nullptr;
};

#endif // NOTIFICATION_H
