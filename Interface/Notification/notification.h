#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../../canvasobject.h"
#include "../TextLabel/textlabel.h"
#include <QThread>

class Notification : public CanvasObject
{
public:
    explicit Notification(CanvasObject* parent = nullptr);
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
