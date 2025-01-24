#ifndef OVALBUTTON_H
#define OVALBUTTON_H

#include "../AbstractButton/abstractbutton.h"
#include "../../TextLabel/textlabel.h"

class OvalButton : public AbstractButton
{
public:
    enum class COLOR {
        WHITE,
        BLUE
    };

    explicit OvalButton(CanvasObject *parent = nullptr, COLOR color = COLOR::WHITE);
    CanvasObject* setIcon(QString filePath) override;
    void setText(QString text);

private:
    TextLabel* label = nullptr;
    COLOR color = COLOR::WHITE;
};

#endif // OVALBUTTON_H
