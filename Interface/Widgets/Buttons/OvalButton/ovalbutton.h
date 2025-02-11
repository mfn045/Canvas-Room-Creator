#ifndef OVALBUTTON_H
#define OVALBUTTON_H

#include "Interface/Widgets/Buttons/AbstractButton/abstractbutton.h"
#include "Interface/Common/TextLabel/textlabel.h"

class OvalButton : public AbstractButton
{
public:
    enum class COLOR {
        WHITE,
        BLUE
    };

    explicit OvalButton(MultiCanvasObject *parent = nullptr, COLOR color = COLOR::WHITE);
    MultiCanvasObject* setIcon(QString filePath) override;
    void setText(QString text);

private:
    TextLabel* label = nullptr;
    COLOR color = COLOR::WHITE;
};

#endif // OVALBUTTON_H
