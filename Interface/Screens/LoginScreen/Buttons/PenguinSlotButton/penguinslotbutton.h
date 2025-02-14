#ifndef PENGUINSLOTBUTTON_H
#define PENGUINSLOTBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

namespace LoginScreen {
namespace Buttons {

class PenguinSlotButton : public AbstractButton
{
public:
    enum TYPE {
        VERTICAL,
        HORIZONTAL
    };
    explicit PenguinSlotButton(QGraphicsItem* parent = nullptr, TYPE type = VERTICAL);


private:

};
}
}

#endif // PENGUINSLOTBUTTON_H
