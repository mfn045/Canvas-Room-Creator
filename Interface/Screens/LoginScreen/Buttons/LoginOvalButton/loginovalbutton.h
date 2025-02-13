#ifndef LOGINOVALBUTTON_H
#define LOGINOVALBUTTON_H

#include <QGraphicsColorizeEffect>
#include <QGraphicsScene>
#include "Interface/Common/TextLabel/textlabel.h"
#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class LoginOvalButton : public AbstractButton
{
public:
    enum SIZE {
        SMALL,
        MEDIUM
    };
    explicit LoginOvalButton(MultiCanvasObject* parent = nullptr, SIZE size = SMALL);

    void setText(QString text);

private:
    SIZE type = SMALL;
    TextLabel* label = nullptr;
};

#endif // LOGINOVALBUTTON_H
