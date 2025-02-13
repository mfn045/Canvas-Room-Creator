#ifndef LOGINBLUEBUTTON_H
#define LOGINBLUEBUTTON_H

#include <QGraphicsColorizeEffect>
#include <QGraphicsScene>
#include "Interface/Common/TextLabel/textlabel.h"
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class LoginBlueButton : public AbstractButton
{
public:
    explicit LoginBlueButton(MultiCanvasObject* parent = nullptr);

    void setText(QString text);

private:
    TextLabel* label = nullptr;
};

#endif // LOGINBLUEBUTTON_H
