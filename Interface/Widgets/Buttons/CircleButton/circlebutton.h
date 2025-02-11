#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"

class CircleButton : public AbstractButton
{
public:
    enum class COLOR {
        BLUE,
        WHITE
    };
    explicit CircleButton(MultiCanvasObject *parent = nullptr, COLOR color = COLOR::BLUE);
    MultiCanvasObject* setIcon(QString filePath) override;
};

#endif // CIRCLEBUTTON_H
