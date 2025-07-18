#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "Interface/Common/CanvasObject/Multi/multicanvasobject.h"
#include "Interface/Common/TextLabel/textlabel.h"

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
};

#endif // NOTIFICATION_H
