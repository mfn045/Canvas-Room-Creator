#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include "../AbstractButton/abstractbutton.h"

class CircleButton : public AbstractButton
{
public:
    enum class COLOR {
        BLUE,
        WHITE
    };
    explicit CircleButton(CanvasObject *parent = nullptr, COLOR color = COLOR::BLUE);
    void setIcon(QString filePath) override;
};

#endif // CIRCLEBUTTON_H
